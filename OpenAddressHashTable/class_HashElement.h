#pragma once
#include <iostream>

//Here we got our Hash Element class: 
//An element is composed by a value that represent the data, and a key that represent where its stored.

class Element {
private:
	std::string Word;
	std::string Definition;
	int HashKey;

public:
	//Constructor:
	Element() { //Default
		this->Word = "EMPTY";
		this->Definition = "EMPTY";
		this->HashKey = -1;
	}
	~Element() { ; } //Destructor

	//Methods: Set
	void setKey(int Key) { this->HashKey = Key; }
	void setWord(std::string Word) { this->Word = Word; }
	void setDefinition(std::string Definition) { this->Definition = Definition; }
	
	//set all the values
	void setAll(int Key, std::string Word, std::string Definition) {
		this->HashKey = Key;
		this->Word = Word;
		this->Definition = Definition;
	}

	//Methods: Get
	int getKey() { return HashKey; }
	std::string getWord() { return Word; }
	std::string getDefinition() { return Definition; }
	
};
	