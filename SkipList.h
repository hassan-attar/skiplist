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
public:
    class iterator{
    private:
        Node<T> *ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = size_t;
        using pointer = T*;
        using reference = T&;
        iterator();
        explicit iterator(Node<T> *node);
        iterator & operator++();
        iterator operator++(int);
        bool operator!=(const SkipList<T>::iterator &rhs) const;
        const T &operator*() const;
    };
    // Constructors
    SkipList();
    explicit SkipList(size_t maxLevel);
    SkipList(const std::initializer_list<T> &list);
    SkipList(const SkipList<T> &rhs);
    SkipList(SkipList<T> &&rhs) noexcept ;
    virtual ~SkipList();
    SkipList<T> &operator=(const SkipList<T> &rhs);
    SkipList<T> &operator=(SkipList<T> &&rhs) noexcept;
    // Getters
    size_t getSize() const;
    size_t getMaxLevel() const;

    // Methods
    void displayHeadToTail() const;
    void displayLevelByLevel() const;
    void insert(const T &item);
    void clear();
    SkipList<T>::iterator find(const T &item) const;
    bool remove(const T &item);

    // iterators
    SkipList<T>::iterator begin() const;
    SkipList<T>::iterator end() const;


    static const size_t DEFAULT_MAX_LEVEL;
protected:
    // Instance data
    Node<T> **heads;
    RandomCoinFlip *randomCoinFlip;
    size_t size;
    size_t maxLevel;
    // Helper methods
    Node<T> *findItem(const T &item, Node<T> **update = nullptr) const;
    size_t randomLevel() const;
};

#include "SkipList.tpp"
#endif //SKIPLIST_SKIPLIST_H

