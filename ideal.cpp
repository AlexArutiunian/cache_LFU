#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "headers/ideal.hpp"


using T = int;
T slow_get_page(T key){ return key; }

int main(){
    int num_pages = 10;
    size_t capacity = 3;
    
    std::cin >> capacity >> num_pages;

    int count = 0;  
    ideal_caches::ideal_cache_<T> c{capacity};
    std::list<T> all_keys;
    for(int i = 0; i != num_pages; i++){
        T k;
        std::cin >> k;
        all_keys.push_back(k);
    }
  //  all_keys = {4, 1, 7, 1, 1, 1, 7, 0, 4, 0};

    for(auto i = all_keys.begin(); i != all_keys.end(); ++i){
        
        if(c.lookup_update(all_keys, *i, slow_get_page(*i))) count += 1;
    }
    std::cout << count << std::endl;
    return 0;
}
