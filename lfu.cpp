#include <iostream>
#include <ctime>
#include <string>
#include "lfu.hpp"


int main(){
    unsigned int start_time = clock();
    std::cout << "Start program" << std::endl;  
    int num_pages;
    size_t capacity;
    typedef std::string T;
   
    std::cin >> capacity; 
    std::cin >> num_pages;
    caches::cache_t<T, page<T>> c{capacity};

    int count = 0;
    for(int i = 0; i < num_pages; i++){
        page<T> k;
        std::cin >> k.id;
        if(c.lookup_update(k)) count += 1;
        
    }
    std::cout << count << std::endl;
    unsigned int end_time = clock();
    double search_time = ((double)(end_time - start_time))/ 1000.0;
    std::cout << "runime (sec) = " << search_time << std::endl;

    return 0;
}