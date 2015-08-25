//Dan Lesko

#ifndef INDEXER_H
#define INDEXER_H
#include <string>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <functional>
#include "BinarySearchTree.h"
#include "MyExceptions.h"

using namespace std;

//Indexer Class Definition
class Indexer
{
	private:
		//Private member variables
		BinarySearchTree<Word> filteredBST;
		BinarySearchTree<Word> indexedBST;
		string datafile;
		string filterfile;

		//Private member function prototypes
		bool FileExists (const char*);
		BinarySearchTree<Word> FileFilterReader(string);
		BinarySearchTree<Word> FileWordReader(string);
		void OutputResults();

	public:
		//Constructor
		Indexer(string, string);
		
		//public member function prototypes
		void DoIndex();
		



};

#endif
