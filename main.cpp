#include <iostream>
#include "kmp.h"
#include <ctime>


//time function
//the text is the first string, and the pattern is the second. Uses CLA's
int main(int argc, char* argv[]) {
    std::string text = argv[1];
    std::string pattern = argv[2];
    KMP thing(text, pattern);

    //this is for time. Will need to change
    unsigned long c_start, c_end;
    c_start = std::clock();
    thing.public_LPS(); //this is where you put the functions you want to bench mark
    c_end = std::clock();
    float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << "time: " << output << std::endl;

}
