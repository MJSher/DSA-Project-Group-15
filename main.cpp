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
    std::pair<bool, std::vector<int>> pair_var = thing.KMP_algorithm();
    std::cout << "does it have a match?: " << pair_var.first << ". list of matches if so: " << std::endl;
    for (int i = 0; i < pair_var.second.size(); i++)
    {
        std::cout << pair_var.second[i] << ", ";
    }
    std::cout << std::endl;
    c_end = std::clock();
    float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    thing.print_num_matches();
    std::cout << "time: " << output << std::endl;

}
