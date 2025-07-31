#include "Graph.h"

// Loading Graph using map, components get searched for tiles, which are created as nodes
Graph::Graph(Map& map) {
    auto& components = map.getComponents(); 

    std::unordered_map<glm::vec2, Node*, NodeVec2Hasher> positionToNode;

    // Loops through each tile recording their position to a unique Node
    for(auto& comp : components) {
        Tile* tile = dynamic_cast<Tile*>(comp.get());
        
        if (!tile || !tile->getWalkable()) continue;

        glm::vec3 worldPos = tile->getPosition();
        
        glm::vec2 gridPos = glm::vec2(worldPos.x, worldPos.z);

        Node* node = new Node(gridPos);
        
        positionToNode[gridPos] = node;
        
        adjList[node] = {};
    }

    glm::vec2 dir[] = {
        {1, 0}, {-1, 0},  // T, B
        {1, 1}, {-1, -1}, // TR, BL
        {1, -1}, {-1, 1}, // TL, BR
        {0, 1}, {0, -1},  // R, L
    };

    // Loops through each entry of Node, and builds adjacency list by positioning
    for(auto& [pos, node] : positionToNode) {
        // Calculates possible neighbor for each node, then uses as key in positionToNode to find possible neighbors
        for(const glm::vec2& offset :  dir) {
            float gridSize = 2.0f;

            glm::vec2 neighbor = pos + offset * gridSize;
            
            auto it = positionToNode.find(neighbor);
            
            if(it != positionToNode.end()) {
                adjList[node].push_back(it->second);
            }
        }

    }
}

Node* Graph::getNodeAt(glm::vec2 worldPos) {
    for (auto& [node, _] : adjList) {

        if (node->worPos == worldPos) {

            return node;
        
        }
    }
    return nullptr;
}

void Graph::resetNodes() {
    for (auto& [node, _] : adjList) {
        node->g = INT_MAX;
        node->h = 0;
        node->parent = nullptr;
    }
}

std::vector<Node*> Graph::getNeighbor(Node* node) {
    auto it = adjList.find(node);
    if (it != adjList.end()) {
        return it->second;
    } else {
        return {};
    }
}

void Graph::Delete() {
    for (auto& [key, _] : adjList) {
        delete key;
    }
    adjList.clear();
}

