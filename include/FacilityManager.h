
#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include "Facility.h"
#include "HashTable.h"
#include "CampusGraph.h"

#include <string>
#include <vector>

class FacilityManager {
private:
    // Store the facilities that passed validation
    std::vector<Facility> facilities;

    // Use the hash table to search by facility ID
    HashTable hashTable;

    std::string trim(std::string text) const;
    std::string normalize(std::string text) const;

public:
    // Load facilities using the buildings in CampusGraph
    void loadFacilities(const std::string& filePath,
                        const CampusGraph& campusGraph);

    void displayAll() const;
    void searchByID(const std::string& id) const;
    void searchByName(const std::string& name) const;
    void searchByCategory(const std::string& category) const;

    void categoryReport() const;
    int getFacilityCount() const;
    void displayHashStats() const;
};

#endif
