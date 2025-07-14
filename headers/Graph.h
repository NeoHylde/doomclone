#ifndef GRAPH_CLASS_H
#define GRAPH_CLASS_H

#include "Node.h"
#include<unordered_map>
#include<vector>
#include"Map.h"

class Graph {
public:
    Graph(Map& map);

    std::vector<Node*> getNeighbor(Node* node);
private:
    std::unordered_map<Node*, std::vector<Node*>, NodePtrHasher, NodePtrEqual> adjList;
};

#endif