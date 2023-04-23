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