#ifndef ASTAR_CLASS_H
#define ASTAR_CLASS_H

#include <glm/glm.hpp>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "Graph.h"

class AStar {
public:

    Graph graph;

    AStar(Graph& g);

    std::vector<Node> getPath(glm::vec3 start, glm::vec3 end);

    int heuristic(Node& a, Node& b);
private:
    Node toGridNode(const glm::vec3& pos) const;
    glm::vec3 toWorldPos(const Node& node) const;
    Node* getLowestFNode(std::vector<Node*>& openSet);
    std::vector<Node> reconstructPath(Node* node);

    bool isInClosedSet(const Node& node, const std::unordered_set<Node>& closedSet) const;
    Node* getNodeFromOpenSet(const Node& node, std::vector<Node*>& openSet) const;
};

#endif