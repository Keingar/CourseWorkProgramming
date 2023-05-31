#include <string>
#include <sstream>
#include <cstdlib>
#include <Windows.h>
#include <iomanip>

#include "UI.h"
#include "Item.h"

UI::UI() {
    selectedOption = 0;
    drawMenu();
}

void UI::drawMenu()
{
    clearConsole();
    for (unsigned i = 0; i < menuOptions.size(); ++i)
    {
        if (i == unsigned(selectedOption))
        {
            std::cout << "===============" << std::endl;
            std::cout << menuOptions[i] << std::endl;
            std::cout << "===============" << std::endl;
            continue;
        }

        if (i - 1 != unsigned(selectedOption)) {
            std::cout << std::endl;
        }

        std::cout << menuOptions[i] << std::endl;

    }
    useMenu();

}

void UI::drawMenuAddCharacter() {
    clearConsole();
    std::cout << "It's not necessary to set all parameters." << std::endl;
    std::cout << "If you don't set something then we will use default value" << std::endl;
    std::cout << "but we highly recommend to set al least character name" << "\n\n";
   
    for (unsigned i = 0; i < int(CharacterCharacterstics.size()); ++i)
    {
        if (i == unsigned(selectedOption))
        {
            std::cout << "===============" << std::endl;
            std::cout << CharacterCharacterstics.at(i) << std::endl;
            std::cout << "===============" << std::endl;

            continue;
        }

        if (i - 1 != unsigned (selectedOption)) {
            std::cout << std::endl;
        }

        std::cout << CharacterCharacterstics[i] << std::endl;

    }
    useMenuAddCharacter();
}
void UI::useMenu() {
    bool menuActive = true;

    int userInput = getUserInput();

    if (selectedOption < 0)
    {
        selectedOption = 0;
    }

    while (menuActive)
    {
        // Get user input

        switch (userInput)
        {
        case 'w':  // Move up in the menu
            if (selectedOption > 0)
                selectedOption--;
                userInput = 0;
                drawMenu();
            break;
        case 's':  // Move down in the menu
            if (selectedOption < int(menuOptions.size()) - 1)
                selectedOption++;
                userInput = 0;
                drawMenu();
            break;
        case 13:  // Select current option
            // Perform the action based on the selectedOption
            switch (selectedOption)
            {
            case 0:
                // Handle "Add character" option
                selectedOption = 0;
                userInput = 0;
                menuActive = false;
                drawMenuAddCharacter();
                break;
            case 1:
                // Handle "Add Item to character" option
                selectedOption = 0;
                userInput = 0;
                menuActive = false;
                DataBase.savedChoice = 0;
                drawMenuToChooseCharacter();
                break;
            case 2:
                // Handle "Remove Character" option
                userInput = 0;
                selectedOption = 0;
                menuActive = false;
                
                drawMenuRemoveCharacter();
                break;
            case 3:    // Handle "Remove Item From Character" option
                selectedOption = 0;
                userInput = 0;
                menuActive = false;
                DataBase.savedChoice = 1;
                drawMenuToChooseCharacter();

                break;
            
            case 4:
                // Handle "Sort" option
                clearConsole();
                askForSortOptions();
                printCharacters(DataBase.characterList);
                break;
            case 5:
                // Handle "Filter" option
                clearConsole();
                askForFilterOptions();
                break;
            case 6:
                // Handle "Print characters" option
                printCharacters(DataBase.characterList);
                break;
            case 7:
                // Handle "Print Items of characters" option
                printItems();
                break;
            case 8:
                // Handle "Quit" option
                DataBase.~DataManager();
                exit(0);
            default:
                break;
            }
            break;
        default:
            useMenu();
            break;
        }
    }
}

void UI::useMenuAddCharacter() {
    bool validationCheck = false;
    bool characterMenuActive = true;
    int userInput = getUserInput();
    std::string NewName;
    

    while (characterMenuActive)
    {
        // Get user input

        switch (userInput)
        {
        case 'w':  // Move up in the menu
            if (selectedOption > 0)
                selectedOption--;
            userInput = 0;
            drawMenuAddCharacter();
            getUserInput();
            break;
        case 's':  // Move down in the menu
            if (selectedOption < int(CharacterCharacterstics.size()) - 1)
                selectedOption++;
            userInput = 0;
            drawMenuAddCharacter();
            getUserInput();
            break;
        case 13:  // Select current option
            switch (selectedOption)
            {
            case 0:
                // Handle "set Character name" option
                clearConsole();
                std::cout << "Write Name for Character ";
                std::cin >> NewName;
                DataBase.NewCharacter.SetCharacterName(NewName);
                drawMenuAddCharacter();
                break;
            case 1:
                // Handle "set maxHealth" option
                clearConsole();
                int newMaxHealth;
                
                std::cout << "Write new maxHealth ";
                std::cin >> newMaxHealth;

                while (!validationCheck)
                {
                    validationCheck = DataBase.NewCharacter.validationOfValue(newMaxHealth);
                    if (validationCheck) {
                        DataBase.NewCharacter.setMaxHealth(newMaxHealth);
                    }
                    else {

                        std::cout << "Max Health must be more than 0 \n";
                        std::cin >> newMaxHealth;
                    }
                    DataBase.NewCharacter.setCurrentHealth(newMaxHealth);
                };
                drawMenuAddCharacter();
                break;
            case 2:
                clearConsole();
                
                int newstrenght;

                std::cout << "Write new new strenght ";
                std::cin >> newstrenght;

                while (!validationCheck)
                {
                    validationCheck = DataBase.NewCharacter.validationOfValue(newstrenght);
                    if (validationCheck) {
                        DataBase.NewCharacter.setStrength(newstrenght);
                    }
                    else {

                        std::cout << "Strenght must be more than 0 \n";
                        std::cin >> newstrenght;
                    }
                };

                drawMenuAddCharacter();
                // Handle "set Strenght" option
                break;
            case 3:
                clearConsole();
                
                int newDefense;

                std::cout << "Write new new Defense ";
                std::cin >> newDefense;

                while (!validationCheck)
                {
                    validationCheck = DataBase.NewCharacter.validationOfValue(newDefense);
                    if (validationCheck) {
                        DataBase.NewCharacter.setDefense(newDefense);
                    }
                    else {

                        std::cout << "Defense must be more than 0\n";
                        std::cin >> newDefense;
                    }
                };

                drawMenuAddCharacter();
                // Handle "set Defense" option
                break;
            case 4:
                clearConsole();
                
                DataBase.NewCharacter.setCharacterID(DataBase.generateCharacterID());
                DataBase.characterList.push_back(DataBase.NewCharacter);
                std::cout << "You have successfully added a character! Press anything to continue";
                getUserInput(); // yes I didn't save return because I don't need it here I use getUserInput only because I need to wait at that moment for input
                selectedOption = 0;
                characterMenuActive = false;
                drawMenu();
                // Handle "Finish" option
                break;
            case 5:
                // Handle "Cancel" option
                characterMenuActive = false;
                clearConsole();
                selectedOption = 0;
                drawMenu();
                break;
            default:
                break;
            }
            break;
        default:
            useMenuAddCharacter();
            break;
        }
    }
}


int UI::getUserInput() {
    // Disable console input echoing and line input
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    unsigned long prevMode = 0;
    GetConsoleMode(hStdin, &prevMode);
    SetConsoleMode(hStdin, prevMode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

    unsigned long numEvents = 0;
    INPUT_RECORD inputRecord;
    do {
        // Read console input until a key event is encountered
        ReadConsoleInput(hStdin, &inputRecord, 1, &numEvents);
    } while (inputRecord.EventType != KEY_EVENT || !inputRecord.Event.KeyEvent.bKeyDown);

    // Restore the console input mode
    SetConsoleMode(hStdin, prevMode);

    // Return the ASCII value of the pressed key
    return (int)inputRecord.Event.KeyEvent.uChar.AsciiChar;
}


void UI::clearConsole()
{
   std::system("cls");
}

void UI::printCharacters(const std::vector<Character>& ListOfCharacter) {
    clearConsole();

    // Set the maximum width for the character name column
    const int maxCharacterNameWidth = 20;

    // Print table header
    std::cout << "+---------------------+---------------+------------+----------+---------+----------------+" << std::endl;
    std::cout << "| Character Name      | Character ID  | Max Health | Strength | Defense | Current Health |" << std::endl;
    std::cout << "+---------------------+---------------+------------+----------+---------+----------------+" << std::endl;

    for (const auto& character : ListOfCharacter) {
        // Truncate the character name if it exceeds the maximum width
        std::string characterName = character.getCharacterName();
        if (characterName.length() > maxCharacterNameWidth) {
            characterName = characterName.substr(0, maxCharacterNameWidth - 3) + "...";
        }

        // Print the table row
        std::cout << "| " << std::left << std::setw(maxCharacterNameWidth) << characterName << " | "
            << std::right << std::setw(13) << character.getCharacterID() << " | "
            << std::right << std::setw(10) << character.getMaxHealth() << " | "
            << std::right << std::setw(8) << character.getStrength() << " | "
            << std::right << std::setw(7) << character.getDefense() << " | "
            << std::right << std::setw(14) << character.getCurrentHealth() << " |" << std::endl;

        // Print the separator line
        std::cout << "+---------------------+---------------+------------+----------+---------+----------------+" << std::endl;
    }

    // Print table footer
    std::cout << "+---------------------+---------------+------------+----------+---------+----------------+" << std::endl;

    std::cout << std::endl << "Press anything to continue!";
    getUserInput();
    drawMenu();
}




void UI::drawMenuRemoveCharacter() {
    clearConsole();
    bool isSelectedOptionDisplayed = false;  // Check if selected option is displayed
    unsigned i = 0;
    for (; i < DataBase.characterList.size(); ++i)
    {
        if (i == unsigned(selectedOption))
        {
            isSelectedOptionDisplayed = true;
            std::cout << "===============" << std::endl;
            std::cout << DataBase.characterList[i].getCharacterName() << std::endl;
            std::cout << "===============" << std::endl;
            continue;
        }

        if (i - 1 != unsigned(selectedOption)) {
            std::cout << std::endl;
        }

        std::cout << DataBase.characterList[i].getCharacterName() << std::endl;
    }

    // Display the cancel option if the selected option is not displayed
    if (!isSelectedOptionDisplayed) {
        std::cout << "===============" << std::endl;
        std::cout << "Cancel" << std::endl;
        std::cout << "===============" << std::endl;
    }
    else {
        if (i - 1 != unsigned(selectedOption)) {
            std::cout << std::endl;
        }
        std::cout << "Cancel" << std::endl;
    }
    

    useMenuRemoveCharacter();
}


void UI::useMenuRemoveCharacter() {
    bool menuRemoveCharacterActive = true;

    int userInput = getUserInput();
    if (selectedOption < 0)
        selectedOption = 0;

    while (menuRemoveCharacterActive) {
        unsigned characterIndex = unsigned(selectedOption);

        switch (userInput) {
        case 'w':  
            if (selectedOption > 0)
                selectedOption--;
            userInput = 0;
            drawMenuRemoveCharacter();
            break;
        case 's': 
            if (selectedOption < int(DataBase.characterList.size()))
                selectedOption++;
            userInput = 0;
            drawMenuRemoveCharacter();
            break;
        case 13:  
            if (characterIndex == int(DataBase.characterList.size())) {
                clearConsole();
                selectedOption = 0;
                menuRemoveCharacterActive = false; 
                drawMenu();
            }
            else if (characterIndex < int(DataBase.characterList.size())) {
                Character& removedCharacter = DataBase.characterList[characterIndex];

                // Remove associated items from inventory
                for (auto it = DataBase.inventoryList.begin(); it != DataBase.inventoryList.end(); ) {
                    if (it->CharacterOwnerID == removedCharacter.getCharacterID()) {
                        it = DataBase.inventoryList.erase(it);
                    }
                    else {
                        ++it;
                    }
                }

                // Remove character
                DataBase.characterList.erase(DataBase.characterList.begin() + characterIndex);

                // Save changes to file
                DataBase.writeToFileCharacters();
                DataBase.writeToFileItems();

                clearConsole();
                std::cout << "Character and associated items removed successfully! Press anything to continue" << std::endl;
                getUserInput();
                menuRemoveCharacterActive = false;  
                drawMenu();
            }
            break;
        default:
            getUserInput();
            break;
        }
    }
}









void UI::useMenuToAddItem() {
    bool validationCheck = false;
    bool AddItemMenu = true;
    int userInput = getUserInput();
    std::string NewName;
    std::string NewDescription;
    Inventory NewInventory;

    while (AddItemMenu)
    {
    
        switch (userInput)
        {
        case 'w': 
            if (selectedOption > 0)
                selectedOption--;
            userInput = 0;
            drawMenuAddItem();
            getUserInput();
            break;
        case 's':  
            if (selectedOption < int(ItemCharacterstics.size()) - 1)
                selectedOption++;
            userInput = 0;
            drawMenuAddItem();
            getUserInput();
            break;
        case 13:  
            switch (selectedOption)
            {
            case 0:
                // Handle "Set Name" option

                clearConsole();
                std::cout << "Write Name for Item ";
                std::cin >> NewName;
                DataBase.newItem.setItemName(NewName);
                drawMenuAddItem();
                break;

            case 1:
                // Handle "Set Defense" option
                clearConsole();

                int newDefense;

                std::cout << "Write new Defense \n";
                std::cin >> newDefense;

                while (!validationCheck)
                {
                    validationCheck = DataBase.newItem.validationOfValue(newDefense);
                    if (validationCheck) {
                        DataBase.newItem.setDefense(newDefense);
                    }
                    else {

                        std::cout << "Defense must be more than -1 \n";
                        std::cin >> newDefense;
                    }
                };

                drawMenuAddItem();
                break;
            case 2:
                // Handle "Set Attack Power" option

                clearConsole();

                int newAttackPower;

                std::cout << "Write new Attack Power \n";
                std::cin >> newAttackPower;

                while (!validationCheck)
                {
                    validationCheck = DataBase.newItem.validationOfValue(newAttackPower);
                    if (validationCheck) {
                        DataBase.newItem.setAttackPower(newAttackPower);
                    }
                    else {

                        std::cout << "Attack Power must be more than -1 \n";
                        std::cin >> newAttackPower;
                    }
                };

                drawMenuAddItem();
                
                break;
            case 3:
                // Handle "Finish" option

                clearConsole();

                DataBase.newItem.ItemID = DataBase.generateItemID();

                NewInventory.CharacterOwnerID = DataBase.ChosenCharacter.getCharacterID();

                NewInventory.ITem = DataBase.newItem;

                DataBase.inventoryList.push_back(NewInventory);
                DataBase.ChosenCharacter.reset();
                std::cout << "You have successfully added Item to character! Press anything to continue";
                getUserInput();
                selectedOption = 0;
                AddItemMenu = false;
                drawMenu();
                
                break;
            case 4:
                // Handle "Cancel" option

                AddItemMenu = false;
                clearConsole();
                selectedOption = 0;
                DataBase.ChosenCharacter.reset();
                drawMenu();
                break;
            default:
                break;
            }
            break;
        default:
            useMenuAddCharacter();
            break;
        }
    }
}

void UI::drawMenuToChooseCharacter() {
    clearConsole();
    unsigned i = 0;
    for (; i < DataBase.characterList.size(); ++i) {
        if (i == unsigned(selectedOption)) {
            std::cout << "===============" << std::endl;
            std::cout << DataBase.characterList[i].getCharacterName() << std::endl;
            std::cout << "===============" << std::endl;
            continue;
        }

        if (i - 1 != unsigned(selectedOption)) {
            std::cout << std::endl;
        }

        std::cout << DataBase.characterList[i].getCharacterName() << std::endl;
    }

    // Draw the cancel option
    if (unsigned(selectedOption) == DataBase.characterList.size()) {
        std::cout << "===============" << std::endl;
        std::cout << "Cancel" << std::endl;
        std::cout << "===============" << std::endl;
    }
    else {
        if (i - 1 != unsigned(selectedOption)) {
            std::cout << std::endl;
        }
        std::cout << "Cancel" << std::endl;
    }
    useMenuToChooseCharacter();
}

void UI::useMenuToChooseCharacter() {
    bool menuToChooseCharacter = true;

    int userInput = getUserInput();
    if (selectedOption < 0)
    {
        selectedOption = 0;
    }

    while (menuToChooseCharacter) {
       
        unsigned characterIndex = unsigned(selectedOption);

        switch (userInput) {
        case 'w':  
            if (selectedOption > 0)
                selectedOption--;
            userInput = 0;
            drawMenuToChooseCharacter();
            break;
        case 's':  
            if (selectedOption < int(DataBase.characterList.size()))
                selectedOption++;
            userInput = 0;
            drawMenuToChooseCharacter();
            break;
        case 13:  // Select current option
            clearConsole();
            if (characterIndex == DataBase.characterList.size()) {
                // Cancel option selected
                selectedOption = 0;
                userInput = 0;
                menuToChooseCharacter = false;  // Exit the loop
                drawMenu();  // Go back to the main menu
            }
            else {
                // Character selected
                menuToChooseCharacter = false;  // Exit the loop
                selectedOption = 0;
                userInput = 0;
                DataBase.ChosenCharacter = DataBase.characterList[characterIndex];
                if (DataBase.savedChoice == 0) {
                    drawMenuAddItem();
                    break;
                }
                else {
                    drawMenuDeleteItemFromCharacter();
                    break;
                }
            }
            break;

        default:
            drawMenuToChooseCharacter();
            break;
        }
    }
}

void UI::drawMenuAddItem() {
    clearConsole();
    std::cout << "It's not necessary to set all parameters." << std::endl;
    std::cout << "If you don't set something then we will use default value" << std::endl;
    std::cout << "but we highly recommend to set al least Item name" << "\n\n";

    for (unsigned i = 0; i < int(ItemCharacterstics.size()); ++i)
    {
        if (i == unsigned(selectedOption))
        {
            std::cout << "===============" << std::endl;
            std::cout << ItemCharacterstics.at(i) << std::endl;
            std::cout << "===============" << std::endl;

            continue;
        }

        if (i - 1 != unsigned(selectedOption)) {
            std::cout << std::endl;
        }

        std::cout << ItemCharacterstics[i] << std::endl;

    }
    useMenuToAddItem();
}




void UI::printItems() {
    clearConsole();

    // Set the maximum width for the item name and character name columns
    const int maxItemNameWidth = 20;
    const int maxCharacterNameWidth = 18;

    // Print table header
    std::cout << "-----------------------------------------------------------------------" << std::endl;
    std::cout << "| Owner              | Item Name          | Defense | Attack | ID      |" << std::endl;
    std::cout << "-----------------------------------------------------------------------" << std::endl;

    for (const Inventory& inventory : DataBase.inventoryList) {
        // Truncate the item name if it exceeds the maximum width
        std::string itemName = inventory.ITem.getItemName();
        if (itemName.length() > maxItemNameWidth) {
            itemName = itemName.substr(0, maxItemNameWidth - 3) + "...";
        }

        // Truncate the character name if it exceeds the maximum width
        std::string characterName = DataBase.getCharacterByID(inventory.CharacterOwnerID).getCharacterName(); // I will see this line in mine nighmares

        if (characterName.length() > maxCharacterNameWidth) {
            characterName = characterName.substr(0, maxCharacterNameWidth - 3) + "...";
        }

        // Print the table row
        std::cout << "| " << std::setw(maxCharacterNameWidth) << characterName
            << " | " << std::setw(maxItemNameWidth) << itemName
            << " | " << std::setw(7) << inventory.ITem.getDefense()
            << " | " << std::setw(6) << inventory.ITem.getAttackPower()
            << " | " << std::setw(8) << inventory.ITem.ItemID << " |" << std::endl;
    }

    // Print table footer
    std::cout << "-----------------------------------------------------------------------" << std::endl;

    std::cout << std::endl << "Press anything to continue!";
    getUserInput();
    drawMenu();
}

void UI::drawMenuDeleteItemFromCharacter() {
    clearConsole();

    Character chosenCharacter = DataBase.ChosenCharacter;

    std::cout << "Items for " << chosenCharacter.getCharacterName() << ":" << std::endl;

    bool isSelectedOptionDisplayed = false;  // Check if selected option is displayed
    unsigned i = 0;

    for (const Inventory& item : DataBase.inventoryList) {
        if (item.CharacterOwnerID == chosenCharacter.getCharacterID()) {
            if (i == unsigned(selectedOption)) {
                std::cout << "===============" << std::endl;
                std::cout << item.ITem.getItemName() << std::endl;
                std::cout << "===============" << std::endl;
                isSelectedOptionDisplayed = true;
            }
            else {
                if (i - 1 != unsigned(selectedOption)) {
                    std::cout << std::endl;
                }
                std::cout << item.ITem.getItemName() << std::endl;
            }
            ++i;
        }
    }

    // Display the cancel option if the selected option is not displayed
    if (!isSelectedOptionDisplayed) {
        std::cout << "===============" << std::endl;
        std::cout << "Cancel" << std::endl;
        std::cout << "===============" << std::endl;
    }
    else {
        if (i - 1 != unsigned(selectedOption)) {
            std::cout << std::endl;
        }
        std::cout << "Cancel" << std::endl;
    }

    useMenuDeleteItemFromCharacter();
}

void UI::useMenuDeleteItemFromCharacter() {
    bool menuDeleteItemFromCharacterActive = true;

    int userInput = getUserInput();
    if (selectedOption < 0)
        selectedOption = 0;

    while (menuDeleteItemFromCharacterActive) {
      
        unsigned selectedItemIndex = unsigned(selectedOption);

        switch (userInput) {
        case 'w':  
            if (selectedOption > 0)
                selectedOption--;
            userInput = 0;
            drawMenuDeleteItemFromCharacter();
            break;
        case 's':
            if (selectedOption < int(DataBase.inventoryList.size()))
                selectedOption++;
            userInput = 0;
            drawMenuDeleteItemFromCharacter();
            break;
        case 13:  // Select current option
            clearConsole();
            if (selectedItemIndex == DataBase.inventoryList.size()) {
                // Cancel option selected
                selectedOption = 0;
                userInput = 0;
                menuDeleteItemFromCharacterActive = false;  
                drawMenu();  // Go back to the main menu
            }
            else {
                // Item selected
                Inventory selectedItem = DataBase.inventoryList[selectedItemIndex];

                // Remove the selected item from inventory
                auto it = std::find(DataBase.inventoryList.begin(), DataBase.inventoryList.end(), selectedItem);
                if (it != DataBase.inventoryList.end()) {
                    DataBase.inventoryList.erase(it);
                    // Save changes to file
                    DataBase.writeToFileItems();

                    clearConsole();
                    std::cout << "Item successfully removed! Press anything to continue" << std::endl;
                    getUserInput();
                }
                else {
                    clearConsole();
                    std::cout << "Failed to remove item! Press anything to continue" << std::endl;
                    getUserInput();
                }
            }

       
            clearConsole();
            drawMenuDeleteItemFromCharacter();
            break;
        default:
            getUserInput();
            break;
        }
    }
}


void UI::askForSortOptions() {
    clearConsole();
    bool sortByName, sortByStrength;
    std::string userInput;
    bool validInput = false;

    // Ask for sorting by name
    while (!validInput) {
        std::cout << "Do you want to sort by name? (yes/no): ";
        std::cin >> userInput;

        if (userInput == "yes" || userInput == "no") {
            validInput = true;
        }
        else {
            std::cout << "Invalid input! Please enter 'yes' or 'no'." << std::endl;
        }
    }

    sortByName = (userInput == "yes");

    validInput = false;

    // Ask for sorting by strength
    while (!validInput) {
        std::cout << "Do you want to sort by strength? (yes/no): ";
        std::cin >> userInput;

        if (userInput == "yes" || userInput == "no") {
            validInput = true;
        }
        else {
            std::cout << "Invalid input! Please enter 'yes' or 'no'." << std::endl;
        }
    }

    sortByStrength = (userInput == "yes");

    DataBase.sortCharacters(sortByName, sortByStrength);
}

void UI::askForFilterOptions() {
    bool enableHealthFilter = false;
    bool enableStrengthFilter = false;
    bool enableItemCountFilter = false;

    char choice;
    std::cout << "Do you want to enable filtering by Health? (Y/N): ";
    std::cin >> choice;
    enableHealthFilter = (choice == 'Y' || choice == 'y');

    std::cout << "Do you want to enable filtering by Strength? (Y/N): ";
    std::cin >> choice;
    enableStrengthFilter = (choice == 'Y' || choice == 'y');

    std::cout << "Do you want to enable filtering by Item count? (Y/N): ";
    std::cin >> choice;
    enableItemCountFilter = (choice == 'Y' || choice == 'y');

    printCharacters(DataBase.filterCharacters(enableHealthFilter, enableStrengthFilter, enableItemCountFilter));
}
