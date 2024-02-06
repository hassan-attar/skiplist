//
// Created by Hassan Attar on 2024-01-25.
//

#ifndef SKIPLIST_NODE_H
#define SKIPLIST_NODE_H
template<typename T>
class Node {
public:
    Node<T> **next; // 8 bytes
    int level;
    T data; // max 8 bytes on this pc
    explicit Node(const T &data);
    Node(const T &data, int _level);
    Node(const Node<T> &rhs);
    Node(Node<T> &&rhs) noexcept ;
    Node<T> &operator=(const Node<T> &rhs);
    Node<T> &operator=(Node<T> &&rhs);
    ~Node();
};
#include "Node.tpp"

#endif // SKIPLIST_NODE_H