#pragma once
#include "class_HashElement.h"
#include <iostream>
#include <vector>
#include <string>

//This is our HashTable.
//We use open address method, that means that there's no pointer and lists, but all the values
//are stored directly into our arrays, with 3 different methods: linear, quadratic probe and double hashing.
//In this HashTable we choose Quadratic Probe.
//In the Open address HashTable, we redefine our Hash Function h to extends itself with a new parameter, i,
//that represent the actual probe index we're searching in -> h(k,i)
//So, the domain is now: h: U X {0,1,2...m-1} -> {0,1,2...m-1}. (so h: universe of key -> available position)
//also we'll need an auxiliar hash function to help us determining the hash value of a certain value, and we use h1(k) to 
//do that. 

class HashMap {
private:
	//Our HashTable
	std::vector<Element> HashTable;
	float LoadFactor;

	//Define private functions:
	std::pair<int, int> QuadraticHash(std::string Key, int Index);
	int auxHash(std::string Key);
	int ElementCount();
	void HashSearch(std::vector<Element> HashTable, std::string Key);
	void HashInsert(std::vector<Element> HashTable, std::string Key, std::string Definition);
	void ReHash();
	void LoadDictionary();
	void Erase();

	//Print Functions
	void PrintTableINFO();
	void ExceededINFO(std::string Key);
	void FoundINFO(std::string Key = "EMPTY", std::string Definition = "EMPTY", int Index = 0, int HashValue = 0, int FoundSTATE = 0);
	void askLCSquestion(std::vector<std::string> AllOccurrence);
	void printAllLCS(std::vector<std::string> AllOccurrence);

	//LCS Function
	std::pair<std::vector<int>, std::vector<char>> LCS(std::string X, std::string Y);
	void printLCS(std::vector<char> LCSPrintTable, std::string X, int Row, int Col, int Width);

	//Private Methods: Set
	void setElement(Element toInsert, int Index);
	void setTable(std::vector<Element> HashTable);
	void setLoadFactor(float LoadFactor);

	//Private Methods: Get
	float getLoadFactor();
	int getTableSize();
	std::vector<Element> getTable();
	Element getElement(int IndexDesired);


public:
	//Constructor and destructor:
	HashMap(int Size) :HashTable(Size), LoadFactor(0) { ; } 
	~HashMap() { ; }


	//Helper Functions: 
	//Here we use some helper function to grant the access to private
	//methods in the class.

	//Helper function for the insert into the hash table.
	void Insert(std::string Word, std::string Definition);

	//Helper function for the searc into the hash table.
	void Search(std::string Word);

	//Helper function for printing the dictionary.
	void PrintDictionary();

	//Helper function to load a premade dictionary into the hashtable.
	void PreMadeDictionary(bool& DictionaryInserted);

	//Helper function that reset the table
	void EraseAll();
};