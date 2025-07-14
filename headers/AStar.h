#ifndef A_STAR_CLASS_H
#define A_STAR_CLASS_H

#include"Graph.h"
#include<vector>
#include<unordered_set>
#include<queue>

class AStar {
public:
    AStar(Graph* graph);

    std::vector<Node> backTrackPath(Node* node);

    bool inVisited(Node* node);

    float heuristic(const Node* a, const Node* b);

    std::vector<Node> getPath(Node* start, Node* end);    
private:
    Graph* graph;

    std::unordered_set<Node, NodePtrHasher> visited;

    struct CompareNode {
        bool operator()(const Node* a, const Node* b) const {
            return a->getF() > b->getF();
        }
    };

    std::priority_queue<Node*, std::vector<Node*>, CompareNode> frontier;
};

#endif