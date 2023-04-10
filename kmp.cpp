#include "kmp.h"

//constructor: just a simple getter that assigns the private text and pattern functions
KMP::KMP(std::string input_text, std::string input_pattern)
{
    this->text = input_text;
    this->pattern = input_pattern;
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
    int counter = 0;
    int prev_index = 0; //prefix. The i in the loop is suffix.
    lps_vector.push_back(0); //the first element of an LPS vector is always 0
    for (int i = 1; i < this->pattern.size(); i++)
    {
        if (this->pattern[i] == this->pattern[prev_index])
        {
            prev_index++;
            lps_vector.push_back(prev_index);

        }
        else
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
        std::cout << vec[i] << ", ";
    }
    std::cout << std::endl;

}
