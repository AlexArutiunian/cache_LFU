#include <iostream>

#include "lfu.hpp"


int main(){
    std::cout << "Start program" << std::endl;  
    int num_pages;
    size_t capacity;
    
    std::cin >> capacity; 
    std::cin >> num_pages;
    caches::cache_t<int> c{capacity};
  
    int count = 0;
    for(int i = 0; i < num_pages; i++){
        page k;
        std::cin >> k.id;
        if(c.lookup_update(k.id)) count += 1;
    }
    std::cout << count << std::endl;
    return 0;
}