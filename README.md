# SkipList (Probabilistic Data Structure)

Sample Run of size 25:
<pre>
Level 0 : * -> 0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25    -> * 
Level 1 : * ->      1                   5         7    8         10   11                  15        17   18   19   20        22        24   25    -> * 
Level 2 : * ->      1                   5                        10                       15             18                            24   25    -> * 
Level 3 : * ->      1                   5                                                                18                                       -> * 
Level 4 : * ->                                                                                           18                                       -> * 
</pre>
## Overview

This repository contains a C++ implementation of a SkipList data structure. SkipList is a data structure that allows for efficient search, insertion, and removal of elements, providing logarithmic time complexity for these operations on average. The SkipList utilizes a randomized process (coin flip) to determine the level of each node. This is a lean implementation, suitable for utilizing it as a submodule in your other repositories.

## Usage

**To use the SkipList in your project, include the `SkipList.h` header file and instantiate a `SkipList` object with the desired type.**
The implementation is in the .tpp file, you don't need to compile it, just compile your main program that includes the header file, and the compiler will find the .tpp itself.

## How to Compile the program:
make sure you included the SkipList.h in your main.cpp (or whatever file that is using SkipList).
```bash
g++ -std=c++17 RandomCoinFlip.cpp main.cpp -o prog
```
## How to use the SkipList in your applications:
```cpp
#include <iostream>
#include "SkipList.h"

int main() {
    // Create a SkipList of integers
    SkipList<int> skipList;

    // Insert some elements
    skipList.insert(10);
    skipList.insert(20);
    skipList.insert(30);
    skipList.insert(40);

    // Display the SkipList from head to tail
    std::cout << "SkipList from head to tail:" << std::endl;
    for(const int &x : p){
        std::cout << x << " ";
    }
    std::cout << std::endl;
    // skipList.displayHeadToTail(); optionally you can use that

    // Display the SkipList level by level
    std::cout << "\nSkipList level by level:" << std::endl;
    skipList.displayLevelByLevel(); // useful for debugging

    // Find an element
    int searchValue = 20;
    SkipList<int>::iterator it = skipList.find(searchValue);
    if (it != skipList.end()) {
        std::cout << "\nFound " << searchValue << " in the SkipList." << std::endl;
    } else {
        std::cout << "\n" << searchValue << " not found in the SkipList." << std::endl;
    }

    // Remove an element
    int removeValue = 30;
    if (skipList.remove(removeValue)) {
        std::cout << "\nRemoved " << removeValue << " from the SkipList." << std::endl;
    } else {
        std::cout << "\n" << removeValue << " not found in the SkipList." << std::endl;
    }

    // Display the SkipList after removal
    std::cout << "\nSkipList after removal:" << std::endl;
    skipList.displayHeadToTail();

    return 0;
}

```
