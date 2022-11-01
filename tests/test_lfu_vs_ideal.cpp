#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include "../headers/ideal.hpp"
#include "../headers/random_test.hpp"
#include "../headers/lfu1.hpp"



using T = int;
T slow_get_page(T key){ return key; }

int main(){
    auto start = std::chrono::steady_clock::now();
    int num_pages = 8;
    size_t capacity = 3;
    test::test(3, 10, 10);  
    std::ifstream myfile;
    myfile.open("test.1");

    std::ofstream restest;
    restest.open("../tests/compare_lfu_vs_ideal.txt");
    

    for(int a = 0; a < 100; ++a){

        int count_ideal = 0;
        int count_lfu = 0; 
        myfile >> capacity >> num_pages; 
        ideal_caches::ideal_cache_<T> c{capacity};
        caches::cache_t<T> c_lfu{capacity};
        std::list<T> all_keys;
        restest << "test " << a + 1 << ": ";
        for(int i = 0; i != num_pages; ++i){
            T k;
            myfile >> k;
            all_keys.push_back(k);
            std::cout << k << " ";
            restest << k << " ";
        }


        for(auto i = all_keys.begin(); i != all_keys.end(); ++i){
            if(c.lookup_update(all_keys, *i, slow_get_page(*i))) count_ideal += 1;
            if(c_lfu.lookup_update(*i, slow_get_page(*i))) count_lfu += 1;
        }
        std::cout << '\n';
        std::cout << "res " << a + 1 << " ideal: " << count_ideal << "; lfu: " << count_lfu << std::endl;
        restest << "answer_ideal: " << count_ideal << " answer_lfu: " << count_lfu << '\n';
        
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    
    std::cout << "runtime (sec) = " << elapsed_seconds.count() << std::endl;
    return 0;
}
