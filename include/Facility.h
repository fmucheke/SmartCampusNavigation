#ifndef FACILITY_H
#define FACILITY_H

#include <string>

class Facility {
private:
    std::string facilityID;
    std::string facilityName;
    std::string buildingName;
    std::string category;

public:
    // Constructor
    Facility(std::string id, std::string name,
             std::string building, std::string cat);

    // Getter functions
    std::string getID() const;
    std::string getName() const;
    std::string getBuilding() const;
    std::string getCategory() const;

    // Display facility information
    void display() const;
};

#endif