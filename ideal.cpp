#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "headers/ideal.hpp"


using T = int;
T slow_get_page(T key){ return key; }

int main(){
    int num_pages = 100;
    size_t capacity = 5;
    
    std::cin >> capacity >> num_pages;

    int count = 0;  
    ideal_caches::ideal_cache_<T> c{capacity};
    std::vector<T> all_keys1;
    std::vector<T> all_keys;
    for(int i = 0; i != num_pages; i++){
        T k;
        std::cin >> k;
        all_keys.push_back(k);
    }
    all_keys1 = {8, 4, 1, 7, 1, 2, 3, 8, 7, 9, 0, 1, 0, 6, 10, 3, 0, 8, 3, 6, 2, 2, 7, 6, 7, 4, 10, 3, 8, 3, 6, 7, 4, 9,
    8, 8, 5, 0, 3, 7, 3, 1, 9, 9, 7, 5, 9, 9, 9, 2, 4, 8, 1, 4, 10, 8, 5, 0, 9, 5, 0, 5, 6, 2, 4, 1, 9, 10,
    7, 2, 7, 10, 10, 4, 0, 8, 9, 7, 3, 6, 4, 1, 5, 8, 8, 2, 7, 3, 3, 3, 2, 7, 4, 2, 9, 7, 7, 1, 0, 5};
    int a = 0;
    for(auto i = all_keys.begin(); i != all_keys.end(); ++i){
        //dump - for print actually cache 
        a += 1;
        if(c.lookup_update(all_keys, *i, slow_get_page(*i), a)) count += 1;
       // c.dump(a);
    }
    std::cout << count << std::endl;
    return 0;
}
