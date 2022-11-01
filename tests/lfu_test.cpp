#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include "../headers/lfu1.hpp"
#include "../headers/random_test.hpp"


using T = int;
T slow_get_page(T key){ return key; }

int main(){
    auto start = std::chrono::steady_clock::now();	
    std::cout << "Start testing" << std::endl;
    test::test(3, 10, 10);  
    int num_pages;
    size_t capacity;
    
    std::ifstream myfile;
    myfile.open("test.1");

    std::ofstream restest;
    restest.open("restest.1");
    int count = 0;

    
    for(int a = 0; a < 100; ++a){
        
        myfile >> capacity >> num_pages;
        caches::cache_t<T, T> c{capacity};
        restest << "test " << a + 1 << ": ";
        for(int i = 0; i < num_pages; i++){
            
            T k;
            myfile >> k;
            if(c.lookup_update(k, slow_get_page(k))) count += 1;
            std::cout << k << " ";
            restest << k << " ";
        }
        
        std::cout << '\n';
        std::cout << "res " << a + 1 << ": " << count << std::endl;
        restest << "answer: " << count << '\n';
        count = 0;
    }
    
    myfile.close();
    restest.close();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    
    std::cout << "runtime (sec) = " << elapsed_seconds.count() << std::endl;
    
    return 0;
}
