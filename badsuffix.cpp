#include <iostream>
#define CHARLIM 256
//CHARLIM = character limit
int biggest(int data1, int data2) {
   if(data1 > data2)
   return data1;
   return data2;
}
void BadCharHeur(string string, int size, int badchar[CHARLIM])
{
	for (int i = 0; i < CHARLIM; i++)
		badchar[i] = -1;
	for (int i = 0; i < size; i++)
		badchar[(int)string[i]] = i;
}
void search(string txt, string pat)
{
	int alength = pat.size();
	int blength= txt.size();
	int badchar[CHARLIM];
	BadCharHeur(pat, blength, badchar);
	int shift = 0;
	while(shift <= (blength - alength))
	{
		int j = alength - 1;
		while(j >= 0 && pat[j] == txt[shift + j])
			j--;
		if (j < 0)
		{
			shift += if(shift + alength < blength) alength-badchar[txt[shift + alength]] else 1;
		}
		else
			shift += max(1, j - badchar[txt[shift + j]]);
	}
}
