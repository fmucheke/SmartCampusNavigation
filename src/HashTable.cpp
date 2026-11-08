#include "HashTable.h"

#include <cctype>
#include <iostream>

// Constructor
HashTable::HashTable(int capacity) {
    if (capacity <= 0) {
        capacity = 101;
    }

    table.resize(capacity);

    entryCount = 0;
    collisionCount = 0;
}

// Normalize ID: remove surrounding spaces and convert to uppercase
std::string HashTable::normalizeID(std::string id) const {
    size_t first = id.find_first_not_of(" \t\r\n");

    if (first == std::string::npos) {
        return "";
    }

    size_t last = id.find_last_not_of(" \t\r\n");

    id = id.substr(first, last - first + 1);

    for (char& c : id) {
        c = static_cast<char>(
            std::toupper(static_cast<unsigned char>(c))
        );
    }

    return id;
}

// Validate ID format: F followed by exactly three digits
bool HashTable::isValidID(std::string id) const {
    if (id.length() != 4 || id[0] != 'F') {
        return false;
    }

    for (int i = 1; i < 4; i++) {
        if (!std::isdigit(static_cast<unsigned char>(id[i]))) {
            return false;
        }
    }

    return true;
}

// Custom hash function
int HashTable::hashFunction(std::string id) const {
    unsigned long hash = 0;

    for (char c : id) {
        hash = (hash * 31 +
                static_cast<unsigned char>(c)) % table.size();
    }

    return static_cast<int>(hash);
}

// Insert a facility into the hash table
bool HashTable::insert(const Facility& facility) {
    std::string id = normalizeID(facility.getID());

    if (!isValidID(id)) {
        return false;
    }

    int index = hashFunction(id);

    // Check for duplicate IDs
    for (const Facility& existing : table[index]) {
        if (normalizeID(existing.getID()) == id) {
            return false;
        }
    }

    // Count collision if bucket already contains a facility
    if (!table[index].empty()) {
        collisionCount++;
    }

    // Store the facility with normalized ID
    Facility normalizedFacility(
        id,
        facility.getName(),
        facility.getBuilding(),
        facility.getCategory()
    );

    table[index].push_back(normalizedFacility);

    entryCount++;

    return true;
}

// Search for a facility by ID
const Facility* HashTable::search(std::string id) const {
    id = normalizeID(id);

    if (!isValidID(id)) {
        return nullptr;
    }

    int index = hashFunction(id);

    for (const Facility& facility : table[index]) {
        if (normalizeID(facility.getID()) == id) {
            return &facility;
        }
    }

    return nullptr;
}

// Return hash table capacity
int HashTable::getCapacity() const {
    return static_cast<int>(table.size());
}

// Return number of stored facilities
int HashTable::getEntryCount() const {
    return entryCount;
}

// Return collision count
int HashTable::getCollisionCount() const {
    return collisionCount;
}
