// File: CampusGraph.cpp
// Author: Franklin Mucheke
// Purpose: Implements the campus graph, adjacency lists, and BFS.

#include "CampusGraph.h"
#include "FileUtils.h"
#include <iostream>
#include <queue>
using namespace std;


int CampusGraph::FindBuildingIndex(const string& name) const{
    string target= StandardizeName(name);

    for (int i=0; i< static_cast<int>(buildings.size()); i++){
        if(StandardizeName(buildings[i])== target){
            return i;
        }

    }
return -1;
}

bool CampusGraph:: AddBuilding(const string& name){
    string building= TrimWhiteSpace(name);

    if (building.size()==0){
         cout<<"Building name has to be a valid string"<<endl;
         return false;
    }

    if (FindBuildingIndex(building)!=-1){
        cout<<"Building already exists"<< endl;
        return false;
    }

    buildings.push_back(TrimWhiteSpace(name));
    adjacencyList.emplace_back();

    return true;

}

bool CampusGraph:: BuildingExists(const string& name) const{
    if(FindBuildingIndex(name)!=-1){
        return true;
    }
return false;
}

bool CampusGraph:: AddConnection(const string& a, const string& b){
    int aIndex=FindBuildingIndex(a);
    int bIndex=FindBuildingIndex(b);

    if (aIndex== -1 || bIndex==-1){
        cout<<"Both buildings have to exist for a connection to be added."<<endl;
        return false;
    }

    if (aIndex==bIndex){
        cout<<"Attempted connection is a self loop and therefore invalid"<<endl;
        return false;
    }

    for (int neighbor: adjacencyList[aIndex]){
        if (neighbor==bIndex){
        cout<< "Connection already exists"<<endl;
        return false;
        }
    }

    adjacencyList[bIndex].emplace_back(aIndex);
    adjacencyList[aIndex].emplace_back(bIndex);
    ConnectionCount+=1;

    return true;

}

void CampusGraph::DisplayGraph() const{
    if(buildings.empty()){
        cout<< "There are no buildings"<<endl;
        return;
    }

    for(size_t i=0; i<buildings.size(); i++){
        cout<<buildings[i]<<": ";

        if (adjacencyList[i].size()!=0){
            for(size_t j=0; j< adjacencyList[i].size(); j++){
                int neighbor= adjacencyList[i][j];
                cout<<buildings[neighbor];
                if(j<adjacencyList[i].size()-1){
                    cout<<", ";
                }
            }
        }
        else{
            cout<<"(no connections)";
        }
        cout<<endl;
        }
    }

void CampusGraph::DisplayDegrees() const{
    cout<<"Total Buildings: "<<buildings.size()<<endl;

    cout<<"Total Connections: "<<ConnectionCount<<endl;

    for(size_t i= 0; i< buildings.size(); i++){
        cout<<buildings[i]<<": "<<adjacencyList[i].size()<<endl;

    }

}

void CampusGraph::BFS(const string& start) const{
    int buildingIndex=FindBuildingIndex(start);

    if(buildingIndex==-1){
        cout<<"The starting building does not exist"<<endl;
        return;
    }

    queue<int> unexploredQueue;
    vector<bool> discoveredBuildings(buildings.size(), false);
    vector<int>  distance(buildings.size(), -1);

    discoveredBuildings[buildingIndex]=true;
    distance[buildingIndex]=0;
    unexploredQueue.push(buildingIndex);
    int reachableCount=0;

    while(!unexploredQueue.empty()){
        int first=unexploredQueue.front();
        unexploredQueue.pop();
        reachableCount+=1;

        cout<<buildings[first]<<": distance "
        << distance[first]<< endl;

        for(int neighbor: adjacencyList[first]){
            if (discoveredBuildings[neighbor]==false){
                discoveredBuildings[neighbor]=true;
                distance[neighbor]=distance[first]+1;
                unexploredQueue.push(neighbor);
            }
        }
    }

    cout<<"Reachable Buildings: "<<reachableCount<<" out of "<<buildings.size()<<endl;

}

string CampusGraph::GetBuildingName(const string& name) const {
    int index= FindBuildingIndex(name);

    if (index==-1){
        return "";
    }

    return buildings[index];
}