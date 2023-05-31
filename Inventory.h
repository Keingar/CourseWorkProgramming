
#include <iostream>
#include "Character.h"
#include "Item.h"
#pragma once


class Inventory
{

public:

	Inventory();

	class Item ITem;
	
	int CharacterOwnerID;

	bool operator==(const Inventory& other) const;
};