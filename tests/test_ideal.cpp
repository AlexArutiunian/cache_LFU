#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "../headers/ideal.hpp"
#include "../headers/random_test.hpp"



using T = int;
T slow_get_page(T key){ return key; }

int main(){
    int num_pages = 8;
    size_t capacity = 3;
    test::test(3, 10, 10);  
    std::ifstream myfile;
    myfile.open("test.1");

    std::ofstream restest;
    restest.open("restest.1");
    

    for(int a = 0; a < 100; ++a){

        int count = 0; 
        myfile >> capacity >> num_pages; 
        ideal_caches::ideal_cache_<T> c{capacity};
        std::list<T> all_keys;
        restest << "test " << a + 1 << ": ";
        for(int i = 0; i != num_pages; i++){
            T k;
            myfile >> k;
            all_keys.push_back(k);
            std::cout << k << " ";
            restest << k << " ";
        }


        for(auto i = all_keys.begin(); i != all_keys.end(); ++i){
            

            if(c.lookup_update(all_keys, *i, slow_get_page(*i))) count += 1;
        }
        std::cout << '\n';
        std::cout << "res " << a + 1 << ": " << count << std::endl;
        restest << "answer: " << count << '\n';

    }
    return 0;
}
