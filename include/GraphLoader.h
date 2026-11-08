#ifndef GRAPH_LOADER_H
#define GRAPH_LOADER_H
#include "CampusGraph.h"
#include <string>

void LoadBuildings (CampusGraph& graph, const std::string& filePath);

void LoadConnections (CampusGraph& graph, const std::string& filePath);

#endif

