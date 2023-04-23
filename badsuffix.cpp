#include <iostream>
#include <vector>

void BadCharHeur(std::string string, int badchar[127]) //Generates the array used to find the shift.
{
    for (int i = 0; i < 127; i++) { //Set the shift for every character to -1.
        badchar[i] = -1;
    }
    for (int i = 0; i < string.size(); i++) { //Set the shift for characters in the string to their position in the string.
        badchar[string[i]] = i;
    }

}
std::pair<int, std::vector<int>> BMAlgorithim(std::string text, std::string pat)
{
    int patternLength = pat.size();
    int textLength= text.size();
    int badChar[127];
    BadCharHeur(pat, badChar);
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
            if (shift + patternLength < textLength) { //If the pattern would not go past the edge of the text
                shift += patternLength - badChar[text[shift + patternLength]];
            } else {
                shift += 1;
            }
        }
        else { //The pattern does not match the text;
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
