#include <iostream>
void prosuffix(int *shift, int *bpos, char *pattern, int alength)
{
	int i=alength;
	int j=alength+1;
	bpos[i]=j;
	while(i>0)
	{
		while(j<=a && pattern[i-1] != pattern[j-1])
		{
			if (shift[j]==0)
				shift[j] = j-i;
			j = bpos[j];
		}
		i--;j--;
		bpos[i] = j;
	}
}
void process2(int *shift, int *bpos, char *pattern, int alength)
{
	int j = bpos[0];
	for(int i=0; i<=alength; i++)
	{
		if(shift[i]==0)
			shift[i] = j;
		if (i==j)
			j = bpos[j];
	}
}
void search(string txt, string pat)
{
	int alength = pat.size();
	int blength= txt.size();
    int bpos[alength+1]
	int shift[alength+1];
    for(int i=0; i<alength+1; i++) shift[i]=0;
    prosuffix(shift, bpos, pattern, alength);
    procase2(shift, bpos, pattern, alength);
	while(shift <= (blength - alength))
	{
		int j = alength - 1;
		while(j >= 0 && pattern[j] == txt[shift + j])
			j--;
		if (j < 0)
		{
			shift += (shift + alength < blength) alength-badchar[txt[shift + alength]] : 1;
		}
		else
			shift += max(1, j - badchar[txt[shift + j]]);
	}
}

// bad char h
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
