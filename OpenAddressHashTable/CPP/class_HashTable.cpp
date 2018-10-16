#include "stdafx.h"
#include "class_HashTable.h"
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

//Function that insert an element into our HashTable
void HashMap::HashInsert(std::vector<Element> HashTable, std::string Key,std::string Definition) {
	//Declaring a new Element
	Element newElement;
	//For all the size of the HashTable:
	//We need to iterate at least M times (HashTable size)
	//To find the right position for a new Element. If a position cannot
	//be found, the table is full. 
	for (size_t i = 0; i < HashTable.size(); i++) {
		//Quadratic probe to find a right index and the HashValue
		std::pair<int,int> IndexKeyPair = QuadraticHash(Key, i);
		int Index = IndexKeyPair.first;
		int HashValue = IndexKeyPair.second;

		//If the element got the word "EMPTY", that means that
		//the position to insert the new element is available
		if (getElement(Index).getWord() == "EMPTY") {
			//check the load factor first: if it exceed 0.5, 
			//the table needs to be rehashed, otherwise the new 
			//element insertion will not be granted.
			if (getLoadFactor() > 0.5) {
				ReHash();
			}
			else { //if the LoadFactor is not a problem, insert the new
				   //element with no problem, and update the load factor aswell.
				newElement.setAll(HashValue, Key, Definition);
				setElement(newElement, IndexKeyPair.first);
				setLoadFactor(ElementCount() / float(getTableSize()));
				return;
			}
		}
	}

	//If the for finishes, that means that we've exceed the size.
	if (ElementCount() == getTableSize()) {
		ExceededINFO(Key);
		return;
	}
}

//Function that given a Key, it will found the Key into our dictionary
//With a list of the most similar words.
void HashMap::HashSearch(std::vector<Element> HashTable, std::string Key) {

	//Not found at the beginning
	bool Found = false;

	//Pair to store index and hash value
	std::pair<int, int> IndexKeyPair;

	//For all the element into our Hash Table
	for (size_t i = 0; i < getTableSize(); i++) {
		//Quadratic probe to find a right index and the HashValue
		IndexKeyPair = QuadraticHash(Key, i);
		int Index = IndexKeyPair.first;
		int HashValue = IndexKeyPair.second;

		//If the element at that index is not empty (because from theory, 
		//if it is, this means that even in the next slot we 
		//will not find anything.
		if (HashTable.at(Index).getWord() != "EMPTY") {

			//If the element at the index is equal to the search Key, and if
			//the element is not been visited (because if we got two or more equal element
			//with different meaning in the hashtable, we need to know which one we've visited)
			//then print the information found, and set the Found value as TRUE, that means
			//the LCS will be executed.

			if (HashTable.at(Index).getWord() == Key) {
				//print info
				FoundINFO(getTable().at(Index).getWord(), getTable().at(Index).getDefinition(), Index, HashValue, 1);
				//true if we find at least one occurence of the word.
				Found = true;			
			}
		}
		//Else the element with that hash key is equal to EMPTY in our hash table, 
		//we dont need to search anymore, break the cycle.
		else {
			break;
		}
	}

	//Element not found, we need to find the best LCS in the table:
	if (!Found) {
		//print that nothing is found
		FoundINFO();

		//if the table isn't empty 
		if (ElementCount() != 0) {

			//Vector to store all the occurence
			std::vector<std::string> AllOccurrence;

			int bestOccurrence = 0;
			//best occurrence string found
			std::string bestString;

			//for the size of the Hash Table
			for (size_t i = 0; i < HashTable.size(); i++) {
				//If the HashTable cell is not empty 
				if (HashTable.at(i).getWord() != "EMPTY") {
					//calculate LCS of the word of that index (i) , and the not found given key 
					std::pair<std::vector<int>, std::vector<char>> LCSContainer = LCS(HashTable.at(i).getWord(), Key);

					//In the LCS Array, the LAST VALUE into the LAST CELL, identify the number of 
					//the equal char occurrence between two given string. So, in each cycle, we ask 
					//the program: is the new LCS better than the last one? (bestOccurence store the 
					//equal character values of each iteration).
					//If the new LCS is better than the last one
					if (LCSContainer.first.at(LCSContainer.first.size() - 1) >= bestOccurrence) {
						//New best occurence is the number of the equal character between these two strings
						bestOccurrence = LCSContainer.first.at(LCSContainer.first.size() - 1);
						//Best occurence string is the string at the current index
						bestString = HashTable.at(i).getWord();
						//Push the string into the occurrence vector to take 
						//track of all of them.
						AllOccurrence.push_back(bestString);
					}
				}
			}

			//If there's at least ONE occurence found:
			if (!AllOccurrence.empty()) {
				//print that word and all the occurrence found
				askLCSquestion(AllOccurrence);
			}
		}
	}
	else //nothing more to do, return 
		return;
		
}

//Quadratic Hash Probe function
std::pair<int, int> HashMap::QuadraticHash(std::string Key, int Index) {

	//Quadratic Probe Formula: h(k,i) = (h1(k)+ c1i + c2i^2) mod m,
	//where c1 and c2 are arbitrary values.
	int C1 = 0;
	int C2 = 1;
	int Hk = auxHash(Key);
	
	//Square the index for the next step 
	int SquaredIndex = pow(Index, 2);
	//Probe formula: h(k,i) = (h1(k)+ c1i + c2i^2) mod m
	int newIndex = (Hk + C1*Index + C2*SquaredIndex) % getTableSize();

	return std::make_pair(newIndex, Hk);
}

//Our AUX h1(k) hash function. 
//This function get a string in input, and hash its value, 
//returning that to the Linear or Quadratic Probe, that will
//use this value in their definitions.
int HashMap::auxHash(std::string Key) {
	int HashCount = 0; //our K
	for (size_t i = 0; i < Key.size(); i++) {
		HashCount += Key.at(i);
	}

	return HashCount;
}

//Function that counts the number of element into our HashTable.
int HashMap::ElementCount() {
	int numberOf = 0;
	for (auto x : getTable()) {
		if (x.getKey() != -1)
			numberOf++;
	}
	return numberOf;
}

//Function that reHash the table if the LF > 0.5.
//ReHash a table is necessary when the Load Factor reaches 0.5,
//because past this value, we cannnot guarantee the succession of the
//next insertion into the hash table, because of the collisions.
void HashMap::ReHash() {
	std::vector<Element> HashTableCopy = getTable();
	//Create a new HashTable double the size of the original
	std::vector<Element> ReHashedTable(getTableSize() * 2); 
	std::vector<Element>::iterator HashIterator;

	//set the reHashed table as the new HashTable
	setTable(ReHashedTable);

	//set the new LoadFactor
	setLoadFactor(ElementCount() / float(getTableSize()));

	//for all the lenght of the current HashTable
	for (HashIterator = HashTableCopy.begin(); HashIterator != HashTableCopy.end(); HashIterator++) {
		//if the element is not empty 
		if ((*HashIterator).getWord() != "EMPTY") {
			//Insert again the element into our new table:
			//because the new size of the rehashed Hash Table,
			//will cause a new value for the index of the rehashed
			//elements.
			HashInsert(ReHashedTable, (*HashIterator).getWord(), (*HashIterator).getDefinition());
		}
	}
}


//Function that load a premade dictionary stored into the default
//folder of this program.
//The dictionary is composed by EVERY alphabet letter, five word for each letter.
void HashMap::LoadDictionary() {
	
	//Resetting the hash table
	Erase();

	std::ifstream fin;

	do { //try to open the file
		fin.clear(); //clear the input
		fin.open("Dictionary.txt"); //open the file
	} while (!fin); //while not opened

	std::string Word;
	std::string Definition;

	//while the input is good 
	while (fin.good()) {
		//get the word
		std::getline(fin, Word);
		//uppercase the first letter
		Word.at(0) = toupper(Word.at(0));
		//get the definition
		std::getline(fin, Definition);
		//uppercase the first letter
		Definition.at(0) = toupper(Definition.at(0));
		//insert word and definition into the HashTable.
		HashInsert(getTable(), Word, Definition);
	}

	//close the input
	fin.close();

}

//Reset the hash table
void HashMap::Erase() {
	std::vector<Element> ResetHT(16);
	setTable(ResetHT);
	setLoadFactor(0);
}



//--------------------------------
//PRINT FUNCTION: 

void HashMap::PrintTableINFO() {

	//if no element into our HashTable, then print is empty
	if (ElementCount() == 0) {
		std::cout << "Dictionary is empty!" << std::endl << std::endl;
	}
	else { //otherwise
		//Actual letter being printed, initially is none.
		char ActualLetter = '0'; 

		//Assign the Actual HashTable to a new one we'll sort		
		std::vector<Element> SortedHashTable = getTable();	
		//Sort the table with a std::sort function and a lambda function,
		//that will sort the HashTable in an alphabetical crescent way
		std::sort(SortedHashTable.begin(), SortedHashTable.end(), [](Element a, Element b) { return a.getWord() < b.getWord(); });

		//declaring an iterator
		std::vector<Element>::iterator DictionaryIT; 
		std::cout << "Printing the Dictionary:" << std::endl;
		
		//for all the element into our HashTable
		for (DictionaryIT = SortedHashTable.begin(); DictionaryIT != SortedHashTable.end(); DictionaryIT++) {
			//if the first letter of the word we're analyzing in that iteration is different from the variable
			//ActualLetter (so we're moving from a letter to another, from example from A to B) and the current
			//analyzed element is not empty.
			//We are doing this to print automatically the letter of the alphabet considered.
			if ((*DictionaryIT).getWord().at(0) != ActualLetter && (*DictionaryIT).getWord() != "EMPTY") {
				std::cout << std::endl;
				//Then the ActualLetter is now the current word's first letter
				ActualLetter = (*DictionaryIT).getWord().at(0);
				//print the ActualLetter to inform the user we're analyzing
				//words with that letter
				std::cout << "Letter " << ActualLetter << ":" << std::endl;
			}

			//if the analyzed element is not empty, 
			if((*DictionaryIT).getWord() != "EMPTY")
			//print  the element 
			std::cout << (*DictionaryIT).getWord() << std::endl;
		}
		
	}
}


//Function that shows up information about when the table get overflowed
void HashMap::ExceededINFO(std::string Key) {
	std::cout << "Size Exceeded." << std::endl;
	std::cout << "Element not Inserted: " << Key << std::endl;
}

//Funcion that show info about a found element
void HashMap::FoundINFO(std::string Key, std::string Definition, int Index, int HashValue, int FoundSTATE) {
	//if the letter is found
	if (FoundSTATE) {
		std::cout << std::endl;
		std::cout << "Printing Information:" << std::endl;
		std::cout << "------" << std::endl;
		std::cout << "State: " << "FOUND" << std::endl;
		std::cout << "Key: " << Key << std::endl;
		std::cout << "Definition: " << Definition << std::endl;
		std::cout << "Index: " << Index << std::endl;
		std::cout << "Hash Value: " << HashValue << std::endl;
		std::cout << "------" << std::endl;
	}
	else { //otherwise, no occurrence
		std::cout << "------" << std::endl;
		std::cout << "State: " << "NOT FOUND" << std::endl;
		std::cout << "------" << std::endl << std::endl;
	}
}


//Function that asks about a successful LCS between two strings;
//It will print all the occurrence found, and will also ask
//If the string given matches with the desires of the user, 
//the string will be printed on the screen, otherwise it goes back.
void HashMap::askLCSquestion(std::vector<std::string> AllOccurrence) {
	//Variables
	int choice;
	bool Exit = false;
	std::string Key = AllOccurrence.at(AllOccurrence.size() - 1);

	//While the user doesn't make the right choice, exit will remain false and the cycle
	//will iterate.
	while (!Exit) {

		printAllLCS(AllOccurrence);
		std::cout << "Most similar occurrence found: " << Key << std::endl;
		std::cout << "Did you mean: " << Key << " ?" << std::endl;
		std::cout << "YES(1) / NO(0): ";
		std::cin >> choice;
		std::cin.clear(); // clean the buffer 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clean the buffer 

																			//If is the word the user was looking for
		if (choice == 1) {
			std::vector<Element> HashTableTMP = getTable();
			std::vector<Element>::iterator it;

			//Iterate in all the table to found that element 
			for (it = HashTableTMP.begin(); it != HashTableTMP.end(); it++) {
				//if found 
				if ((*it).getWord() == Key) {
					//take the index of that element 
					int Index = std::distance(HashTableTMP.begin(), it);
					//and pass it to the function that will print the information about
					FoundINFO(getTable().at(Index).getWord(), getTable().at(Index).getDefinition(), Index, auxHash(Key), 1);

				}
			}

			//now we can exit the program (we'll break the cycle in the next iteration)
			Exit = true;

		}
		//otherwise, if not the word we were looking for, go back 
		else if (choice == 0) {
			std::cout << "Going back..." << std::endl << std::endl;
			Exit = true;
		}
		//choice is not recognized, and the cycle will not break.
		else {
			std::cout << "Choice not recognized." << std::endl << std::endl;
		}
	}
}


//Function that help us printing all the LCS string occurrence found.
void HashMap::printAllLCS(std::vector<std::string> AllOccurrence) {
	std::vector<std::string>::reverse_iterator it;
	std::cout << "All occurrence found: " << std::endl;
	for (it = AllOccurrence.rbegin(); it != AllOccurrence.rend(); it++) {
		std::cout << (*it) << std::endl;
	} std::cout << std::endl;
}


//---------------------------------------------------
//LCS FUNCTIONS: 

//Function that calculate LCS between two given strings.
std::pair<std::vector<int>, std::vector<char>> HashMap::LCS(std::string X, std::string Y) {

	int m = X.length() + 1; //ROW
	int n = Y.length() + 1; //COLUMN

	//Typical DP approach: 
	//we store one table for our main purpose of calculating
	//the optimal substructure (and so the optimal solution to the subproblems)
	//and another table as the size of the first one, to store the "path" in this case,
	//but work generally for any DP where we want to store a solution.
	std::vector<int> LCSTable(m*n);
	std::vector<char> LCSPrintTable(m*n, '0');

	//Set first row and first column value to zero:

	for (size_t i = 0; i < m; i++) {
		//first element of every row at column 0 is setted to 0 (case when j = 0)
		LCSTable.at(n*i + 0) = 0; 
	}

	for (size_t j = 0; j < m; j++) {
		//first element of every columun at row 0 is setted to 0 (case when i = 0);
		LCSTable.at(n * 0 + j) = 0; 
	}

	//for the size of the first string 
	for (size_t i = 1; i < m; i++) {
		//for the size of the second string 
		for (size_t j = 1; j < n; j++) {
			//First case: Xi = Yi (the character are equal)
			if (X.at(i - 1) == Y.at(j - 1)) { 
				//The new value is equal to the diagonal+1 ( c[i-1,j-1]+1))
				LCSTable.at(n*i + j) = LCSTable.at(n*(i - 1) + j - 1) + 1; 
				//Update B with DIAGONAL arrow
				LCSPrintTable.at(n*i + j) = 'D'; 
			}
			//Second case: Xi != Yi, so they're not equal: 
			//also we're in the case where Xi-1, Yj.
			//Then we'll take the value UP to this cell (in the row-1, but same column)
			//and put that into our actual cell. Note that this is the default choosen 
			//value for completing the LCS matrix. (Xi-1, Yj)
			else if (LCSTable.at(n*(i - 1) + j) >= LCSTable.at(n*i + (j - 1))) {
				//The new value is equal to the up cell value (c[i-1,j])
				LCSTable.at(n*i + j) = LCSTable.at(n*(i - 1) + j);
				//Update B with UP arrow
				LCSPrintTable.at(n*i + j) = 'U'; 
			}
			//Second Case: Xi != Yi, but Xi, Yj-1.
			//This is equal to the above case, but we're considering Yj-i
			//instead of Xi-1.
			else {
				//The new value is equal to the left cell value(c[i,j-1])
				LCSTable.at(n*i + j) = LCSTable.at(n*i + j - 1); 
				//Update B with LEFT arrow
				LCSPrintTable.at(n*i + j) = 'L'; 
			}
		}
	}

	//Return the container of table C and table B.
	return std::make_pair(LCSTable, LCSPrintTable); 
}

//Function that prints the LCS between two string.
void HashMap::printLCS(std::vector<char> LCSPrintTable, std::string X, int Row, int Col, int Width) {

	//Base case: empty string 
	//if row or column are empty
	if (Row == 0 || Col == 0) { 
		//return to the precedent stack call 
		return;
	}

	//If we found a diagonal arrow
	if (LCSPrintTable.at(Width*Row + Col) == 'D') { 
		//Go up in the diagonal c[i-1,j-1]
		printLCS(LCSPrintTable, X, Row - 1, Col - 1, Width); 
		//***Exiting from the recursion***
		//in this case, we use Row-1 as the index to print the i-th letter of the string (after the recursion occurred)
		std::cout << X.at(Row - 1); 
	}
	//If we found an up arrow
	else if (LCSPrintTable.at(Width*Row + Col) == 'U') { 
		//Go up in the table c[i-1,j]
		printLCS(LCSPrintTable, X, Row - 1, Col, Width); 
	}
	//Else, we found a left arrow
	else { 
		//Go left in the table c[i,j-1]
		printLCS(LCSPrintTable, X, Row, Col - 1, Width); 
	}

}


//Methods: Set
void HashMap::setElement(Element toInsert, int Index) {
	HashTable.at(Index) = toInsert;
}

void HashMap::setTable(std::vector<Element> HashTable) {
	this->HashTable = HashTable;
}

void HashMap::setLoadFactor(float LoadFactor) { 
	this->LoadFactor = LoadFactor; 
}

//Private Methods: Get
float HashMap::getLoadFactor() {
	return LoadFactor; 
}

int HashMap::getTableSize() {
	return HashTable.size(); 
}

std::vector<Element> HashMap::getTable() {
	return HashTable; 
}

Element HashMap::getElement(int IndexDesired) {
	return HashTable.at(IndexDesired); 
}


//Helper Functions: 
//Here we use some helper function to grant the access to private
//methods in the class.

//Helper function for the insert into the hash table.
void HashMap::Insert(std::string Word, std::string Definition) {
	//Capitalize first Letter of the word
	Word.at(0) = toupper(Word.at(0));
	//Lower the rest 
	for (int i = 1; i < Word.length(); i++) Word.at(i) = tolower(Word.at(i));

	//Capitalize first Letter of the definition
	Definition.at(0) = toupper(Definition.at(0));

	HashInsert(getTable(), Word, Definition);
}

//Helper function for the searc into the hash table.
void HashMap::Search(std::string Word) {
	//Capitalize first Letter
	Word.at(0) = toupper(Word.at(0));
	//Lower the rest 
	for (int i = 1; i < Word.length(); i++) Word.at(i) = tolower(Word.at(i));

	HashSearch(getTable(), Word);
}

//Helper function for printing the dictionary.
void HashMap::PrintDictionary() {
	PrintTableINFO();
}


//Helper function to load a premade dictionary into the hashtable.
void HashMap::PreMadeDictionary(bool& DictionaryInserted) {
	std::cout << std::endl << "Loading a pre-made dictionary..." << std::endl;
	LoadDictionary();
	std::cout << "Dictionary correctly loaded." << std::endl << std::endl;
	DictionaryInserted = true;
}

//Helper function that reset the table
void HashMap::EraseAll() {
	Erase();
}
