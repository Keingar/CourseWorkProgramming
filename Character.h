#pragma once
#include <iostream>

class Character {

public:

	Character();
	void setMaxHealth(int value);
	void setStrength(int value);
	void setDefense(int value);
	void SetCharacterName(std::string newName);
	void setCurrentHealth(int value);
	void setCharacterID(int value);
	std::string getCharacterName() const;

	int getMaxHealth()const;
	int getCurrentHealth()const;
	int getStrength()const;
	int getDefense()const;
	int getCharacterID()const;



	void reset();
	bool validationOfValue(int value);

private:
	std::string characterName;
	int CharacterID;
	int maxHealth;
	int strength;
	int currentHealth;
	int defense;
};