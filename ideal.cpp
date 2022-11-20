#include "headers/ideal.hpp"
#include <chrono>

using T = int;
T slow_get_page(T key){ return key; }

int main(){
    
    
    size_t capacity = 0;
    int num_pages = 0;
    std::cin >> capacity >> num_pages;

    std::vector<T> all_keys;
    for(int i = 0; i != num_pages; ++i){
        T k;
        std::cin >> k;
        all_keys.push_back(k);
    }
    
    auto start = std::chrono::steady_clock::now();
    ideal_caches::ideal_cache_<T> c(all_keys, capacity); 
    int a = 0;
    int hits = 0;
    for(auto i : all_keys){
        if(c.lookup_update(i, i, a)) hits += 1;
        a += 1;
    }
    
  
    std::cout << hits << std::endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    
    std::cout << "runtime (sec) = " << elapsed_seconds.count() << std::endl;
    
    return 0;
}
