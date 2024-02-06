//
// Created by Hassan Attar on 2024-01-25.
//

#include "Node.h"

template<typename T>
Node<T>::Node(const T &data): Node(data, 0) {}

template<typename T>
Node<T>::Node(const T &data, int _level): next{new Node<T>*[_level + 1]}, level{_level}, data{data} {}

template<typename T>
Node<T>::~Node() {
    if(next){
        delete [] next;
    }
}
template<typename T>
Node<T>::Node(const Node<T> &rhs): Node(rhs.data, rhs.level) {
    for(int i = 0; i <= level; i++){
        next[i] = rhs.next[i];
    }
}
template<typename T>
Node<T> &Node<T>::operator=(const Node<T> &rhs) {
    if(this != &rhs){
        if(next){
            delete [] next;
        }
        level = rhs.level;
        data = rhs.data;
        next = new Node<T>*[level + 1];
        for(int i = 0; i <= level; i++){
            next[i] = rhs.next[i];
        }
    }
}

template<typename T>
Node<T>::Node(Node<T> &&rhs) noexcept: next{rhs.next}, level{rhs.level}, data{rhs.data} {
    rhs.next = nullptr;
}
template<typename T>
Node<T> &Node<T>::operator=(Node<T> &&rhs) {
    if(next){
        delete [] next;
    }
    next = rhs.next;
    data = rhs.data;
    level = rhs.level;
    rhs.next = nullptr;
}


