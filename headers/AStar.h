#ifndef A_STAR_CLASS_H
#define A_STAR_CLASS_H

#include "Graph.h"

#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

class AStar {
public:
    AStar(Graph* graph);

    std::vector<glm::vec3> backTrackPath(Node* node);

    glm::vec3 toVec3F(Node node);

    bool inVisited(Node* node);

    float heuristic(const Node* a, const Node* b);

    std::vector<glm::vec3> getPath(Node* start, Node* end);    

    Graph* graph;
private:

    std::unordered_set<Node*, NodePtrHasher, NodePtrEqual> visited;
    
    struct CompareNode {
        bool operator()(const Node* a, const Node* b) const {
            return a->getF() > b->getF();
        }
    };

    std::priority_queue<Node*, std::vector<Node*>, CompareNode> frontier;
};

#endif