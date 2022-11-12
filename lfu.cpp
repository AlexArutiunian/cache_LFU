#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "headers/lfu1.hpp"


using T = int;
T slow_get_page(T key){ return key; }

int main(){
    int num_pages;
    size_t capacity;
    
    std::cin >> capacity >> num_pages;

    int count = 0;  
    caches::cache_t<T> c{capacity};

    for(int i = 0; i < num_pages; ++i){
        T k;
        std::cin >> k;
        if(c.lookup_update(k, slow_get_page(k))) count += 1;
    }
    std::cout << count << std::endl;
    return 0;
}
