#include "Indexer.h"
#include <string>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <functional>

using namespace std;

//Constructor Definition
Indexer::Indexer(string filterFile, string dataFile)
{
	//Calls FileExists to check to see if filterfile exists
	//Throw exception if it does not.
	if (!FileExists(filterFile.c_str()))
	{
		throw Exceptions(filterFile + " was not found!");
	}

	//Calls FileExists to check to see if datafile exists
	//Throws exception if it does not
	else if (!FileExists(dataFile.c_str()))
	{
		throw Exceptions(dataFile + " was not found!");
	}
	
	datafile = dataFile;
	filterfile = filterFile;

}

//FileExists definition
bool Indexer::FileExists(const char* testFile)
{
	//creates bool variable to return
	bool openFile = true;

	//opens file for read in
	fstream infile(testFile, ios::in);
	if(infile.fail()) // if file doesn't open return print error message and exit program
	{
		cout << testFile << " was not successfully opened." << endl;
		openFile = false;
		return openFile;
	}
	else
	{
		cout << testFile << " was successfully opened." << endl;
	}

	//close file and return openFile variable
		infile.close();
		return openFile;
}

//FileFilterReader definition
BinarySearchTree<Word> Indexer::FileFilterReader(string filterfile)
{
	//creates string variables to store full line and the next word in the line
	string getLine;
	string next;
	
	//opens filterfile
	fstream infile(filterfile.c_str(), ios::in);

	//initializes lineNum to 0 so we can assign lineNum to a Word node later
	//in this function it never increments so we can tell it
	int lineNum = 0;

	//loop to read each line from file
	do
	{
		//gets a whole line from the file
		getline(infile,getLine);

		//assigns stringstream object to getLine and reads the first word called next
		stringstream ss;
		ss << getLine;
		ss >> next;

		//loops through getLine and does all string manipulation operations
		do
		{
			//creates array of punction to check for
			char chars[] = "().,\"!?:;";
			//converts all alphas to lowercase
			transform(next.begin(), next.end(), next.begin(), ::tolower); 
			//removes punctuation defined in char array
			for (unsigned int i = 0; i<strlen(chars); ++i)
			{
				next.erase(remove(next.begin(), next.end(), chars[i]), next.end());
			}
			//erases all digits
			next.erase(std::remove_if(next.begin(), next.end(), ::isdigit), next.end());
			//removes any punctuation found at beginning of the words
			while (ispunct(next[0]))
				next.erase(0,1);

			//removes hyphens and apostrophes at the end of the words
			for (int n=next.length(); n && next[--n]=='-'; next.resize(n));
			for (int n=next.length(); n && next[--n]=='\''; next.resize(n));

			//creates a new Word object
			Word newWord(next,lineNum);
			// adds the object to the tree
			filteredBST.insert(newWord);
		} while (ss >> next);


	} while (!infile.eof());

	//closes file
	infile.close();

	//returns the BST
	return filteredBST;
}

BinarySearchTree<Word> Indexer::FileWordReader(string datafile)
{
	//creates string variables to store full line and the next word in the line
	string getLine;
	string next;
	
	//opens datafile
	fstream infile(datafile.c_str(), ios::in);

	//initializes lineNum
	int lineNum= 0;

	//loops through each line of datafile
	do
	{
		//gets individual line from file
		getline(infile,getLine);
		//increments lineNum
		lineNum++;

		//assigns stringstream object to getLine and reads the first word called next
		stringstream ss;
		ss << getLine;
		ss >> next;

		//loops through getLine and does all string manipulation operations
		do
		{
			//creates array of punctuation to check for
			char chars[] = "().,\"!?:;";
			//converts all alphas to lower
			transform(next.begin(), next.end(), next.begin(), ::tolower); 
			//removes all punctuation defined in char array
			for (unsigned int i = 0; i<strlen(chars); ++i)
				{
					next.erase(remove(next.begin(), next.end(), chars[i]), next.end());
				}
			//erases all digits from word
			next.erase(std::remove_if(next.begin(), next.end(), ::isdigit), next.end());
			//removes all punctuation at beginning of words
			while (ispunct(next[0]))
				next.erase(0,1);
			//removes hyphens or apostrophes at end of words
			for (int n=next.length(); n && next[--n]=='-'; next.resize(n));
			for (int n=next.length(); n && next[--n]=='\''; next.resize(n));
			
			//creates new word
			Word newWord(next,lineNum);
			//if the word is nothing dont do anything
			if (next == "")
				;
			//otherwise compare to filtered BST
			else if (!(filteredBST.contains(newWord)))
			{
				//if it does not exist in filteredBST add it to indexedBST
				indexedBST.insert(newWord);
			}
		} while (ss >> next);


	} while (!infile.eof());

	//close file
	infile.close();

	//return indexedBST
	return indexedBST;
}

//Do Index definition
void Indexer::DoIndex()
{
	filteredBST = FileFilterReader(filterfile);
	indexedBST = FileWordReader(datafile);

	//call output results
	OutputResults();
	//print message saying that program has finished running
	cout << "Binary trees successfully written to files." << endl;
}

//output results function definition
void Indexer::OutputResults()
{
	//out two files for output
	ofstream indexOut("indexResults.txt", ios::out);
	ofstream filterOut("filterResults.txt", ios::out);

	//add information from trees to the files
	indexedBST.outTree(indexOut);
	filteredBST.outTree(filterOut);

	//close the files
	indexOut.close();
	filterOut.close();
}