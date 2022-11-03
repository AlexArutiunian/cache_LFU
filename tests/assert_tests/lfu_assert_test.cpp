#include "../../headers/lfu1.hpp"
#include <iostream>
#include <vector>
#include <assert.h>


using T = int;

T slow_get_page(T key){
    return key;
}

int test(std::vector<T>& test_keys, size_t cap){
    int hit = 0;
    caches::cache_t<T> c{cap};
    for(auto i = test_keys.begin(); i != test_keys.end(); ++i){
        if(c.lookup_update(*i, slow_get_page(*i))){
            hit += 1;
        }
    }
    return hit;
}

int main(){
    
    std::vector<int> hits { 0 };
    
    size_t cap = 3;
    
    std::vector<std::vector<T>> test_keys = {
    {1, 2, 5, 5, 5, 3, 2, 1}, 
    {1, 0, 3, 4, 0, 3, 9, 1, 9, 6},
    {8, 9, 2, 8, 8, 8, 6, 8, 3, 8},
    {1, 2, 3, 4, 1, 2, 4, 4, 4, 3, 2, 2}, 
    {0, 1, 7, 8, 9, 1, 5, 4, 9, 2} };
    
    hits[0] = test(test_keys[0], cap);
    hits[1] = test(test_keys[1], cap);
    hits[2] = test(test_keys[2], cap);
    hits[3] = test(test_keys[3], cap);
    hits[4] = test(test_keys[4], cap);
    
    assert(hits[0] == 3);
    assert(hits[1] == 2);
    assert(hits[2] == 5);
    assert(hits[3] == 5);
    assert(hits[4] == 0);

    std::cout << "capacity = " << cap << std::endl;
    for(auto i = test_keys.begin(); i != test_keys.end(); ++i){
        for(auto a = (*i).begin(); a != (*i).end(); ++a) 
            std::cout << *a << " ";
        std::cout << std::endl;    
    }
    
    std::cout << "TEST OK" << std::endl;
}

