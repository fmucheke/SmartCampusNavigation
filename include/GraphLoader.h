// File: GraphLoader.h
// Author: Franklin Mucheke
// Purpose: Declares the building and connection file loaders.

#ifndef GRAPH_LOADER_H
#define GRAPH_LOADER_H
#include "CampusGraph.h"
#include <string>

void LoadBuildings (CampusGraph& graph, const std::string& filePath);

void LoadConnections (CampusGraph& graph, const std::string& filePath);

#endif

