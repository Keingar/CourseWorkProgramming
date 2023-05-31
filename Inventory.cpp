#include "Inventory.h"

Inventory::Inventory() {
    CharacterOwnerID = 1;
}

bool Inventory::operator==(const Inventory& other) const {
    return this->ITem.ItemID == other.ITem.ItemID;
}