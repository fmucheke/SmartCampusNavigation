#include "FacilityManager.h"
#include "FileUtils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cctype>

// Remove spaces from the beginning and end
std::string FacilityManager::trim(std::string text) const {
    return TrimWhiteSpace(text);
}

// Convert text to uppercase for comparisons
std::string FacilityManager::normalize(std::string text) const {
    return StandardizeName(text);
}

// Load facilities from the text file
void FacilityManager::loadFacilities(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Could not open: " << filePath << "\n";
        return;
    }

    // Load the valid building names
    std::vector<std::string> buildings;
    std::ifstream buildingFile("data/buildings.txt");
    std::string line;

    if (!buildingFile.is_open()) {
        std::cout << "Could not open data/buildings.txt\n";
        return;
    }

    while (std::getline(buildingFile, line)) {
        line = trim(line);

        if (line.empty() || line[0] == '#') {
            continue;
        }

        buildings.push_back(normalize(line));
    }

    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;
        line = trim(line);

        // Ignore blank lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Check that there are exactly four fields
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

        // Check for empty fields
        if (id.empty() || name.empty() ||
            building.empty() || category.empty()) {

            std::cout << filePath << ":" << lineNumber
                      << " - Empty field\n";
            rejected++;
            continue;
        }

        // Check that the building exists
        bool buildingFound = false;

        for (const std::string& validBuilding : buildings) {
            if (normalize(building) == validBuilding) {
                buildingFound = true;
                break;
            }
        }

        if (!buildingFound) {
            std::cout << filePath << ":" << lineNumber
                      << " - Unknown building: "
                      << building << "\n";
            rejected++;
            continue;
        }

        // Create the facility
        Facility facility(id, name, building, category);

        // Insert into custom hash table
        // Reject invalid or duplicate IDs
        if (!hashTable.insert(facility)) {
            std::cout << filePath << ":" << lineNumber
                      << " - Invalid or duplicate facility ID\n";
            rejected++;
            continue;
        }

        facilities.push_back(facility);
        accepted++;
    }

    std::cout << "Facilities accepted: " << accepted << "\n";
    std::cout << "Facilities rejected: " << rejected << "\n";
}

// Display all facilities
void FacilityManager::displayAll() const {
    if (facilities.empty()) {
        std::cout << "No facilities available.\n";
        return;
    }

    for (const Facility& facility : facilities) {
        facility.display();
        std::cout << "--------------------\n";
    }
}

// Search by facility ID using the custom hash table
void FacilityManager::searchByID(const std::string& id) const {
    const Facility* found = hashTable.search(id);

    if (found != nullptr) {
        std::cout << "Facility found:\n";
        found->display();
    } else {
        std::cout << "Facility not found.\n";
    }
}

// Search by complete facility name
void FacilityManager::searchByName(const std::string& name) const {
    bool found = false;

    for (const Facility& facility : facilities) {
        if (normalize(facility.getName()) == normalize(name)) {
            facility.display();
            std::cout << "--------------------\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No facilities found with that name.\n";
    }
}

// Search by facility category
void FacilityManager::searchByCategory(
    const std::string& category) const {

    bool found = false;

    for (const Facility& facility : facilities) {
        if (normalize(facility.getCategory()) ==
            normalize(category)) {

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
    std::cout << "Total facilities: " << total << "\n";
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
