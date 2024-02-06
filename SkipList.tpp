//
// Created by Hassan Attar on 2024-01-25.
//

#include "SkipList.h"
#include <cmath>
#include <iostream>
#include <iomanip>

template<typename T>
const size_t SkipList<T>::DEFAULT_MAX_LEVEL = 25;
/**
 * Initializer list constructor
 * @param list std::initializer_list<T>
 */
template<typename T>
SkipList<T>::SkipList(const std::initializer_list<T> &list)
:heads{new Node<T>*[maxLevel]}, randomCoinFlip{new RandomCoinFlip()}, size{0}{
    for(int i = 0; i < maxLevel; i++) heads[i] = nullptr;
    for(const T &x: list)
        insert(x);
}

/**
 * Default Constructor
 */
template<typename T>
SkipList<T>::SkipList():SkipList(DEFAULT_MAX_LEVEL){}

template<typename T>
SkipList<T>::SkipList(size_t _maxLevel): heads{new Node<T>*[_maxLevel]}, randomCoinFlip{new RandomCoinFlip()}, size{0}, maxLevel{_maxLevel} {
    for(int i = 0; i < maxLevel; i++) heads[i] = nullptr;
}

/**
 * Copy Constructor
 * @param rhs
 */
template<typename T>
SkipList<T>::SkipList(const SkipList<T> &rhs): SkipList(rhs.maxLevel) {
    Node<T> *temp = rhs.heads[0];
    while(temp){
        insert(temp->data);
        temp = temp->next[0];
    }
}

template<typename T>
SkipList<T>::SkipList(SkipList<T> &&rhs) noexcept: SkipList(rhs.maxLevel){
    size = rhs.size;
    for(int i = 0; i < maxLevel; i++){
        heads[i] = rhs.heads[i];
    }
    rhs.heads = nullptr;
}

template<typename T>
SkipList<T> &SkipList<T>::operator=(SkipList<T> &&rhs) {
    clear();
    maxLevel = rhs.maxLevel;
    size = rhs.size;
    heads = new Node<T>*[maxLevel];
    for(int i = 0; i < maxLevel; i++){
        heads[i] = rhs.heads[i];
    }
    rhs.heads = nullptr;
}
template<typename T>
SkipList<T> &SkipList<T>::operator=(const SkipList<T> &rhs) {
    if(this != &rhs){
        clear();
        Node<T> *temp = rhs.heads[0];
        while(temp){
            insert(temp->data);
            temp = temp->next[0];
        }
    }
}
template<typename T>
SkipList<T>::~SkipList() {
    clear();
    delete randomCoinFlip;
}

template<typename T>
void SkipList<T>::clear() {
    Node<T> *prev {nullptr};
    // heads[0] is utilized to store the next node.
    if(heads && heads[0]){
        prev = heads[0];
        heads[0] = heads[0]->next[0];
    }
    // either heads && heads[0] exist, or the list is empty all together.
    while(heads[0]){
        delete prev;
        prev = heads[0];
        heads[0] = heads[0]->next[0];
    }
    if(prev){
        delete prev;
    }
    if(heads){
        delete [] heads;
    }
    heads = nullptr;
    size = 0;
}

/**
 * Returns a number between 0 (inclusive) and maxLevel (exclusive), representing the level to which the node will go up.
 * Probability of a node rising each level is 1/2
 * @return random level
 */
template<typename T>
size_t SkipList<T>::randomLevel() {
    size_t level = 0;
    while(level < maxLevel - 1){
        if(randomCoinFlip->flipCoin() == 0) break;
        level++;
    }
    return level;
}

template<typename T>
Node<T> *SkipList<T>::findItem(const T &item, Node<T> **update) {
    int currentLevel = maxLevel - 1; // start from top most level.
    Node<T> *cur, *prev{nullptr};
    while (currentLevel >= 0){
        cur = prev ? prev->next[currentLevel] : heads[currentLevel];
        /*
        if cur becomes null, there are 2 cases:
            1- if prev is null, that means that level has no nodes (empty level)
                => cur should start from the beginning of the next level
            2- if prev is not null, which means cur is either at the end of that level or has a data greater than or equal to item. therefore, the item should be on the right side of the prev node.
                => cur should start from the prev node (scan the bottom level from that element forward)
        cur starts to point at heads[currentLevel], since prev is null at the beginning;
        */
        while(cur && item > cur->data){ // move cur to the smallest element, larger than or equal to item or null(end of that level)
            prev = cur;
            cur = cur->next[currentLevel];
        }
        // we either reached the end of a level, or a node whose data is larger than or equal to item
        if(update) update[currentLevel] = prev;
        --currentLevel; // go to the bottom level.
    }
    // cur now points to the item or the smallest element larger than the item.
    return cur;
}

/**
 * inserts item into the SkipList, if it does not already exist.
 * @param item to be inserted
 */
template<typename T>
void SkipList<T>::insert(const T &item) {
    Node<T> **update = new Node<T> *[maxLevel]; // array for updating links between node after insertion
    for(int i = 0; i < maxLevel; i++) update[i] = nullptr;

    Node<T> *cur = findItem(item, update); // cur now points to the item or the smallest element larger than the item.
    if(cur && cur->data == item) return; // don't add duplicates

    int itemLevel = randomLevel(); // determine to which level the new node should be promoted
    Node<T> *newNode = new Node<T>(item, itemLevel);

    for(int currentLevel = 0; currentLevel <= itemLevel; currentLevel++){ //update the links of new node and the SkipList
        newNode->next[currentLevel] = update[currentLevel] ? update[currentLevel]->next[currentLevel] : heads[currentLevel];
        update[currentLevel] ? update[currentLevel]->next[currentLevel] = newNode : heads[currentLevel] = newNode;
        /*
        newNode next at each level should point to:
            1- if update[currentLevel] is null, that means the newNode is becoming the first node in a level.
                => A - newNode->next[currentLevel] should become heads[currentLevel] (which is either null(level was empty), or address of the previous first node in that level)
                   B - heads[currentLevel] should now point to the new Node
            2- if update[currentLevel] is not null
            Attention: update[currentLevel]->item, is the largest data, smaller than the item. the new node is inserted after that node.
                => A - newNode->next should point to the next node of update[currentLevel].
                   B - update[currentLevel]->next[currentLevel] should become the newNode
         */
    }
    size++;
    delete[] update;
}

/**
 * This methods performs something similar to binary search on the SkipList. It runs in average-case: O(Log(n)), worst-case O(n)
 * @param item to search for
 * @return a pointer to the item, or nullptr if not found
 */
template<typename T>
typename SkipList<T>::iterator SkipList<T>::find(const T &item) {
    Node<T> *cur = findItem(item);
    // cur now points to the item or the largest element smaller than the item.
    if(cur && cur->data == item) return SkipList<T>::iterator(cur);
    else return end();
}
/**
 * Removes item from the SkipList, if doesn't exist, will throw runtime_error
 * @param item to be removed
 * @return true if success, false otherwise.
 */
template<typename T>
bool SkipList<T>::remove(const T &item) {
    Node<T> **update = new Node<T> *[maxLevel]; // array for updating links between node after insertion
    for (int i = 0; i < maxLevel; i++) update[i] = nullptr;
    Node<T> *cur = findItem(item, update);
    // cur now points to the item or the largest element smaller than the item.
    if (!cur || cur->data != item) {
        return false;
    }; // don't need to delete anything
    for (int currentLevel = 0; currentLevel <= cur->level; currentLevel++) {
        /*
        if update[currentLevel] is null, that means the cur is the first node in that level.
                => heads[currentLevel] should point to the next node of the cur (heads[currentLevel] = cur->next[currentLevel])
        if update[currentLevel] is NOT null, then it is the node before the element to be deleted.
                => it's next should point to the cur->next at that same level
         */
        update[currentLevel] ? update[currentLevel]->next[currentLevel] = cur->next[currentLevel]
                             : heads[currentLevel] = cur->next[currentLevel];
    }
    delete cur;
    delete[] update;
    size--;
    return true;
}

/**
 * Display elements in level 0
 */
template<typename T>
void SkipList<T>::displayHeadToTail() {
    Node<T>* temp = heads[0];
    while(temp){
        std::cout << temp->data << " ";
        temp = temp->next[0];
    }
    std::cout << std::endl;
}
/**
 * Display elements level by level
 */
template<typename T>
void SkipList<T>::displayLevelByLevel() {
    T *arr = new T[size];
    Node<T>* temp;
    int i;
    for(int curLevel = 0; curLevel < maxLevel && heads[curLevel]; curLevel++){
        i = 0;
        std::cout << "Level " << std::setw(2) << curLevel <<": * -> ";
        temp = heads[curLevel];
        while(temp){
            if(curLevel == 0){
                arr[i++] = temp->data;
            } else {
                while(arr[i] != temp->data){
                    std::cout << std::setw(4) << "" << " ";
                    i++;
                }
            }
            std::cout << std::setw(4) << temp->data << " ";
            temp = temp->next[curLevel];
            if(curLevel != 0) i++;
        }
        while(i < size){
            std::cout << std::setw(4) << "" << " ";
            i++;
        }
        std::cout <<" -> * " << std::endl;
    }

}

template<typename T>
size_t SkipList<T>::getSize() {
    return size;
}
template<typename T>
size_t SkipList<T>::getMaxLevel() {
    return maxLevel;
}

template<typename T>
typename SkipList<T>::iterator SkipList<T>::begin() {
    return SkipList<T>::iterator(heads[0]);
}
template<typename T>
typename SkipList<T>::iterator SkipList<T>::end() {
    return SkipList<T>::iterator(nullptr);
}



// Iterator

template<typename T>
SkipList<T>::iterator::iterator() : ptr{nullptr}{}

template<typename T>
SkipList<T>::iterator::iterator(Node<T> *node): ptr{node} {}

template<typename T>
bool SkipList<T>::iterator::operator!=(const SkipList<T>::iterator &rhs) {
    return ptr != rhs.ptr;
}
template<typename T>
typename SkipList<T>::iterator &SkipList<T>::iterator::operator++() {
    if(ptr){
        ptr = ptr->next[0];
    }
    return *this;
}
template<typename T>
typename SkipList<T>::iterator SkipList<T>::iterator::operator++(int) {
    SkipList<T>::iterator it = *this;
    ++it;
    return it;
}

template<typename T>
T SkipList<T>::iterator::operator*() {
    return ptr->data;
}





