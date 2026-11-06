
#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include "Facility.h"
#include "HashTable.h"

#include <vector>
#include <string>

class FacilityManager {
private:
    // Stores all accepted facility records
    std::vector<Facility> facilities;

    // Custom hash table for searching facilities by ID
    HashTable hashTable;

    // Helper functions
    std::string trim(std::string text) const;
    std::string normalize(std::string text) const;

public:
    // Load facility records from a file
    void loadFacilities(const std::string& filePath);

    // Display all facilities
    void displayAll() const;

    // Search facilities by ID using the custom hash table
    void searchByID(const std::string& id) const;

    // Search by complete facility name
    void searchByName(const std::string& name) const;

    // Search by facility category
    void searchByCategory(const std::string& category) const;

    // Display facility category statistics
    void categoryReport() const;

    // Return the number of accepted facilities
    int getFacilityCount() const;

    // Display hash table information
    void displayHashStats() const;
};

#endif

