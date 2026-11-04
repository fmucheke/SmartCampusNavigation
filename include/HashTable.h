#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "facility.h"
#include <vector>
#include <string>

class HashTable {
private:
    // Each bucket can store multiple facilities.
    // This allows us to handle collisions.
    std::vector<std::vector<Facility>> table;

    int entryCount;
    int collisionCount;

    // Helper functions
    std::string normalizeID(std::string id) const;
    bool isValidID(std::string id) const;
    int hashFunction(std::string id) const;

public:
    // Constructor
    HashTable(int capacity = 101);

    // Insert a facility
    bool insert(const Facility& facility);

    // Search for a facility using its ID
    const Facility* search(std::string id) const;

    // Return hash table information
    int getCapacity() const;
    int getEntryCount() const;
    int getCollisionCount() const;
};

#endif

