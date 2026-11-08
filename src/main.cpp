#include <iostream>
#include <string>
#include <limits>
#include "FacilityManager.h"
#include "CampusGraph.h"
#include "GraphLoader.h"
#include "FileUtils.h"


using namespace std;

// This function handles the facility menu
void facilityMenu(FacilityManager& manager) {

    int choice = -1;
    string input;

    do {
        // Display the facility menu
        cout << "\n========== Facility Management ==========\n";
        cout << "1. Display All Facilities\n";
        cout << "2. Search Facility by ID\n";
        cout << "3. Search Facility by Name\n";
        cout << "4. Search Facility by Category\n";
        cout << "5. Facility Category Report\n";
        cout << "6. Hash Table Statistics\n";
        cout << "0. Return to Main Menu\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";

        // Check if the user entered a valid number
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            choice = -1;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Run the option selected by the user
        switch (choice) {

            case 1:
                // Show all facilities
                cout << "\nAll Campus Facilities:\n";
                manager.displayAll();
                break;

            case 2:
                // Search for a facility using its ID
                cout << "\nEnter Facility ID: ";
                getline(cin, input);
                manager.searchByID(input);
                break;

            case 3:
                // Search facilities by their name
                cout << "\nEnter Facility Name: ";
                getline(cin, input);
                manager.searchByName(input);
                break;

            case 4:
                // Find facilities in a specific category
                cout << "\nEnter Facility Category: ";
                getline(cin, input);
                manager.searchByCategory(input);
                break;

            case 5:
                // Display the number and percentage of each category
                cout << "\nFacility Category Report:\n";
                manager.categoryReport();
                break;

            case 6:
                // Show the hash table information
                cout << "\nHash Table Statistics:\n";
                manager.displayHashStats();
                break;

            case 0:
                // Go back to the main menu
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice. Try again.\n";
                break;
        }

    } while (choice != 0);
}

int main(int argc, char* argv[]){

    string DataDirectory= "data";

    if (argc>1) {
        DataDirectory= argv[1];
    }

    CampusGraph graph;

    LoadBuildings(graph, DataDirectory + "/buildings.txt");
    LoadConnections(graph, DataDirectory + "/connections.txt");

    int choice= -1;

    do {
        cout<<"\n========== Smart Campus Navigation ==========\n";
        cout<<"1. View all facilities\n";
        cout<<"2. Search facility by ID\n";
        cout<<"3. View campus graph\n";
        cout<<"4. Display graph counts and degrees\n";
        cout<<"5. Find reachable buildings (BFS)\n";
        cout<<"6. Add department\n";
        cout<<"7. Search department\n";
        cout<<"8. Display department hierarchy\n";
        cout<<"9. Run preorder traversal\n";
        cout<<"10. Exit\n";
        cout<<"=============================================\n";
        cout<<"Enter your choice: ";


        if (!(cin >> choice)) {
            if (cin.eof()) {
                cout<<"\nInput ended, exiting the program.\n";
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            choice = -1;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
            //member A
                break;
            case 2:
            //member A
                break;
            case 3:
                cout<<"\nCampus Graph:\n";
                graph.DisplayGraph();
                break;
            case 4:
                cout<<"\nGraph Counts and Degrees:\n";
                graph.DisplayDegrees();
                break;
            case 5:{
                string start;

                cout<<"Enter the starting building: ";
                getline(cin,start);
                start= TrimWhiteSpace(start);

                if (start.empty()){
                    cout<<"Error: starting building cannot be an empty string"<<endl;
                }
                else{
                    graph.BFS(start);
                }
                break;
            }
            case 6:
            //member C
                break;
            case 7:
            //member C
                break;
            case 8:
            //member C
                break;
            case 9:
            //member C
                break;
            case 10:
                cout<<"Exiting program.... \n";
                break;
            default:
                cout<<"Invalid choice, please try again.\n";
                break;


        }
    


    } while (choice!=10);

    return 0;
}