#ifndef GRAPH_CLASS_H
#define GRAPH_CLASS_H

#include"Node.h"
#include <vector>

class Graph {
public:
    Graph(int width, int height);

    bool isBlocked(int x, int y) const;
    void setBlocked(int x, int y, bool blocked);

    std::vector<Node> getNeighbors(const Node& node) const;

    bool inBounds(int x, int y) const;

private:
    int width, height;
    std::vector<std::vector<bool>> blocked;

};

#endif

