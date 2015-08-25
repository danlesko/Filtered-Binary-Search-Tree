//Dan Lesko

#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <queue>

using namespace std;

//Word Class Definition
class Word
{
	private:
		//private member variables
		int count;
		queue<int> lineNumbers;
		string wordText;
		int tempLineNum;

	public:
		//constructor prototypes
		Word();
		Word(string, int);
		
		//function prototypes
		void CountWord(int);
		string GetWord();
		
		//operator overload prototypes
		bool operator < (const Word &rhs) const;
		bool operator == (Word &rhs) const;
		Word operator = (const Word &rhs);

		//ostream overload definition
		friend ostream &operator<< (ostream &strm, Word &inWord)
		{
			//if front lineNumber is 0, just output wordText
			if (inWord.lineNumbers.front() == 0)
			{
				strm << inWord.wordText;
			}
			//otherwise
			else
			{
				//formats how code will look
				if (inWord.count < 10)
				{
				strm << left << setfill('.') << setw(23) << inWord.wordText;
				}
				else if (inWord.count < 100)
				{
				strm << left << setfill('.') << setw(22) << inWord.wordText;
				}
				else if (inWord.count < 1000)
				{
				strm << left << setfill('.') << setw(21) << inWord.wordText;
				}
				else if (inWord.count < 10000)
				{
				strm << left << setfill('.') << setw(20) << inWord.wordText;
				}
				strm << inWord.count;
				strm << ": ";
			
				//this code makes it so duplicate lineNumbers are not outputted
				do
				{
					int temp; // create temp variable
					temp = inWord.lineNumbers.front(); // assign temp to front of queue

					strm << inWord.lineNumbers.front() << " "; // output front of queue
					inWord.lineNumbers.pop(); // pop front
					int temp2 = 0; // create new temp variable
					if (!(inWord.lineNumbers.empty())) // if queue is not empty
						temp2 = inWord.lineNumbers.front(); //assign temp2 to new queue front

					
					while (temp == temp2) //loops while temp is equal to temp 2
					{
						inWord.lineNumbers.pop(); // pop the queue
						if (!inWord.lineNumbers.empty()) // if the queue is not empty
							temp2 = inWord.lineNumbers.front(); // assign temp2 to new queue front
						else
							temp2 = 0;
					}
					

				}while (inWord.lineNumbers.size() > 0);
			}

			return strm;
		}

};

#endif