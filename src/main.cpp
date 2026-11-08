
#include <iostream>
#include <string>
#include <limits>

#include "FacilityManager.h"
#include "DepartmentTree.h"
#include "CampusGraph.h"
#include "GraphLoader.h"

using namespace std;

// Facility management menu
void facilityMenu(FacilityManager& manager) {
    int choice = -1;
    string input;

    do {
        cout << "\n========== Facility Management ==========\n";
        cout << "1. Display All Facilities\n";
        cout << "2. Search Facility by ID\n";
        cout << "6. Hash Table Statistics\n";
        cout << "0. Return to Main Menu\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            if (cin.eof()) {
                return;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "\nAll Campus Facilities:\n";
                manager.displayAll();
                break;

            case 2:
                cout << "\nEnter Facility ID: ";
                getline(cin, input);
                manager.searchByID(input);
                break;

            case 6:
                manager.displayHashStats();
                break;

            case 0:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }

    } while (choice != 0);
}

// Check for blank input
bool isBlank(string s) {
    for (char c : s) {
        if (c != ' ' && c != '\t' && c != '\r') {
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

// Read a single-digit menu choice
int readChoice() {
    string line;

    if (!getline(cin, line)) {
        return 0;
    }

    if (line.size() == 1 &&
        line[0] >= '0' &&
        line[0] <= '9') {
        return line[0] - '0';
    }

    return -1;
}

int main(int argc, char* argv[]) {
    string dataDir = "data";

    if (argc > 1) {
        dataDir = argv[1];
    }

    // Load campus buildings and connections
    CampusGraph campusGraph;

    LoadBuildings(campusGraph, dataDir + "/buildings.txt");
    LoadConnections(campusGraph, dataDir + "/connections.txt");

    // Load Member A facilities
    FacilityManager facilityManager;
    facilityManager.loadFacilities(
        dataDir + "/facilities.txt",
        campusGraph
    );

    // Load departments
    DepartmentTree tree;

    int deptAccepted = 0;
    int deptRejected = 0;

    tree.loadFromFile(
        dataDir + "/departments.txt",
        "departments.txt",
        deptAccepted,
        deptRejected
    );

    cout << "departments.txt: "
         << deptAccepted << " accepted, "
         << deptRejected << " rejected\n";

    int choice = -1;

    do {
        cout << "\n========== Smart Campus System ==========\n";
        cout << "1. Facility Management\n";
        cout << "6. Add department\n";
        cout << "7. Search department\n";
        cout << "8. Display department hierarchy\n";
        cout << "9. Run preorder traversal\n";
        cout << "0. Exit\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";

        choice = readChoice();

        switch (choice) {
            case 1:
                facilityMenu(facilityManager);
                break;

            case 6:
                addDepartmentMenu(tree);
                break;

            case 7:
                searchDepartmentMenu(tree);
                break;

            case 8:
                tree.displayHierarchy();
                break;

            case 9:
                tree.printSequence("Preorder", tree.preorder());
                break;

            case 0:
                cout << "Goodbye.\n";
                break;

            default:
                cout << "Invalid choice. Please enter 0 to 9.\n";
                break;
        }

    } while (choice != 0);

    return 0;
}
