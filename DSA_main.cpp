#include "KMP.h"
#include <fstream>
#include <string>
#include <vector>


//FIND AND REPLACE: Given a document, this program is able to find the first instance a specific phrase is used,
//and is able to flip through the next instance of that phrase, or replace one or all instances of that phrase
//with another. The user is able to do this either using the Knuth–Morris–Pratt(KMP) algorithm or
//the Boyer-Moore algorithm.

//functions
//function to read in the file and store it as a vector of strings
std::vector<std::string> read_file(std::string file_name);
//function that outputs the algorithm stage: basically selects which algorithm you will pick
void algorithm_stage(std::vector<std::string> document);
//function that asks which word you will select. is_KMP is your algorithm choice from the first function.
//is_KMP is true if you selected KMP, and false if you selected Boyer_More
void word_select_stage(bool is_KMP, std::vector<std::string> document );
//function that shows the first position you found the line at, and gives you choices on what to do next.
void choice_stage(std::pair<bool, std::vector<int>> search_result, int position, int position_index, std::string phrase, int line_index, std::vector<std::string> document);//function that searches for the next instance of the word
//function that moves to the next element of the array
void next_stage(std::pair<bool, std::vector<int>> search_result, int position, int position_index, std::string phrase, int line_index, std::vector<std::string> document);
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
    algorithm_stage(document); //starts the program output
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

void algorithm_stage(std::vector<std::string> document)
{
    char algorithm;
    std::cout << "Welcome to the find and replace program!" << std::endl;
    std::cout << "Which algorithm would you like to use? The Knuth-Morris-Pratt(KMP) algorithm or the Boyer-Moore algorithm?" << std::endl;
    std::cout << "(select K (or k) for KMP, and B (or b) for Boyer_Moore)" << std::endl;
    std::cin >> algorithm;
    switch (algorithm)
    {
        case 'K':
            word_select_stage(true, document);
            break;
        case 'k':
            word_select_stage(true, document);
            break;
        case 'B':
            word_select_stage(false, document);
            break;
        case 'b':
            word_select_stage(false, document);
            break;
        default:
            std::cout << "That is not an acceptable input. Try again." << std::endl;
            algorithm_stage(document);
            break;
    }
}

void word_select_stage(bool is_KMP, std::vector<std::string> document)
{
    std::string phrase;
    std::cout << "which phrase do you want to find? (make sure it matches capitalization)" << std::endl;
    std::cin >> phrase;
    if (is_KMP) //if you chose KMP
    {
        KMP algorithm;
        std::pair<bool, std::vector<int>> results;
        results.first = false;
        int counter = 0;
        while (!results.first && counter < (document.size() - 1)) //makes sure to find the first line with the word
        {
            results = algorithm.KMP_algorithm(document[counter], phrase);
            if (results.first == true)
            {
                break;
            }
            counter++;
        }
        if (!results.first) //if there are no matches in the document
        {
            std::cout << "This word cannot be found in the document. Try again with another word" << std::endl << std::endl;
            algorithm_stage(document);
        }
        else
        {
            //move onto the choice stage
            choice_stage(results, results.second[0], 0, phrase, counter, document);
        }

    }
    else //if you chose Boyer-Moore
    {
        std::cout << "The boyer Moore algorithm has not been implemented at this point." << std::endl;
        std::cout << "Come back later." << std::endl;
        return;
    }
}

void choice_stage(std::pair<bool, std::vector<int>> search_result, int position, int position_index, std::string phrase, int line_index, std::vector<std::string> document)
{
    //display which word you got
    char choice;
    std::cout << phrase << " was found at this line at index " << position << ":\n";
    std::cout << '"' << document[line_index] << '"' <<  std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "\t -Go to the next instance of this word (N)" << std::endl;
    std::cout << "\t -Replace this current word (R)" << std::endl;
    std::cout << "\t -Go back (B)" << std::endl;
    std::cin >> choice;
    switch(choice)
    {
        case 'N':
            next_stage(search_result, position, position_index, phrase, line_index, document);
            break;
        case 'n':
            next_stage(search_result, position, position_index, phrase, line_index, document);
            break;
        case 'R':
            //
            break;
        case 'r':
            //
            break;
        case 'B':
            //
            break;
        case 'b':
            //
            break;
        default:
            //
            break;
    }
}

void next_stage(std::pair<bool, std::vector<int>> search_result, int position, int position_index, std::string phrase, int line_index, std::vector<std::string> document)
{
    std::cout << "test" << std::endl;
    if (position_index < (search_result.second.size() - 1))
    {
        choice_stage(search_result, search_result.second[position_index + 1], (position_index + 1), phrase, line_index, document);
    }
    else
    {
        KMP algorithm;
        search_result.first = false;
        int i = 1;
        while ((line_index + i) < document.size() && search_result.first == false)
        {
            search_result = algorithm.KMP_algorithm(document[line_index + i], phrase);
            if (search_result.first) //this is the line in which it fails
            {
                break;
            }
            i++;
        }
        if (!search_result.first)
        {
            std::cout << "No other matches can be found." << std::endl;
        }
        else
        {
            if(line_index <= (document.size() - 1))
            {
                choice_stage(search_result, search_result.second[0], 0, phrase, (line_index + i), document);
            }
            else
            {
                std::cout << "No other matches can be found." << std::endl;
            }
        }
    }
}
