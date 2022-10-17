#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "../headers/lfu1.hpp"
#include "random_test.hpp"


typedef int T;
T slow_get_page(T key){ return key; }

int main(){
    unsigned int start_time = clock();
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
    
    unsigned int end_time = clock();
    double search_time = ((double)(end_time - start_time))/ 1000.0;
    std::cout << "runtime (sec) = " << search_time << std::endl;
    
    return 0;
}
