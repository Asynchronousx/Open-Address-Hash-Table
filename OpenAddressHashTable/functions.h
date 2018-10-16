#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "class_HashTable.h"

void PrintProgramINFO() {
	std::cout << "*** HASH TABLE: Quadratic Probing / Open Addressing ***" << std::endl;
}

void Menu() {
	std::cout << std::endl;
	std::cout << "Select your Choice!" << std::endl;
	std::cout << "------" << std::endl;
	std::cout << "1. Insert a value." << std::endl;
	std::cout << "2. Search  a value." << std::endl;
	std::cout << "3. Print Dictionary." << std::endl;
	std::cout << "4. Load a pre-made Dictionary." << std::endl;
	std::cout << "5. Erase all the data." << std::endl;
	std::cout << "6. Clean the screen." << std::endl;
	std::cout << "7. EXIT." << std::endl;
	std::cout << "------" << std::endl;
}

//Cleaning the buffer to avoid wrong input crash and problems.
void CleanBuffer() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Modality will represent the modality of the text that will appear on the screen;
//to avoid to create another function for various text output purpose on the screen,
//we're giving here a default variable that will lead the function into the right way.
void inputValidation(int& input, int Modality = 0) {
	if (!Modality) {
		while (!std::cin) {
			std::cout << "Choice not recognized." << std::endl;
			std::cout << "Try again." << std::endl << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "What you would like to do? ";
			std::cin >> input;
			std::cout << std::endl;

		}
	}
	else {
		while (!std::cin) {
			std::cout << std::endl;
			std::cout << "Choice not recognized." << std::endl;
			std::cout << "Do you wish to continue?" << std::endl;
			std::cout << "YES(1) / NO(0) : ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> input;
		}
	}
}

//Function that will be the core of our menu
void Selector(HashMap HashTable) {

	//Variables
	int choice;
	int localChoice;
	int RestartMenu = 0;

	bool Exit = false;
	bool DictionaryInserted = false;
	std::string WordtoInsert;
	std::string WordtoSearch;
	std::string Definition;

	//Choice cin:
	std::cout << "What you would like to do? ";
	std::cin >> choice;
	std::cout << std::endl;

	inputValidation(choice);

	//While cycle, nested with the Switch:
	//While not exit button, keep looping
	while (choice != 7) {
		switch (choice)
		{
		default: //Int Choice not valid
			std::cout << "Choice not recognized." << std::endl;
			std::cout << "Try again." << std::endl << std::endl;
			break;

		case 1: //Insert choice
			std::cout << "Write the word to insert: ";
			std::cin.ignore();
			std::getline(std::cin, WordtoInsert);

			//if no word instered, take the word again
			if (WordtoInsert == "") {
				while (WordtoInsert == "") {
					std::cout << "Can't insert an empty word." << std::endl;
					std::cout << std::endl;
					std::cout << "Write the word to insert: ";
					std::getline(std::cin, WordtoInsert);
				}
			}

			std::cout << "Write it's definition: ";
			std::getline(std::cin, Definition);
			std::cout << std::endl;

			//If no definition inserted, insert a default value
			if (Definition == "") Definition = "EMPTY";

			HashTable.Insert(WordtoInsert, Definition);
			std::cout << "Word Inserted." << std::endl;
			RestartMenu++;
			break;

		case 2: //Search Choice
			std::cout << "Write the word to search: ";
			std::cin >> WordtoSearch;
			std::cout << std::endl;
			HashTable.Search(WordtoSearch);
			RestartMenu++;
			break;

		case 3:
			HashTable.PrintDictionary();
			RestartMenu += 2;
			break;

		case 4: //load a premade dictionary
			std::cout << "Loading a pre-made Dictionary, will erase" << std::endl;
			std::cout << "all your previous HashTable entries and data." << std::endl;
			std::cout << "Do you wish to continue?" << std::endl;
			std::cout << "YES(1) / NO(0) : ";

			std::cin >> localChoice;
			inputValidation(localChoice, 1);

			//While Exit auxiliary value is false (will become
			//true only when the user make some choice 
			while (!Exit) {
				//If the premade dictionary is not inserted, or we want to go
				//back at every nested level of the loop:
				if (!DictionaryInserted || localChoice == 0) {
					if (localChoice == 1) {
						HashTable.PreMadeDictionary(DictionaryInserted);
						RestartMenu += 2;
						Exit = true;
					}
					else if (localChoice == 0) {
						std::cout << "Operation cancelled." << std::endl;
						Exit = true;
					}
					else {
						std::cout << "Choice not recognized." << std::endl << std::endl;
						std::cout << "Do you wish to continue?" << std::endl;
						std::cout << "YES(1) / NO(0) : ";

						std::cin >> localChoice;
						inputValidation(localChoice, 1);
					}
				}
				//Else, the dictionary is already inserted:
				else if (DictionaryInserted) {
					std::cout << std::endl << "------" << std::endl;
					std::cout << "Pre-Made Dictionary ";
					std::cout << "Already inserted." << std::endl;
					std::cout << "Do you want to ";
					std::cout << "re-load the Dictionary ? " << std::endl;
					std::cout << "All the data will be wiped ";
					std::cout << "and restored with Default values." << std::endl;
					std::cout << "------" << std::endl << std::endl;
					std::cout << "YES(1) / NO(0) : ";

					std::cin >> localChoice;
					inputValidation(localChoice, 1);

					if (localChoice == 1) {
						HashTable.PreMadeDictionary(DictionaryInserted);
						Exit = true;
					}
					else if (localChoice == 0) {
						std::cout << "Operation cancelled." << std::endl;
						Exit = true;
					}
					else {
						std::cout << "Choice not recognized." << std::endl;
						std::cout << "Do you wish to continue?" << std::endl;
						std::cout << "YES(1) / NO(0) : ";

						std::cin >> localChoice;
						inputValidation(localChoice, 1);

					}

					RestartMenu += 2;

				}
			}

			break;

		case 5:
			std::cout << "Erase will delete all the entries" << std::endl;
			std::cout << "into your Dictionary HashTable." << std::endl;
			std::cout << "Do you wish to continue?" << std::endl;
			std::cout << "YES(1) / NO(0) : ";

			std::cin >> localChoice;
			inputValidation(localChoice, 1);

			//While Exit auxiliary value is false (will become
			//true only when the user make some choice 
			while (!Exit) {
				if (localChoice == 1) {
					HashTable.EraseAll();
					std::cout << "Table resetted." << std::endl;
					RestartMenu++;
					DictionaryInserted = false;
					Exit = true;
				}
				else if (localChoice == 0) {
					std::cout << "Operation cancelled." << std::endl;
					Exit = true;
				}
				else {
					std::cout << "Choice not recognized." << std::endl << std::endl;
					std::cout << "Do you wish to continue?" << std::endl;
					std::cout << "YES(1) / NO(0) : ";

					std::cin >> localChoice;
					inputValidation(localChoice, 1);
				}
			}

			break;

		case 6:
			system("CLS");
			PrintProgramINFO();
			Menu();
			RestartMenu = 0;
			break;

		} //end of the switch

		  //After every iteration of the switch, 
		  //if the values of restart menu is equal to 4, 
		  //it will be re-printed for the comfort of the user.
		if (RestartMenu == 4) {
			std::cout << std::endl;
			std::cout << "...Re-Printing the Menu: " << std::endl;
			Menu();
			RestartMenu = 0;
		}

		//Resetting the exit as false 
		Exit = false;
		std::cout << std::endl;
		std::cout << "What would you like to do? ";
		std::cin >> choice;
		std::cout << std::endl;
		inputValidation(choice);

	}

	std::cout << std::endl << "Exiting from the Vocabulary..." << std::endl;
}

