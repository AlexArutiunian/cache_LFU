#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include "../../headers/ideal.hpp"
#include "../../headers/random_test_ideal.hpp"



using T = int;
T slow_get_page(T key){ return key; }

int main(){
    auto start = std::chrono::steady_clock::now();
    int num_pages = 200000;
    size_t capacity = 100000;
    test::test(num_pages, capacity, 100000);  
    std::ifstream myfile;
    myfile.open("test.1");

    std::ofstream restest;
    restest.open("restest.1");
    

    //for(int a = 0; a < 100; ++a){

    int count = 0; 
    myfile >> capacity >> num_pages; 
    
    std::vector<T> all_keys;
    // restest << "test " << a + 1 << ": ";
    for(int i = 0; i != num_pages; i++){
        T k;
        myfile >> k;
        all_keys.push_back(k);
    //    std::cout << k << " ";
        restest << k << " ";
    }

    int z = 0;
    ideal_caches::ideal_cache_<T> c{all_keys, capacity};
    for(auto i = all_keys.begin(); i != all_keys.end(); ++i){
        z += 1;
        if(c.lookup_update(*i, slow_get_page(*i), z)) count += 1;
    }
    /*   std::cout << '\n';
    std::cout << "res " << a + 1 << ": " << count << std::endl;
    restest << "answer: " << count << '\n';*/
        
   // }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << count << std::endl;
    std::cout << "runtime (sec) = " << elapsed_seconds.count() << std::endl
    << "\nthe number of pages: " << num_pages << " and capacity of cache: " << capacity;
    return 0;
}
