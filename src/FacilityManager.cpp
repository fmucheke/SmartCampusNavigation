
#include "FacilityManager.h"
#include "FileUtils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>

// Remove spaces from the beginning and end
std::string FacilityManager::trim(std::string text) const {
    return TrimWhiteSpace(text);
}

// Make text consistent for comparisons
std::string FacilityManager::normalize(std::string text) const {
    return StandardizeName(text);
}

// Check if the facility ID follows the correct format
static bool validFacilityID(const std::string& id) {
    if (id.length() != 4 || id[0] != 'F') {
        return false;
    }

    for (int i = 1; i < 4; i++) {
        if (id[i] < '0' || id[i] > '9') {
            return false;
        }
    }

    return true;
}

// Load facilities from the given file
void FacilityManager::loadFacilities(
    const std::string& filePath,
    const CampusGraph& campusGraph) {

    std::ifstream file(filePath);

    // Handle a missing or unreadable facility file
    if (!file.is_open()) {
        std::cout << "Could not open: " << filePath << "\n";

        std::cout << "\nFacilities accepted: 0\n";
        std::cout << "Facilities rejected: 0\n";

        displayHashStats();
        return;
    }

    std::string line;
    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;
        line = trim(line);

        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Each facility should have four fields
        int separators = 0;

        for (char c : line) {
            if (c == '|') {
                separators++;
            }
        }

        if (separators != 3) {
            std::cout << filePath << ":" << lineNumber
                      << " - Expected exactly 4 fields\n";
            rejected++;
            continue;
        }

        std::stringstream stream(line);

        std::string id;
        std::string name;
        std::string building;
        std::string category;

        std::getline(stream, id, '|');
        std::getline(stream, name, '|');
        std::getline(stream, building, '|');
        std::getline(stream, category, '|');

        id = normalize(id);
        name = trim(name);
        building = trim(building);
        category = trim(category);

        // Make sure all fields have values
        if (id.empty() || name.empty() ||
            building.empty() || category.empty()) {

            std::cout << filePath << ":" << lineNumber
                      << " - Empty field\n";
            rejected++;
            continue;
        }

        // Check the ID format
        if (!validFacilityID(id)) {
            std::cout << filePath << ":" << lineNumber
                      << " - Invalid facility ID format: "
                      << id << "\n";
            rejected++;
            continue;
        }

        // Check the building using the campus graph
        if (!campusGraph.BuildingExists(building)) {
            std::cout << filePath << ":" << lineNumber
                      << " - Unknown building: "
                      << building << "\n";
            rejected++;
            continue;
        }

        // Use the official building name from CampusGraph
        building = campusGraph.GetBuildingName(building);

        // Check for duplicate facility IDs
        if (hashTable.search(id) != nullptr) {
            std::cout << filePath << ":" << lineNumber
                      << " - Duplicate facility ID: "
                      << id << "\n";
            rejected++;
            continue;
        }

        // Create the facility
        Facility facility(id, name, building, category);

        // Add the facility to the custom hash table
        if (!hashTable.insert(facility)) {
            std::cout << filePath << ":" << lineNumber
                      << " - Could not insert facility: "
                      << id << "\n";
            rejected++;
            continue;
        }

        facilities.push_back(facility);
        accepted++;
    }

    // Show loading summary and hash statistics
    std::cout << "\nFacilities accepted: "
              << accepted << "\n";

    std::cout << "Facilities rejected: "
              << rejected << "\n";

    displayHashStats();
}

// Display all facilities
void FacilityManager::displayAll() const {

    if (facilities.empty()) {
        std::cout << "No facilities available.\n";
        std::cout << "Total facilities: 0\n";
        return;
    }

    std::cout << "\nAll Campus Facilities:\n\n";

    for (const Facility& facility : facilities) {
        facility.display();
        std::cout << "--------------------\n";
    }

    std::cout << "Total facilities: "
              << getFacilityCount() << "\n";
}

// Search for a facility using its ID
void FacilityManager::searchByID(const std::string& id) const {

    // Remove spaces and normalize the ID
    std::string normalizedID = normalize(id);

    // Check the ID before searching
    if (!validFacilityID(normalizedID)) {
        std::cout << "Invalid facility ID format. "
                  << "Use F followed by three digits.\n";
        return;
    }

    // Search the custom hash table
    const Facility* found = hashTable.search(normalizedID);

    if (found != nullptr) {
        std::cout << "Facility found:\n";
        found->display();
    } else {
        std::cout << "Facility " << normalizedID
                  << " not found.\n";
    }
}

// Search for facilities by name
void FacilityManager::searchByName(
    const std::string& name) const {

    bool found = false;
    std::string searchName = normalize(name);

    for (const Facility& facility : facilities) {
        if (normalize(facility.getName()) == searchName) {
            facility.display();
            std::cout << "--------------------\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No facilities found with that name.\n";
    }
}

// Search for facilities by category
void FacilityManager::searchByCategory(
    const std::string& category) const {

    bool found = false;
    std::string searchCategory = normalize(category);

    for (const Facility& facility : facilities) {
        if (normalize(facility.getCategory()) ==
            searchCategory) {

            facility.display();
            std::cout << "--------------------\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No facilities found in that category.\n";
    }
}

// Display category statistics
void FacilityManager::categoryReport() const {

    if (facilities.empty()) {
        std::cout << "No facilities available for report.\n";
        std::cout << "Total facilities: 0\n";
        return;
    }

    std::vector<std::string> categoryNames;
    std::vector<std::string> categoryKeys;
    std::vector<int> counts;

    // Count facilities in each category
    for (const Facility& facility : facilities) {
        std::string category = facility.getCategory();
        std::string key = normalize(category);
        bool found = false;

        for (size_t i = 0; i < categoryKeys.size(); i++) {
            if (categoryKeys[i] == key) {
                counts[i]++;
                found = true;
                break;
            }
        }

        if (!found) {
            categoryKeys.push_back(key);
            categoryNames.push_back(category);
            counts.push_back(1);
        }
    }

    int total = getFacilityCount();

    std::cout << "\nFacility Category Report\n";
    std::cout << "----------------------------------------\n";

    std::cout << std::left
              << std::setw(25) << "Category"
              << std::setw(8) << "Count"
              << "Percent\n";

    std::cout << "----------------------------------------\n";

    for (size_t i = 0; i < categoryNames.size(); i++) {
        double percent =
            (static_cast<double>(counts[i]) / total) * 100.0;

        std::cout << std::left
                  << std::setw(25) << categoryNames[i]
                  << std::setw(8) << counts[i]
                  << std::fixed << std::setprecision(1)
                  << percent << "%\n";
    }

    std::cout << "----------------------------------------\n";
    std::cout << "Total facilities: "
              << total << "\n";
}

// Return the total number of facilities
int FacilityManager::getFacilityCount() const {
    return static_cast<int>(facilities.size());
}

// Display custom hash table statistics
void FacilityManager::displayHashStats() const {

    std::cout << "\nHash Table Statistics\n";

    std::cout << "Capacity: "
              << hashTable.getCapacity() << "\n";

    std::cout << "Entries: "
              << hashTable.getEntryCount() << "\n";

    std::cout << "Collisions: "
              << hashTable.getCollisionCount() << "\n";
}
