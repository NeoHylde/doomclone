#ifndef GRAPH_CLASS_H
#define GRAPH_CLASS_H

#include "Node.h"
#include<unordered_map>
#include<vector>
#include"Map.h"

class Graph {
public:
    Graph(Map& map);

    struct NodeVec2Hasher {
    std::size_t operator()(const glm::vec2& v) const {
        auto h1 = std::hash<float>{}(v.x);
        auto h2 = std::hash<float>{}(v.y);
        return h1 ^ (h2 << 1);  // Combine the hashes
    }
};


    std::vector<Node*> getNeighbor(Node* node);

    Node* getNodeAt(glm::vec2 worldPos);

    void resetNodes();

    void Delete();
private:
    std::unordered_map<Node*, std::vector<Node*>, NodePtrHasher, NodePtrEqual> adjList;
};

#endif