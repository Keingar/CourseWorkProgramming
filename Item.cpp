#include "Item.h"

Item::Item()
{

	ItemName = "Item";
	defense = 0;
	attackPower = 0;
}

int Item::getDefense()const {
	return defense;
}

int Item::getAttackPower()const {
	return attackPower;
}

std::string Item::getItemName()const {
	return ItemName;
}


void Item::setDefense(int value) {
	defense = value;
}

void Item::setAttackPower(int value) {
	attackPower = value;
}

void Item::setItemName(std::string newName) {
	ItemName = newName;
}

bool Item::validationOfValue(int value) {

	if (value < -1) {
		return false;
	}

	return true;
}