#include <iostream>
#include <cmath>
#include <vector>
#define CHARLIM 127
//CHARLIM = character limit

void BadCharHeur(std::string string, int size, int badchar[CHARLIM])
{
    for (int i = 0; i < CHARLIM; i++) {
        badchar[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        badchar[(int)string[i]] = i;
    }

}
std::pair<int, std::vector<int>> BMAlgorithim(std::string text, std::string pat)
{
    int patternLength = pat.size();
    int textLength= text.size();
    int badChar[CHARLIM];
    BadCharHeur(pat, textLength, badChar);
    int shift = 1;
    std::vector<int> locations;
    int found = 0; //used to keep track if at least one match has been found.
    while(shift <= (textLength - patternLength))
    {
        int patternIndex = patternLength - 1;
        while(patternIndex >= 0 && pat[patternIndex] == text[shift + patternIndex]) { //For as long as the pattern and text match
            patternIndex--;
        }
        if (patternIndex < 0) { //This means the whole pattern matches the text
            locations.push_back(shift);
            found = 1;
            if (shift + patternLength < textLength) {
                shift += patternLength - badChar[text[shift + patternLength]];
            } else {
                shift = 1;
            }
        }
        else { //The patterns does not match the text;
            shift += std::max(1, patternIndex - badChar[text[shift + patternIndex]]);
        }
    }
    std::pair<int, std::vector<int>> returnValue;
    returnValue.first = found;
    returnValue.second = locations;
    return returnValue;
}

int main() { //For testing purposes only, to be removed later
    std::pair<int, std::vector<int>> returnValue;
    returnValue = BMAlgorithim("Much, much longer stringly. I think ring should appear at least twice, though still somewhat sparingly.", "ring");
    //In sample text, 'ring' appears at index 20, 36, 96
    for (int i = 0; i < returnValue.second.size(); i++) {
        std::cout << returnValue.second[i] << std::endl;
    }
    return 0;
}
