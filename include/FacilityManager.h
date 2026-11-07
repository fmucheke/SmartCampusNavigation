
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

    // Custom hash table for facility ID searches
    HashTable hashTable;

    // Helper functions
    std::string trim(std::string text) const;
    std::string normalize(std::string text) const;

public:
    // Load facilities from a text file
    void loadFacilities(const std::string& filePath);

    // Display all facilities
    void displayAll() const;

    // Search by facility ID
    void searchByID(const std::string& id) const;

    // Search by complete facility name
    void searchByName(const std::string& name) const;

    // Search by category
    void searchByCategory(const std::string& category) const;

    // Generate category statistics
    void categoryReport() const;

    // Return total number of facilities
    int getFacilityCount() const;

    // Display hash table statistics
    void displayHashStats() const;
};

#endif

