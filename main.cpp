#include <iostream>
#include "SkipList.h"
#include <vector>
#include <algorithm>
#include <random>


int main() {
    int size{100};
    std::vector<int> randomValues(size);
    int i;
    for(i = 0; i < size; i++){
        if(i == size/2){
            randomValues[i]= 0;
            std::cout << ">>> Insert Test Opportunity for latter: Middle element not in the list is: "<< (size/2 + 1) << std::endl;
            continue;
        }
        randomValues[i]= i + 1; // items to be inserted range from 1 to size (both inclusive)
    }
    std::cout << "A vector<int> of size " << size << " has been created and filled with values 1 to " << size << "." << std::endl;

    std::cout << "Enter Number of levels for SkipList (Default is 20 (recommended)): (MAX is 100)" << std::endl;
    SkipList<int> *s = new SkipList<int>();


    std::cout << "Shuffling numbers in the vector..." << std::endl;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(randomValues.begin(), randomValues.end(), g); // put input data in random order
    std::cout << ">>> vector<int> has been randomly shuffled, elements will be inserted in the SkipList in random order to make sure it can handle all the cases of insertion properly" << std::endl;
    i = 0;
    for(const int &x: randomValues){
        s->insert(x); // insert them into SkipList
        i++;
        if(i % (size/4) == 0){
            std::cout <<(i / (size/4))*25 <<  "% of elements inserted successfully." << std::endl;
        }
    }
    std::cout << "#### SkipList Created. ####"<< std::endl;
    SkipList<int> p(*s);
    SkipList<int> q;
    q = p;
    SkipList<int> t(std::move(q));
    SkipList<int> o;
    p.displayLevelByLevel();
    o = std::move(p);
    o.displayLevelByLevel();
    std::cout << "p,q\n";
    q.displayHeadToTail();
    p.displayHeadToTail();
    std::cout << "o, t\n";
    o.displayHeadToTail();
    t.displayHeadToTail();

    SkipList<int>::iterator it;
    for(it = s->begin(); it != s->end(); ++it){
        std::cout << *it << " -> ";
    }
    std::cout << std::endl;
    std::cout << "forRange\n";
    for(int x : *s){
        std::cout << x << " -> ";
    }

    std::cout << std::endl;
    it = s->find(40);
    std::cout << "40 is in the list: " << (it != s->end()) << std::endl;
    it = s->find(120);
    std::cout << "120 is in the list: " << (it != s->end()) << std::endl;
    delete s;
    return 0;
}

