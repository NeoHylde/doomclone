#include "AStar.h"

AStar::AStar(Graph* graph) : graph(graph) {}

std::vector<Node> AStar::backTrackPath(Node* node) {
    std::vector<Node> path;
    while(node != nullptr) {
        path.emplace_back(node);
        node = node->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

bool AStar::inVisited(Node* node) {
    return visited.find(*node) != visited.end();
}

float AStar::heuristic(const Node* a, const Node* b) {
    glm::vec2 delta = a->worPos - b->worPos;
    return glm::length(delta);
}


std::vector<Node> AStar::getPath(Node* start, Node* end) {
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