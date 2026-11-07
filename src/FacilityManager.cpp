
#include "FacilityManager.h"
#include "FileUtils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <cctype>

// Remove spaces from the beginning and end
std::string FacilityManager::trim(std::string text) const {
    return TrimWhiteSpace(text);
}

// Convert text to uppercase for comparisons
std::string FacilityManager::normalize(std::string text) const {
    return StandardizeName(text);
}

// Return the number of stored facilities
int FacilityManager::getFacilityCount() const {
    return static_cast<int>(facilities.size());
}

// Display all stored facilities
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

