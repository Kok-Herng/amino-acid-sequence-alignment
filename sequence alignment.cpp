 // CPP program to implement sequence alignment problem. 
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

// function to find out the minimum penalty 
void getMinimumPenalty(string seq1, string seq2, int mmp, int gp)
{
	int i, j; // intialising variables 

	int m = seq1.length(); // length of gene1 
	int n = seq2.length(); // length of gene2 

	// table for storing optimal substructure answers 
	int scoreFunction[m + 1][n + 1] = { 0 };

	// intialising the table 
	for (i = 0; i <= (n + m); i++)
	{
		scoreFunction[i][0] = i * gp;
		scoreFunction[0][i] = i * gp;
	}

	// calcuting the minimum penalty 
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (seq1[i - 1] == seq2[j - 1])
			{
				scoreFunction[i][j] = scoreFunction[i - 1][j - 1];
			}
			else
			{
				scoreFunction[i][j] = min({ scoreFunction[i - 1][j - 1] + mmp ,
								            scoreFunction[i - 1][j] + gp ,
								            scoreFunction[i][j - 1] + gp });
			}
		}
	}

	// Reconstructing the solution 
	int maxl = n + m; // maximum possible length 

	i = m; j = n;

	int pos1 = maxl;
	int pos2 = maxl;

	// Final answers for the respective strings 
	int ans1[maxl + 1], ans2[maxl + 1];

	while (!(i == 0 || j == 0))
	{
		if (seq1[i - 1] == seq2[j - 1])
		{
			ans1[pos1] = (int)seq1[i - 1];
			ans2[pos2] = (int)seq2[j - 1];
			pos1--;
			pos2--;
			i--; 
			j--;
		}
		else if (scoreFunction[i - 1][j - 1] + mmp == scoreFunction[i][j])
		{
			ans1[pos1] = (int)seq1[i - 1];
			ans2[pos2] = (int)seq2[j - 1];
			pos1--;
			pos2--;
			i--; 
			j--;
		}
		else if (scoreFunction[i - 1][j] + gp == scoreFunction[i][j])
		{
			ans1[pos1] = (int)seq1[i - 1];
			ans2[pos2] = (int)'_';
			pos1--;
			pos2--;
			i--;
		}
		else if (scoreFunction[i][j - 1] + gp == scoreFunction[i][j])
		{
			ans1[pos1] = (int)'_';
			ans2[pos2] = (int)seq2[j - 1];
			pos1--;
			pos2--;
			j--;
		}
	}
	while (pos1 > 0)
	{
		if (i > 0) 
		{
		    ans1[pos1] = (int)seq1[i-1];
		    pos1--;
		    i--;
		}
		else 
		{
		    ans1[pos1] = (int)'_';
		    pos1--;
		}
	}
	while (pos2 > 0)
	{
		if (j > 0) 
		{
		    ans2[pos2] = (int)seq2[j-1];
		    pos2--;
		    j--;
		}
		else 
		{
		    ans2[pos2] = (int)'_';
		    pos2--;
		}
	}

	// Since we have assumed the answer to be n+m long, we need to remove the extra gaps in the starting 
	int filterseq = 1;
	for (i = maxl; i >= 1; i--)
	{
		if ((char)ans2[i] == '_' && (char)ans1[i] == '_')
		{
			filterseq = i + 1;
			break;
		}
	}

	// Printing the final answer 
	cout << "Minimum Penalty in aligning the genes = ";
	cout << scoreFunction[m][n] << "\n";
	cout << "The aligned genes are :\n";
	for (i = filterseq; i <= maxl; i++)
	{
		cout << (char)ans1[i];
	}
	cout << "\n";
	for (i = filterseq; i <= maxl; i++)
	{
		cout << (char)ans2[i];
	}

	return;
}

// Deliver code 
int main() {
	string gene1, gene2; 
	int misMatchPenalty, gapPenalty;
	
	cout<<"======================================================================\n";
    cout<<"==                    Sequence Alignment Program                    ==\n";
    cout<<"==                             Welcome!                             ==\n";
    cout<<"======================================================================\n";
	  
	// input strings 
	cout << "Please enter gene 1:" << endl;
	cin >> gene1;
	
	cout << "Please enter gene 2:" << endl;
	cin >> gene2;
	
	// intialsing penalties of different types 
	// While the input entered is not an integer, prompt the user to enter an integer.
	cout << "Please enter penalty for gap:" << endl;
	cin >> gapPenalty;
	while(!cin)
    {
        cout << "That was not an integer! Please enter an integer for gap penalty: \n";
        cin.clear();
        cin.ignore();
        cin >>gapPenalty;
    }
	
	cout << "Please enter penalty for mismatch:" << endl;
	cin >> misMatchPenalty;
    while(!cin)
    {
        cout << "That was not an integer! Please enter an integer mismatch penalty: \n";
        cin.clear();
        cin.ignore();
        cin >> misMatchPenalty;
    }
    
	// calling the function to calculate the result 
	getMinimumPenalty(gene1, gene2,
		misMatchPenalty, gapPenalty);

	cout << endl;
	cout << endl;
    cout << "Thank you for using our program!"<<endl;
	return 0;
}

