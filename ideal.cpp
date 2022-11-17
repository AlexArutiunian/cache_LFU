#include "headers/ideal.hpp"


using T = int;
T slow_get_page(T key){ return key; }

int main(){
    auto start = std::chrono::steady_clock::now();
    
    size_t capacity = 5;
    int num_pages = 100;
   // std::cin >> capacity >> num_pages;

    std::vector<T> all_keys1;
    std::vector<T> all_keys;
    /*for(int i = 0; i != num_pages; ++i){
        T k;
        std::cin >> k;
        all_keys.push_back(k);
    }*/
    all_keys = {8, 4, 1, 7, 1, 2, 3, 8, 7, 9, 0, 1, 0, 6, 10, 3, 0, 8, 3, 6, 2, 2, 7, 6, 7, 4, 10, 3, 8, 3, 6, 7, 4, 9,
    8, 8, 5, 0, 3, 7, 3, 1, 9, 9, 7, 5, 9, 9, 9, 2, 4, 8, 1, 4, 10, 8, 5, 0, 9, 5, 0, 5, 6, 2, 4, 1, 9, 10,
    7, 2, 7, 10, 10, 4, 0, 8, 9, 7, 3, 6, 4, 1, 5, 8, 8, 2, 7, 3, 3, 3, 2, 7, 4, 2, 9, 7, 7, 1, 0, 5};
    

    ideal_caches::ideal_cache_<T> c(all_keys, capacity);  // 2 10 9 4 3 5 1 7 4 3 1 4
    
    int a = 0;
    int hits = 0;
    for(auto i : all_keys){
       // c.dump_ftr();
        if(c.lookup_update(i, i, a)) hits += 1;
       
        a += 1;
        std::cout << a << ")";
        c.dump_c();
    }
    
   /* for(auto i : all_keys){
        c.upd_future(i, a);
        a += 1;
        c.dump();
    }*/
    std::cout << hits << std::endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    
    std::cout << "runtime (sec) = " << elapsed_seconds.count() << std::endl;
    
    return 0;
}
