#include "../../headers/ideal.hpp"
#include <iostream>
#include <vector>
#include <assert.h>


using T = int;

T slow_get_page(T key){
    return key;
}

int test(std::vector<T>& test_keys, size_t cap){
    int hit = 0;
    ideal_caches::ideal_cache_<T> c{cap};
    for(auto i = test_keys.begin(); i != test_keys.end(); ++i){
        if(c.lookup_update(test_keys, *i, slow_get_page(*i))){
            hit += 1;
        }
    }
    return hit;
}

int main(){
    
    std::vector<int> hits { 0 };
    
    //test for capacity of cache = 2, 3 and 4
    size_t cap1 = 3;
    size_t cap2 = 2;
    size_t cap3 = 4;
    std::vector<std::vector<T>> test_keys = {
    {1, 2, 5, 5, 5, 3, 2, 1}, 
    {8, 9, 0, 2, 4, 7, 6, 5, 7, 1},
    {8, 9, 2, 8, 8, 8, 6, 8, 3, 8},
    {9, 4, 3, 5, 1, 7, 4, 3, 1, 4}, 
    {0, 1, 7, 8, 9, 1, 5, 4, 9, 2}, 
    {0, 1, 7, 8, 9, 3, 5, 4, 6, 2} };
    
    hits[0] = test(test_keys[0], cap1);
    hits[1] = test(test_keys[1], cap1);
    hits[2] = test(test_keys[2], cap1);
    hits[3] = test(test_keys[3], cap2);
    hits[4] = test(test_keys[4], cap3);
    hits[5] = test(test_keys[5], cap2);
    
    assert(hits[0] == 3);
    assert(hits[1] == 1);
    assert(hits[2] == 5);
    assert(hits[3] == 2);
    assert(hits[4] == 2);
    assert(hits[5] == 0);

    
    for(auto i = test_keys.begin(); i != test_keys.end(); ++i){
        for(auto a = (*i).begin(); a != (*i).end(); ++a) 
            std::cout << *a << " ";
        std::cout << std::endl;    
    }
    
    std::cout << "TEST OK" << std::endl;
}
