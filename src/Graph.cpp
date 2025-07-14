#include "Graph.h"

Graph::Graph(int width, int height) : width(width), height(height), blocked(width, std::vector<bool>(height, false)) {}

void Graph::setBlocked(int x, int y, bool value){
    if (inBounds(x, y)) {
        blocked[x][y] = value;
    }
}

bool Graph::isBlocked(int x, int y) const {
    return inBounds(x, y) ? blocked[x][y] : true;
}

std::vector<Node> Graph::getNeighbors(const Node& node) const {
    std::vector<Node> neighbors;
    const int dx[] = {1, 1, -1, -1, -1, 1, 0, 0};
    const int dy[] = {1, -1, 1, -1, 0, 0, 1, -1};

    for(int i = 0; i < 8; i++) {
        if(inBounds(node.x + dx[i], node.y + dy[i]) && !isBlocked(node.x + dx[i], node.y + dy[i])) {
            neighbors.emplace_back(node.x + dx[i], node.y + dy[i]);
        }
    }

    return neighbors;
}

bool Graph::inBounds(int x, int y) const {
    return (x < width) && (y < height);
}