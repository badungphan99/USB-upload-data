//
// Created by dungpb on 8/25/20.
//

#include <iostream>		// Include all needed libraries here
#include <wiringPi.h>

//using namespace std;		// No need to keep using “std”

int main()
{
    wiringPiSetup();			// Setup the library
//    pinMode(25, OUTPUT);		// Configure GPIO0 as an output
    pinMode(27, INPUT);		// left
    pinMode(26, INPUT);         // down
    pinMode(22, INPUT);         // up
    pinMode(21, INPUT);         // right

// Main program loop
    while(1)
    {
        // Button is pressed if digitalRead returns 0
//        if(digitalRead(1) == 1)
//        std::cout <<"27 " << digitalRead(27) << "\n";
//        std::cout <<"26 " << digitalRead(26) << "\n";
        std::cout <<"22 " << digitalRead(22) << "\n";
        std::cout <<"21 " << digitalRead(21) << "\n";
        delay(500);

    }
    return 0;
}