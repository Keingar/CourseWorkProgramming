#include <iostream>
#include "DataManager.h"
#pragma once
class UI {
	
public:

	UI();

	UI& operator=(UI&&) = delete;
	UI(const UI&) = delete;
	UI& operator=(const UI&) = delete;

	int getUserInput();
	void clearConsole();
private:
	int selectedOption;

	void drawMenu();
	void drawMenuAddCharacter();
	void drawMenuRemoveCharacter();
	void drawMenuAddItem();
	void drawMenuToChooseCharacter();
	void drawMenuDeleteItemFromCharacter();

	void useMenu();
	void useMenuAddCharacter();
	void useMenuRemoveCharacter();
	void useMenuToChooseCharacter();
	void useMenuToAddItem();
	void useMenuDeleteItemFromCharacter();
	void askForSortOptions();

	void askForFilterOptions();
	void printCharacters(const std::vector<Character>& ListOfCharacter);
	void printItems();

	DataManager DataBase;
protected: 


	std::vector<std::string> menuOptions = {
		"Add character",
		"Add Item to character",
		"Remove Character",
		"Remove Item From Character",
		"Sort",
		"Filter",
		"Print characters",
		"Print Items of characters",
		"Quit"
	};
	std::vector<std::string> CharacterCharacterstics = {
		"set Character name",
		"set maxHealth",
		"set Strenght",
		"set Defense",
		"Finish",
		"Cancel"
	};
	std::vector<std::string> ItemCharacterstics = {
		"Set Name",
		"Set Defense",
		"Set Attack Power",
		"Finish",
		"Cancel"
	};
};