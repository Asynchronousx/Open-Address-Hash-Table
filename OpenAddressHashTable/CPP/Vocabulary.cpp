// OpenAddressHashTable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "class_HashTable.h"
#include "functions.h"


int main()
{
	HashMap Dictionary(16);
	PrintProgramINFO();
	Menu();
	Selector(Dictionary);
}

