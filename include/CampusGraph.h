#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>

class CampusGraph{
private:
    std::vector<std::string> buildings;
    std::vector<std::vector<int>> adjacencyList;
    int ConnectionCount= 0;
    
    int FindBuildingIndex(const std:: string& name) const;



public:
    bool AddBuilding(const std:: string& name);
    bool BuildingExists(const std::string& name) const;
    bool AddConnection(const std::string& a, const std::string& b);

    void DisplayGraph() const;
    void DisplayDegrees() const;
    void BFS(const std:: string& start) const;
    std::string GetBuildingName(const std::string& name) const;


};
#endif
