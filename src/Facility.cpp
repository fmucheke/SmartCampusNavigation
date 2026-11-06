#include "Facility.h"
#include <iostream>

// Constructor
Facility::Facility(std::string id, std::string name,
                   std::string building, std::string cat) {
    facilityID = id;
    facilityName = name;
    buildingName = building;
    category = cat;
}

// Returns facility ID
std::string Facility::getID() const {
    return facilityID;
}

// Returns facility name
std::string Facility::getName() const {
    return facilityName;
}

// Returns building name
std::string Facility::getBuilding() const {
    return buildingName;
}

// Returns facility category
std::string Facility::getCategory() const {
    return category;
}

// Displays facility information
void Facility::display() const {
    std::cout << "Facility ID: " << facilityID << std::endl;
    std::cout << "Facility Name: " << facilityName << std::endl;
    std::cout << "Building: " << buildingName << std::endl;
    std::cout << "Category: " << category << std::endl;
}

