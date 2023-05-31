	#pragma once

	#include <iostream>
	#pragma once


	class Item
	{

	public:

		Item();

		int ItemID;

		int getDefense()const;
		int getAttackPower()const;

		std::string getItemName()const;

		bool validationOfValue(int value);

		void setDefense(int value);
		void setAttackPower(int value);
		void setItemName(std::string newName);
		
	private:
		int defense;
		int attackPower;

		std::string ItemName;


	};