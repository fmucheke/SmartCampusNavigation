#include "GraphLoader.h"
#include "FileUtils.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void LoadBuildings(CampusGraph& graph, const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()){
        cout<<"Error, unable to open "<<filePath<<endl;
        cout<< filePath <<": 0 accepted, 0 rejected"<<endl;
        return;
    }

    int accepted=0;
    int rejected=0;

    string line;
    int lineNumber=0;

    while (getline(file,line)) {
        lineNumber++;

        string building= TrimWhiteSpace(line);

        if (building.empty()){
            continue;
        }

        if (building[0]=='#'){
            continue;
        }

        if (building.find('|')!= string::npos){
            rejected++;

                cout<<"Warning: " <<filePath
                <<", line: "<<lineNumber
                <<": too many fields in building record"
                <<endl;
            continue;
        }

        if (graph.AddBuilding(building)){

            accepted+=1;
        }
        else{
            rejected+=1;
            cout<<"Warning: " <<filePath
                <<", line: "<<lineNumber
                <<": Duplicate building: "<<building
                <<endl;

        }
    }

    cout<<filePath<<": "
        <<accepted<<" accepted, "
        <<rejected<<" rejected"
        <<endl;

}

void LoadConnections(CampusGraph& graph, const string& filePath){
    ifstream file(filePath);
    if (!file.is_open()){
        cout<<"Error, unable to open "<<filePath<<endl;
        cout<< filePath <<": 0 accepted, 0 rejected"<<endl;
        return;
    }

    int accepted=0;
    int rejected=0;

    string line;
    int lineNumber=0;

    while (getline(file,line)) {
        lineNumber++;

        string building= TrimWhiteSpace(line);

        if (building.empty()){
            continue;
        }

        if (building[0]=='#'){
            continue;
        }

        size_t separator= building.find('|');

        if (separator==string::npos) {

            rejected++;

            cout<<"Warning: "<< filePath
                <<", line "<< lineNumber
                <<": Missing | separator"
                <<endl;
            
            continue;
        }

        if (building.find('|', separator + 1)!=string::npos) {

            rejected++;

            cout<<"Warning: "<< filePath
                <<", line "<< lineNumber
                <<": too many fields"
                <<endl;
            
            continue;
        }

        string BuildingA= TrimWhiteSpace(building.substr(0, separator));

        string BuildingB= TrimWhiteSpace(building.substr(separator+1));

        if (BuildingA.empty() || BuildingB.empty()){
            rejected++;

             cout<<"Warning: "<< filePath
                <<", line "<< lineNumber
                <<": empty building name"
                <<endl;

            continue;
        }

        if (!graph.BuildingExists(BuildingA) || !graph.BuildingExists(BuildingB)){
            rejected++;

             cout<<"Warning: "<< filePath
                <<", line "<< lineNumber
                <<": unknown building in connection: "
                <<BuildingA<<"|"<<BuildingB
                <<endl;

            continue;
        }

        if (StandardizeName(BuildingA)==StandardizeName(BuildingB)){
            rejected++;

             cout<<"Warning: "<< filePath
                <<", line "<< lineNumber
                <<": self connection"
                <<endl;

            continue;
        }



        if (graph.AddConnection(BuildingA,BuildingB)){
            accepted++;

        }
        else{
            rejected++;

            cout<<"Warning: "<< filePath
                <<", line "<< lineNumber
                <<": Duplicate connection: "
                << BuildingA << "|" <<BuildingB
                <<endl;
        }

    }

        cout<<filePath<<": "
        <<accepted<<" accepted, "
        <<rejected<<" rejected"
        <<endl;

}