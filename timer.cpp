//
// Created by dungpb on 22/08/2020.
//

#define TIME 1000000000

#include <chrono>
#include <unistd.h>
#include <iostream>

int main()
{
    int x = 0;
    auto timeStart = std::chrono::high_resolution_clock::now();
    while (true) {

//        sleep(1);
        auto time = (std::chrono::high_resolution_clock::now() - timeStart).count();
        if (time > TIME) {
            std::cout << x++ << "\n";
            timeStart = std::chrono::high_resolution_clock::now();
        }
    }
}