#include <vector>
#include "Inventory.h"
#include "Character.h"
#pragma once


class DataManager
{

public:

	DataManager();
	~DataManager();
	
	DataManager& operator=(const DataManager&) = delete; //I don't like warnings

	std::vector<class Character> characterList;
	std::vector<class Inventory> inventoryList; // characterList separate because in invetory list characters can be repeated but Items not
	
	int generateCharacterID();
	int generateItemID();
	int savedChoice; // to choose between menu addItem or removeItemFromCharacter menu
	void deleteCharacterFromFile(int characterID);

	Character NewCharacter;
	Item newItem;
	Character ChosenCharacter;
	Item ChosenItem;

	Character getCharacterByID(int characterID);

	void writeToFileCharacters();
	void readFromFileCharacters();

	void writeToFileItems();
	void readFromFileItems();

	void sortCharacters(bool sortByName, bool sortByStrength);

	std::vector<Character> filterCharacters(bool enableHealthFilter, bool enableStrengthFilter, bool enableItemCountFilter);

private: 

	const std::string fileNameCharacter = "characterList.bin";
	const std::string fileNameItems = "ItemList.bin";


};