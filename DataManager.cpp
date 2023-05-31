#include "DataManager.h"
#include <random>
#include <algorithm>
#include "Item.h"
#include <fstream>
#include "Inventory.h"

DataManager::DataManager() {
    readFromFileCharacters();   
    readFromFileItems();
}

DataManager::~DataManager() {
    writeToFileCharacters();
    writeToFileItems();
}

void DataManager::writeToFileCharacters() {
    std::ofstream outputFile(fileNameCharacter, std::ios::binary);
    if (!outputFile) {
        std::cout << "Failed to open the file for writing." << std::endl;
        return;
    }

    for (const Character& character : characterList) {
        // Save the values one by one
        int maxHealth = character.getMaxHealth();
        int currentHealth = character.getCurrentHealth();
        int strength = character.getStrength();
        int defense = character.getDefense();
        int CharacterID = character.getCharacterID();
        std::string characterName = character.getCharacterName();

        outputFile.write(reinterpret_cast<const char*>(&CharacterID), sizeof(int));
        outputFile.write(reinterpret_cast<const char*>(&maxHealth), sizeof(int));
        outputFile.write(reinterpret_cast<const char*>(&currentHealth), sizeof(int));
        outputFile.write(reinterpret_cast<const char*>(&strength), sizeof(int));
        outputFile.write(reinterpret_cast<const char*>(&defense), sizeof(int));

        // Save the length of the characterName string
        unsigned nameLength = unsigned(characterName.length());
        outputFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(int));

        // Save the characters of the characterName string
        outputFile.write(characterName.c_str(), nameLength + 1); // +1 to include the null terminator
    }

    outputFile.close();
}


void DataManager::readFromFileCharacters() {
    
    std::ifstream inputFile(fileNameCharacter, std::ios::binary);
    if (!inputFile) {
        std::cout << "Failed to open the file for reading." << std::endl;
        return;
    }

    int maxHealth;
    int currentHealth;
    int strength;
    int defense;
    int CharacterID;
    std::string characterName;

    characterList.clear(); // Clear the existing character list

    while (true) {
        Character character;

        // Read the values one by one
        inputFile.read(reinterpret_cast<char*>(&CharacterID), sizeof(int));
        inputFile.read(reinterpret_cast<char*>(&maxHealth), sizeof(int));
        inputFile.read(reinterpret_cast<char*>(&currentHealth), sizeof(int));
        inputFile.read(reinterpret_cast<char*>(&strength), sizeof(int));
        inputFile.read(reinterpret_cast<char*>(&defense), sizeof(int));

        // Read the length of the characterName string
        unsigned nameLength;
        inputFile.read(reinterpret_cast<char*>(&nameLength), sizeof(int));

        if (!inputFile)
            break; // Reached the end of the file

        // Read the characters of the characterName string
        std::vector<char> nameBuffer(nameLength + 1); // +1 for null terminator
        inputFile.read(nameBuffer.data(), nameLength + 1);
        characterName = std::string(nameBuffer.data());
        
        character.setCharacterID(CharacterID);
        character.setMaxHealth(maxHealth);
        character.setCurrentHealth(currentHealth);
        character.setStrength(strength);
        character.setDefense(defense);
        character.SetCharacterName(characterName);
        characterList.push_back(character);
    }

    inputFile.close();
}

int DataManager::generateCharacterID() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(10000, 99999);

    int newID;
    bool isUnique = false;

    while (!isUnique) {
        newID = dist(mt);

        auto it = std::find_if(characterList.begin(), characterList.end(),
            [newID](const Character& currentCharacter) { return currentCharacter.getCharacterID() == newID; });

        if (it == characterList.end()) {
            isUnique = true;
        }
    }

    return newID;
}

int DataManager::generateItemID() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(10000, 99999);

    int newItemID = -1; // Initialize with a value outside the range of possible IDs
    bool isUnique = false;

    while (!isUnique) {
        newItemID = dist(mt);

        auto it = std::find_if(inventoryList.begin(), inventoryList.end(),
            [newItemID](const Inventory& currentInventory) { return currentInventory.ITem.ItemID == newItemID; }); // I spend like 2 hours just for this line

        if (it == inventoryList.end()) {
            isUnique = true;
        }
    }

    return newItemID;
}

void DataManager::deleteCharacterFromFile(int characterID) {
    std::ifstream inputFile(fileNameCharacter, std::ios::binary);
    if (!inputFile) {
        std::cout << "Failed to open the file for reading." << std::endl;
        return;
    }

    std::ofstream tempFile("temp.bin", std::ios::binary);
    if (!tempFile) {
        std::cout << "Failed to create temporary file." << std::endl;
        return;
    }

    Character tempCharacter;

    while (inputFile.read(reinterpret_cast<char*>(&tempCharacter), sizeof(Character))) {
        if (tempCharacter.getCharacterID() != characterID) {
            // Write the character to the temporary file if the ID doesn't match
            tempFile.write(reinterpret_cast<const char*>(&tempCharacter), sizeof(Character));
        }
    }

    inputFile.close();
    tempFile.close();

    // Delete the original file and rename the temporary file to the original name
    std::remove(fileNameCharacter.c_str());
    if (std::rename("temp.bin", fileNameCharacter.c_str()) != 0) {
        std::cout << "Failed to rename temporary file." << std::endl;
        return;
    }

    std::cout << "Character removed from the file successfully!" << std::endl;
}

void DataManager::writeToFileItems()
{
    std::ofstream outputFile(fileNameItems, std::ios::binary);
    if (!outputFile) {
        std::cout << "Failed to open the file for writing." << std::endl;
        return;
    }

    for (const Inventory& inventory : inventoryList) {
        const Item& item = inventory.ITem;
        int ownerID = inventory.CharacterOwnerID;  // Get the owner's ID

        // Save the values one by one
        int itemID = item.ItemID;
        int defense = item.getDefense();
        int attackPower = item.getAttackPower();
        std::string itemName = item.getItemName();

        outputFile.write(reinterpret_cast<const char*>(&itemID), sizeof(int));
        outputFile.write(reinterpret_cast<const char*>(&ownerID), sizeof(int));  // Save the owner's ID
        outputFile.write(reinterpret_cast<const char*>(&defense), sizeof(int));
        outputFile.write(reinterpret_cast<const char*>(&attackPower), sizeof(int));

        // Save the length of the itemName string
        unsigned nameLength = unsigned(itemName.length());
        outputFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(int));

        // Save the characters of the itemName string
        outputFile.write(itemName.c_str(), nameLength + 1); // +1 to include the null terminator
    }

    outputFile.close();
}

void DataManager::readFromFileItems()
{
    std::ifstream inputFile(fileNameItems, std::ios::binary);
    if (!inputFile) {
        std::cout << "Failed to open the file for reading." << std::endl;
        return;
    }

    int itemID;
    int ownerID{};  
    int defense;
    int attackPower;
    std::string itemName;

    inventoryList.clear();

    while (true) {
        Inventory inventory;
        Item& item = inventory.ITem;

        inputFile.read(reinterpret_cast<char*>(&itemID), sizeof(int));
        inputFile.read(reinterpret_cast<char*>(&ownerID), sizeof(int));
        inputFile.read(reinterpret_cast<char*>(&defense), sizeof(int));
        inputFile.read(reinterpret_cast<char*>(&attackPower), sizeof(int));

        unsigned nameLength;
        inputFile.read(reinterpret_cast<char*>(&nameLength), sizeof(int));

        if (!inputFile)
            break;

        std::vector<char> nameBuffer(nameLength + 1);
        inputFile.read(nameBuffer.data(), nameLength + 1);
        itemName = std::string(nameBuffer.data());

        item.ItemID = itemID;
        item.setDefense(defense);
        item.setAttackPower(attackPower);
        item.setItemName(itemName);

        inventory.CharacterOwnerID = ownerID;  

        inventoryList.push_back(inventory);
    }

    inputFile.close();
}



Character DataManager::getCharacterByID(int characterID) {
    for (const auto& character : characterList) {
        if (character.getCharacterID() == characterID) {
            return character;
        }
    }
    // Return a default-constructed Character object if the ID is not found
    return Character();
}

void DataManager::sortCharacters(bool sortByName, bool sortByStrength) {
    if (sortByName && sortByStrength) {
        // Sort by name (case-insensitive) and then by strength
        std::sort(characterList.begin(), characterList.end(), [](const Character& a, const Character& b) {
            std::string nameA = a.getCharacterName();
            std::string nameB = b.getCharacterName();

            // Convert names to lowercase for case-insensitive comparison
            std::transform(nameA.begin(), nameA.end(), nameA.begin(), ::tolower);
            std::transform(nameB.begin(), nameB.end(), nameB.begin(), ::tolower);

            if (nameA == nameB) {
                return a.getStrength() > b.getStrength();
            }
            return nameA < nameB;
            });
        // here almost never sorted by  strength because it's sorting by name and then by strength 
    }
    else if (sortByName) {
        // Sort by name (case-insensitive)
        std::sort(characterList.begin(), characterList.end(), [](const Character& a, const Character& b) {
            std::string nameA = a.getCharacterName();
            std::string nameB = b.getCharacterName();

            std::transform(nameA.begin(), nameA.end(), nameA.begin(), ::tolower);
            std::transform(nameB.begin(), nameB.end(), nameB.begin(), ::tolower);

            return nameA < nameB;
            });
    }
    else if (sortByStrength) {
        std::sort(characterList.begin(), characterList.end(), [](const Character& a, const Character& b) {
            return a.getStrength() > b.getStrength();
            });
    }

    // No sorting applied if both sortByName and sortByStrength are false
}

std::vector<Character> DataManager::filterCharacters(bool enableHealthFilter, bool enableStrengthFilter, bool enableItemCountFilter) {
    std::vector<Character> filteredList = characterList;

    // Filter by Health
    if (enableHealthFilter) {
        int healthThreshold;
        std::cout << "Enter the Health threshold: ";
        std::cin >> healthThreshold;
        filteredList.erase(std::remove_if(filteredList.begin(), filteredList.end(), [healthThreshold](const Character& character) {
            return character.getMaxHealth() < healthThreshold;
            }), filteredList.end());
    }

    // Filter by Strength
    if (enableStrengthFilter) {
        int strengthThreshold;
        std::cout << "Enter the Strength threshold: ";
        std::cin >> strengthThreshold;
        filteredList.erase(std::remove_if(filteredList.begin(), filteredList.end(), [strengthThreshold](const Character& character) {
            return character.getStrength() < strengthThreshold;
            }), filteredList.end());
    }

    // Filter by Item count
    if (enableItemCountFilter) {
        std::cout << "Enter the Item count threshold: ";
        int itemCountThreshold;
        std::cin >> itemCountThreshold;
        filteredList.erase(std::remove_if(filteredList.begin(), filteredList.end(), [this, itemCountThreshold](const Character& character) {
            int itemCount = 0;
            for (const Inventory& inventory : inventoryList) {
                if (inventory.CharacterOwnerID == character.getCharacterID()) {
                    itemCount++;
                }
            }
            return itemCount < itemCountThreshold;
            }), filteredList.end());
    }

    return filteredList;
}

