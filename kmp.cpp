#include "kmp.h"

//constructor: just a simple getter that assigns the private text and pattern functions
KMP::KMP(std::string input_text, std::string input_pattern)
{
    this->text = input_text;
    this->pattern = input_pattern;
    this->num_matches = 0;
}
/*The LPS is an essential string that helps dictate how far to skip over if there isn't a match
 * because the LPS already knows what is repeated, saving us time
 *To create the LPS, it is essentially a string of numbers that shows how many times an element is repeated
 * So for AAAA the LPS is 0 1 2 3 because the last element of A has 3 previous A's directly behind it
 * However, the counter resets when a new letter is introduced, even when the same letter repeated before
 * so AABA is 0100. B has no B's behind it, and the last A has a B behind it, meaning there are no A's
 * directly behind it.
 * The reason the LPS is a vector and not a string is so that I can more easily access the numbers
 * Counter starts at 0 and is going to be placed in the LPS vector
 * if current matches previous: increase counter by 1
 * if current does not match prev and counter == 0, make counter 0
 * if current does not match prev and counter != 0, counter gains the value of LPS two slots ago*/


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

void KMP::public_LPS()
{
    std::vector<int> vec = create_LPS();
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << ",";
    }
    std::cout << std::endl;

}


void KMP::KMP_algorithm()
{
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
            std::cout << "Found match at position " << (text_index - this->pattern.size()) << std::endl;
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
}

void KMP::print_num_matches()
{
    std::cout << "num matches: " << this->num_matches << std::endl;
}
