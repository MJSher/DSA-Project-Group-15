#include <vector>
#include <string>
#include <iostream>
class KMP
{
private:
    std::string pattern;
    std::string text;
    std::vector<int> create_LPS(); //creates LPS string to use for KMP
    int num_matches; //number of matches
public:
    KMP(std::string input_text, std::string input_pattern); //so the inputs are CLD's
    void search(int mode); //so I think I will give a mode that asks for things
    void public_LPS(); //public function for testing. Will delete later.
    void KMP_algorithm();
};
