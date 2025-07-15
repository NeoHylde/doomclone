#include "AStar.h"

AStar::AStar(Graph* graph) : graph(graph) {}

glm::vec3 AStar::toVec3F(Node node) {
    return glm::vec3((float)node.worPos.x, 0.0f, (float)node.worPos.y);
}

std::vector<glm::vec3> AStar::backTrackPath(Node* node) {
    std::vector<glm::vec3> path;
    while(node != nullptr) {
        path.emplace_back(toVec3F(*node));
        node = node->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

bool AStar::inVisited(Node* node) {
    return visited.find(node) != visited.end();
}

float AStar::heuristic(const Node* a, const Node* b) {
    glm::vec2 delta = a->worPos - b->worPos;
    return glm::length(delta);
}

std::vector<glm::vec3> AStar::getPath(Node* start, Node* end) {
    graph->resetNodes();
    visited.clear();
    while (!frontier.empty()) frontier.pop();

    start->g = 0;
    start->h = heuristic(start, end);
    frontier.push(start);


    while(!frontier.empty()) {
        //Pops top (lowest f cost node)
        Node* node = frontier.top();
        frontier.pop();
        visited.emplace(node);

        if(node == end) {
            return backTrackPath(node);
        }
        

        std::vector<Node*> neighbors = graph->getNeighbor(node);

        for (Node* neighbor : neighbors) {
            // Only checks univisited nodes
            if (inVisited(neighbor)) continue;

            //our current cost to get to neighbor
            int tentativeG = node->g + 1;

            if (tentativeG < neighbor->g) {
                neighbor->g = tentativeG;
                neighbor->h = heuristic(neighbor, end);
                neighbor->parent = node;
                frontier.push(neighbor);
            }
        }

    }

    return {};
}