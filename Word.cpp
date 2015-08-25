#include "Word.h"
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

// less than operator overload
bool Word::operator < (const Word &rhs) const
{
	//creates bool variable to return
	bool lessThan;

	//if lhs word is less than rhs less than is true, otherwise its falsefalse
	if (strcmp(wordText.c_str(),rhs.wordText.c_str()) < 0) 
		lessThan = true;
	else
		lessThan = false;

	return lessThan;
}

// is equal operator overload
bool Word::operator == (Word &rhs) const
{
	//creates bool variable to return
	bool equalTo;

	//if the words are equal equal to is true and it calls Countword, otherwise it is set to false
	if (strcmp(wordText.c_str(),rhs.wordText.c_str()) == 0)
	{
		equalTo = true;
		rhs.CountWord(tempLineNum);
	}
	else
		equalTo = false;

	return equalTo;
}

//equal sign operator overload
//this is never used in my program
Word Word::operator = (const Word &rhs)
{
	//assigns member variables in lhs word to rhs word
	wordText = rhs.wordText;
	lineNumbers = rhs.lineNumbers;
	count = rhs.count;
	return *this;
}

//getWord def, returns wordText
string Word::GetWord()
{
	return wordText;
}

//CountWord definition
void Word::CountWord (int lineNumber)
{
	//if lineNumber != 0
	//if (lineNumber != 0)
	//{
		count+=1; //count increments
		//if (!(lineNumbers.front() == lineNumber)) // if lineNumbers.front is not equal to linenumber
			lineNumbers.push(lineNumber); // linenumber gets pushed to queue
	//}
}

//Default constructor, does nothing
Word::Word()
{
}

//Custom constructor
Word::Word(string word, int lineNum)
{
	//assigns wordText to word
	wordText = word;
	//starts count at 1
	count = 1;
	//pushes first lineNumber to queue
	lineNumbers.push(lineNum);
	//creates a tempLineNum
	tempLineNum = lineNum;
}

