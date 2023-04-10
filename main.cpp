#include <iostream>
#include "kmp.h"

//the text is the first string, and the pattern is the second. Uses CLA's 
int main(int argc, char* argv[]) {
    std::string text = argv[1];
    std::string pattern = argv[2];
    KMP thing(text, pattern);
    thing.public_LPS();
}
