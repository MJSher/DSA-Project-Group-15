#include "KMP.h"
#include <fstream>
#include <string>

//functions
//function to read in the file and store it as a vector of strings
std::vector<std::string> read_file(std::string file_name);
//function that outputs the algorithm stage: basically selects which algorithm you will pick
void algorithm_stage();
//function that asks which word you will select. is_KMP is your algorithm choice from the first function.
//is_KMP is true if you selected KMP, and false if you selected Boyer_More
void word_select_stage(bool is_KMP);
//function that shows the first position you found the line at, and gives you choices on what to do next.
void choice_stage(std::pair<bool, std::vector<int>> search_result, int position_index);
//function that replaces the word with something else (this will alter the line)
void replace(std::string &line, int starting_position, std::string new_word);
//replaces all instances of the old word with the new word
void replace_all(std::vector<std::string> &document, std::string old_word, std::string new_word);
//writes the output file
void write_output(std::vector<std::string> document);

//only 1 CLA argument
int main(int argc, char* argv[])
{
    std::string file_name = argv[1];
    std::vector<std::string> document = read_file(file_name);

    for (int i = 0; i < document.size(); i++)
    {
        for (int j = 0; j < document[i].size(); j++)
        {
            std::cout << document[i][j];
        }
        std::cout << std::endl;
    }
}

//function definitions
std::vector<std::string> read_file(std::string file_name)
{
    std::vector<std::string> file_vector = {};

    std::ifstream(my_file);
    my_file.open(file_name); //create and open the file named file_name
    std::string line;
    while (std::getline(my_file, line, '\n'))
    {
        file_vector.push_back(line);
    }

    my_file.close();
    return file_vector;
}
