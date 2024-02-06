//
// Created by Hassan Attar on 2024-01-25.
//
#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include "Node.h"
#include <initializer_list>
#include "RandomCoinFlip.h"
template<typename T>
class SkipList {
    // Instance data
    Node<T> **heads;
    RandomCoinFlip *randomCoinFlip;
    int size;
    int maxLevel;

    // Static data
    static const int DEFAULT_MAX_LEVEL;
    // Private methods
    Node<T> *findItem(const T &item, Node<T> **update = nullptr);
    int randomLevel();

public:
    class iterator : std::iterator<std::forward_iterator_tag, T, size_t,T*, T&>{
    private:
        Node<T> *ptr;
    public:
        iterator();
        iterator(Node<T> *node);
        iterator & operator++();
        iterator operator++(int);
        bool operator!=(const SkipList<T>::iterator &rhs);
        T operator*();
    };
    // Constructors
    SkipList();
    explicit SkipList(int maxLevel);
    SkipList(const std::initializer_list<T> &list);
    SkipList(const SkipList<T> &rhs);
    SkipList(SkipList<T> &&rhs) noexcept ;
    ~SkipList();
    SkipList<T> &operator=(const SkipList<T> &rhs);
    SkipList<T> &operator=(SkipList<T> &&rhs);
    // Getters
    int getSize();
    int getMaxLevel();

    // Methods
    void displayHeadToTail();
    void displayLevelByLevel();
    void insert(const T &item);
    void clear();
    const Node<T> *find(const T &item);
    T remove(const T &item);

    // iterators
    SkipList<T>::iterator begin();
    SkipList<T>::iterator end();
};

#include "SkipList.tpp"
#endif //SKIPLIST_SKIPLIST_H

