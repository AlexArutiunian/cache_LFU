#pragma once

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

namespace test {

void test(int m, int n, int range){
    std::ofstream myfile;
    myfile.open("test.1");
    
    for(int a = 0; a < 100; a++){
        myfile << m << " " << n << " ";
        for (int i = 0; i < n; ++i) {
            int a = std::rand() % range;
            myfile << a << " ";
        }
    }
    myfile.close();
}    
};
