#include <iostream>
#include <vector>
#include <string>

void generateStrongGoodSuffixShift(int *shift, int *borderPos, std::string pattern) {
    //shift and borderPos is an array with size equal to the pattern + 1.
    int patternLength=pattern.size();
    int tempPatLength = patternLength;
    int j=patternLength+1;
    borderPos[patternLength]=j; //Set borderPos[patternLength] to patternLength+1.
    while(tempPatLength>0) {
        while(j<=patternLength && pattern[tempPatLength-1] != pattern[j-1]) {//If the spot at pattern[temp-1] doesn't equal pattern[j-1]
            if (shift[j]==0) { //If shift is 0
                shift[j] = j-tempPatLength; //Set shift to j-temp
            }
            j = borderPos[j];
        }
        tempPatLength--;
        j--;
        borderPos[tempPatLength] = j;
    }
}

void generateWeakGoodSuffixShift(int *shift, int *borderPosArr, std::string pattern) { //Preprocess for case 2, when there is no proper suffix.
    int patternLength = pattern.size();
    int borderPos = borderPosArr[0];
    for(int i=0; i <= patternLength; i++) {
        if(shift[i] == 0) { //If the shift isn't set to anything
            shift[i] = borderPos; //Set the shift to the borderPos at this location
        }
        if (i == borderPos) { //When i = border location
            borderPos = borderPosArr[borderPos]; //Update the border position to a new one.
        }
    }
}

void BadCharHeur(std::string string, int badchar[127]) { //Generates the array used to find the shift.
    for (int i = 0; i < 127; i++) { //Set the shift for every character to -1.
        badchar[i] = -1;
    }
    for (int i = 0; i < string.size(); i++) { //Set the shift for characters in the string to their position in the string.
        badchar[string[i]] = i;
    }
}

std::pair<bool, std::vector<int>> BMAlgorithim(std::string text, std::string pat) {
    int patternLength = pat.size();
    int textLength= text.size();
    //Bad Character Heuristic
    int badChar[127];
    BadCharHeur(pat, badChar);
    //Good Suffix Heuristic
    int borderPosition[patternLength + 1];
    int shiftArr[patternLength + 1];
    for (int i = 0; i < patternLength + 1; i++) { //Set initial value of shift to 0.
        shiftArr[i] = 0;
    }
    generateStrongGoodSuffixShift(shiftArr, borderPosition, pat);
    generateWeakGoodSuffixShift(shiftArr, borderPosition, pat);
    int shift = 1;
    std::vector<int> locations; //List of indexes where the pattern appears.
    bool found = 0; //used to keep track if at least one match has been found.
    while(shift <= (textLength - patternLength)) { //Until the shift goes past the edge of the text
        int patternIndex = patternLength - 1;
        while(patternIndex >= 0 && pat[patternIndex] == text[shift + patternIndex]) { //For as long as the pattern and text match
            patternIndex--;
        }
        if (patternIndex < 0) { //This means the whole pattern matches the text
            locations.push_back(shift);
            found = 1;
            int tempBadCharShift = 1;
            if (shift + patternLength < textLength) { //If the pattern would not go past the edge of the text
                tempBadCharShift = patternLength - badChar[text[shift + patternLength]];
            }
            //Shift by the highest of the two heuristics
            shift += std::max(shiftArr[0], tempBadCharShift);
        }
        else { //The pattern does not match the text;
            //Shift the highest of the two heuristics
            shift += std::max(shiftArr[patternIndex + 1], patternIndex - badChar[text[shift + patternIndex]]);
        }
    }
    std::pair<bool, std::vector<int>> returnValue;
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
