#include "Character.h"

Character::Character() {
	CharacterID = 0; 
	maxHealth = 100;
	characterName = "DeafultName";
	currentHealth = maxHealth;
	strength = 10;
	defense = 5;
}

void Character::setMaxHealth(int value) {
	maxHealth = value;
}

void Character::setCurrentHealth(int value) {
	currentHealth = value;
}


void Character::setDefense(int value) {
	defense = value;
}

void Character::setStrength(int value) {
	strength = value;
}

void Character::SetCharacterName(std::string newName) {
	characterName = newName;
}

std::string Character::getCharacterName() const{
	return characterName;
}

int Character::getMaxHealth() const {
	return maxHealth;
}

int Character::getCurrentHealth() const {
	return currentHealth;
}

int Character::getStrength() const
{
	return strength;
}

int Character::getDefense()const {
	return defense;
}

void Character::setCharacterID(int value) {
	CharacterID = value;
}

int Character::getCharacterID()const {
	return CharacterID;
}

void Character::reset() {
	CharacterID = 0; 
	maxHealth = 100;
	characterName = "DeafultName";
	currentHealth = maxHealth;
	strength = 10;
	defense = 5;
}

bool Character::validationOfValue(int value) {

	if (value <= 0) {
		return false;
	}

	return true;
}

