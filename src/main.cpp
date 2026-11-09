// File: main.cpp
// Authors: Urisha Shrestha, Franklin Mucheke, Samriddi Upreti
// Purpose: Coordinates file loading and the Milestone 1 main menu.
#include <iostream>
#include <string>
#include <limits>

#include "FacilityManager.h"
#include "CampusGraph.h"
#include "GraphLoader.h"
#include "FileUtils.h"
#include "DepartmentTree.h"

using namespace std;

// Check whether the input is blank
bool isBlank(const string& s) {
    for (char c : s) {
        if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
            return false;
        }
    }
    return true;
}

// Add a department
void addDepartmentMenu(DepartmentTree& tree) {
    string name, parent, error;

    cout << "Enter department name: ";
    getline(cin, name);

    if (isBlank(name)) {
        cout << "Error: department name cannot be blank.\n";
        return;
    }

    if (!tree.isEmpty()) {
        cout << "Enter parent department name: ";
        getline(cin, parent);

        if (isBlank(parent)) {
            cout << "Error: parent name cannot be blank.\n";
            return;
        }
    }

    if (tree.addDepartment(name, parent, error)) {
        cout << "Department added.\n";
    } else {
        cout << "Error: " << error << "\n";
    }
}

// Search for a department
void searchDepartmentMenu(DepartmentTree& tree) {
    string name;

    cout << "Enter department name: ";
    getline(cin, name);

    if (isBlank(name)) {
        cout << "Error: department name cannot be blank.\n";
        return;
    }

    tree.searchAndDisplay(name);
}

// Read a menu choice, including option 10
int readChoice() {
    string line;

    if (!getline(cin, line)) {
        return 10;
    }

    line = TrimWhiteSpace(line);

    if (line.empty()) {
        return -1;
    }

    for (char c : line) {
        if (c < '0' || c > '9') {
            return -1;
        }
    }

    if (line == "10") {
        return 10;
    }

    if (line.size() == 1) {
        return line[0] - '0';
    }

    return -1;
}

int main(int argc, char* argv[]) {

    string DataDirectory = "data";

    if (argc > 1) {
        DataDirectory = argv[1];
    }

    // Step 1: Load campus buildings
    CampusGraph graph;
    LoadBuildings(graph, DataDirectory + "/buildings.txt");

    // Step 2: Load campus connections
    LoadConnections(graph, DataDirectory + "/connections.txt");

    // Step 3: Load facilities (Member A)
    FacilityManager facilityManager;

    facilityManager.loadFacilities(
        DataDirectory + "/facilities.txt",
        graph
    );

    // Step 4: Load departments
    DepartmentTree tree;

    int deptAccepted = 0;
    int deptRejected = 0;

    tree.loadFromFile(
        DataDirectory + "/departments.txt",
        "departments.txt",
        deptAccepted,
        deptRejected
    );

    cout << "departments.txt: "
         << deptAccepted << " accepted, "
         << deptRejected << " rejected\n";

    int choice = -1;

    do {
        cout << "\n========== Smart Campus Navigation ==========\n";
        cout << "1. View all facilities\n";
        cout << "2. Search facility by ID\n";
        cout << "3. View campus graph\n";
        cout << "4. Display graph counts and degrees\n";
        cout << "5. Find reachable buildings (BFS)\n";
        cout << "6. Add department\n";
        cout << "7. Search department\n";
        cout << "8. Display department hierarchy\n";
        cout << "9. Run preorder traversal\n";
        cout << "10. Exit\n";
        cout << "=============================================\n";
        cout << "Enter your choice: ";

        choice = readChoice();

        switch (choice) {

            // MEMBER A: Display all facilities
            case 1:
                facilityManager.displayAll();
                break;

            // MEMBER A: Search facility using hash table
            case 2: {
                string id;

                cout << "\nEnter Facility ID: ";
                getline(cin, id);

                facilityManager.searchByID(id);
                break;
            }

            // GRAPH MEMBER: Display campus graph
            case 3:
                cout << "\nCampus Graph:\n";
                graph.DisplayGraph();
                break;

            // GRAPH MEMBER: Display degrees
            case 4:
                cout << "\nGraph Counts and Degrees:\n";
                graph.DisplayDegrees();
                break;

            // GRAPH MEMBER: BFS traversal
            case 5: {
                string start;

                cout << "Enter the starting building: ";
                getline(cin, start);

                start = TrimWhiteSpace(start);

                if (start.empty()) {
                    cout << "Error: starting building cannot be empty.\n";
                } else {
                    graph.BFS(start);
                }

                break;
            }

            // DEPARTMENT MEMBER: Add department
            case 6:
                addDepartmentMenu(tree);
                break;

            // DEPARTMENT MEMBER: Search department
            case 7:
                searchDepartmentMenu(tree);
                break;

            // DEPARTMENT MEMBER: Display hierarchy
            case 8:
                tree.displayHierarchy();
                break;

            // DEPARTMENT MEMBER: Preorder traversal
            case 9:
                tree.printSequence("Preorder", tree.preorder());
                break;

            case 10:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice, please try again.\n";
                break;
        }

    } while (choice != 10);

    return 0;
}
