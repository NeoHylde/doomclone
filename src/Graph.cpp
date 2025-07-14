#include "Graph.h"

Graph::Graph(Map& map) { //Need to implement functions in map for fetching components

}

std::vector<Node*> Graph::getNeighbor(Node* node) {
    auto it = adjList.find(node);
    if (it != adjList.end()) {
        return it->second;
    } else {
        return {};
    }
}
