// File: main.cpp
// Authors: Urisha Shrestha, Franklin Mucheke, Samriddi Upreti
// Purpose: Coordinates file loading and the final main menu.
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

// Read a menu choice
int readChoice() {
    string line;

    if (!getline(cin, line)) {
        return 18;
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

    int choice=0;

    for (char c : line) {
        choice= choice*10 + (c-'0');

        if(choice>18){
            return -1;
        }
    }

    if (choice<1 || choice>18){
        return -1;
    }

    return choice;

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
        cout << "3. Search facility by name\n";
        cout << "4. Search facility by category\n";
        cout << "5. View campus graph\n";
        cout << "6. Display graph counts and degrees\n";
        cout << "7. Find reachable buildings(BFS)\n";
        cout << "8. Find shortest path\n";
        cout << "9. Add department\n";
        cout << "10. Search department\n";
        cout << "11. Display department hierarchy\n";
        cout << "12. Preorder traversal\n";
        cout << "13. Postorder traversal\n";
        cout << "14. Level-order traversal\n";
        cout << "15. Department statistics\n";
        cout << "16. Facility category report\n";
        cout << "17. Graph connectivity report\n";
        cout << "18. Exit\n";
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

          // MEMBER A: Search facility by complete name
            case 3: {
                string name;

                cout << "\nEnter facility name: ";
                getline(cin, name);

                if (StandardizeName(name).empty()) {
                    cout << "Error: Facility name cannot be blank.\n";
                    break;
                }

                facilityManager.searchByName(name);
                break;
            }

            // MEMBER A: Search facility by complete category
            case 4: {
                string category;

                cout << "\nEnter facility category: ";
                getline(cin, category);

                if (StandardizeName(category).empty()) {
                    cout << "Error: Category cannot be blank.\n";
                    break;
                }

                facilityManager.searchByCategory(category);
                break;
            }

            // GRAPH MEMBER: Display campus graph
            case 5:
                cout << "\nCampus Graph:\n";
                graph.DisplayGraph();
                break;

            // GRAPH MEMBER: Display degrees
            case 6:
                cout << "\nGraph Counts and Degrees:\n";
                graph.DisplayDegrees();
                break;

            // GRAPH MEMBER: BFS traversal
            case 7: {
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

            case 8:{
                string start;
                string destination;

                cout<<"Enter the starting building: "<<endl;
                getline(cin, start);
                start= TrimWhiteSpace(start);

                if(start.empty()){
                    cout<<"Invalid, start building cannot be empty"<<endl;
                    break;
                }

                cout<<"Enter the destination building: "<<endl;
                getline(cin, destination);
                destination= TrimWhiteSpace(destination);

                if (destination.empty()){
                    cout<<"Invalid, destination building cannot be empty"<<endl;
                    break;
                }

                graph.ShortestPath(start,destination);
                break;
            }

            // DEPARTMENT MEMBER: Add department
            case 9:
                addDepartmentMenu(tree);
                break;

            // DEPARTMENT MEMBER: Search department
            case 10:
                searchDepartmentMenu(tree);
                break;

            // DEPARTMENT MEMBER: Display hierarchy
            case 11:
                tree.displayHierarchy();
                break;

            //  Preorder traversal
            case 12:
                tree.printSequence("Preorder", tree.preorder());
                break;
            
                       // Postorder traversal
            case 13:
                tree.printSequence("Postorder", tree.postorder());
                break;

            //  Level-order traversal
            case 14:
                tree.printSequence("Level-order", tree.levelOrder());
                break;

            //  Department statistics
            case 15:
                tree.displayStatistics();
                break;

            //  Facility category report
            case 16:
                facilityManager.categoryReport();
                break;

            case 17:
                graph.ConnectivityReport();
                break;

            case 18:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice, please try again.\n";
                break;
        }

    } while (choice != 18);

    return 0;
}
