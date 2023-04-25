#include <vector>
#include <string>
#include <iostream>
#include <utility>
class KMP
{
private:
    std::string pattern;
    std::string text;
    std::vector<int> create_LPS(); //creates LPS string to use for KMP
    int num_matches; //number of matches
    friend class Find_Replace;
public:
    KMP(); //so the inputs are CLA's
    void public_LPS(std::string input_text, std::string input_pattern); //public function for testing. Will delete later.
    std::pair<bool, std::vector<int>> KMP_algorithm(std::string input_text, std::string input_pattern);
    void print_num_matches();
};
