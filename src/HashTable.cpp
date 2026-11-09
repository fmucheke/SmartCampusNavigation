#include "HashTable.h"

#include <cctype>
#include <iostream>

// Create the hash table
HashTable::HashTable(int capacity) {
    // Use 101 buckets if the given capacity is invalid
    if (capacity <= 0) {
        capacity = 101;
    }

    table.resize(capacity);
    entryCount = 0;
    collisionCount = 0;
}

// Remove extra spaces and convert the ID to uppercase
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

// Check that the ID is F followed by exactly three digits
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

// Calculate the bucket index using a custom hash function
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

    // Reject invalid IDs
    if (!isValidID(id)) {
        return false;
    }

    int index = hashFunction(id);

    // Reject duplicates, including IDs with different cases
    for (const Facility& existing : table[index]) {
        if (normalizeID(existing.getID()) == id) {
            return false;
        }
    }

    // Count one collision when inserting into an occupied bucket
    if (!table[index].empty()) {
        collisionCount++;
    }

    // Store the normalized ID
    Facility normalizedFacility(
        id,
        facility.getName(),
        facility.getBuilding(),
        facility.getCategory()
    );

    // Separate chaining allows multiple entries in one bucket
    table[index].push_back(normalizedFacility);
    entryCount++;

    return true;
}

// Search for a facility by ID using the hash table
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

// Return the number of buckets
int HashTable::getCapacity() const {
    return static_cast<int>(table.size());
}

// Return the number of stored facilities
int HashTable::getEntryCount() const {
    return entryCount;
}

// Return the number of collisions
int HashTable::getCollisionCount() const {
    return collisionCount;
}
