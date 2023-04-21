#include "kmp.h"

//constructor: just a simple getter that assigns the private text and pattern functions
KMP::KMP(std::string input_text, std::string input_pattern)
{
    this->text = input_text;
    this->pattern = input_pattern;
    this->num_matches = 0;
}

//This function creates an LPS table, also known as a prefix table
//LPS stands for "longest prefix which is also a suffix"
//Basically, the length of shared elements between the first and last parts of the array.
//Each element of the LPS table shows how long the LPS would be if the index you are at is the last element
//This table is used to find elements in the text that already show up in the pattern and allows the program
//to skip them. This allows the KMP algorithm to have a time complexity of O(n)
std::vector<int> KMP::create_LPS()
{
    std::vector<int> lps_vector;
    int prev_index = 0; //prefix. The i in the loop is suffix.
    lps_vector.push_back(0); //the first element of an LPS vector is always 0
    for (int i = 1; i < this->pattern.size(); i++) //i is current index
    {
        if (this->pattern[i] == this->pattern[prev_index]) //if the current and previous element match
        {
            prev_index++;
            lps_vector.push_back(prev_index); //the current element matches the value of the previous element + 1

        }
        else //if they do not match
        {
            if (prev_index == 0)
            {
                lps_vector.push_back(0);
            }
            else
            {
                prev_index = lps_vector[prev_index - 1];
                i--;
            }
        }
    }

    return lps_vector;
}
//This function allows you to publicly display the LPS.
void KMP::public_LPS()
{
    std::vector<int> vec = create_LPS();
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << ",";
    }
    std::cout << std::endl;

}

//This function
std::pair<bool, std::vector<int>> KMP::KMP_algorithm()
{
    std::vector<int> match_positions = {};
    bool has_match = false;
    std::pair<bool, std::vector<int>> return_pair;
    int pattern_index = 0; //starts at 0 because that's the beginning of the pattern
    int text_index = 0; //starts at beginning of text
    std::vector LPS = create_LPS();
    while (text_index < this->text.size()) //this goes through the entire text
    {
        while (pattern_index < this->pattern.size()) //this goes through the entire pattern until there is a mismatch
        {
            if (this->pattern[pattern_index] != this->text[text_index]) //if there is a mismatch
            {
                break; //check if this break completely from the while loop as I do not want pat and text to increment.
            }
            pattern_index++;
            text_index++;
        }
        if (pattern_index == this->pattern.size())
        {
            //then it should be a match
            //std::cout << "Found match at position " << (text_index - this->pattern.size()) << std::endl;
            has_match = true;
            match_positions.push_back(text_index - this->pattern.size());
            this->num_matches++;
            if (pattern_index == 0)
            {
                text_index++;
            }
            else
            {
                pattern_index = LPS[pattern_index - 1];
            }
        }
        else
        {
            //not a match
            if (pattern_index == 0)
            {
                text_index++;
            }
            else
            {
                pattern_index = LPS[pattern_index - 1];
            }
            //text_index++; //text should not increment when a mismatch occurs
        }
    }
    return_pair.first = has_match;
    return_pair.second = match_positions;
    return return_pair;
}

void KMP::print_num_matches()
{
    std::cout << "num matches: " << this->num_matches << std::endl;
}
