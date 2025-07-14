#include "AStar.h"

AStar::AStar(Graph& g) : graph(g) {
}

int AStar::heuristic(Node& a, Node& b) {
    return static_cast<int>(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2))); //Euclidean dist
}

Node AStar::toGridNode(const glm::vec3& pos) const {
    return Node(pos.x, pos.y);
}

glm::vec3 AStar::toWorldPos(const Node& node) const {
    return glm::vec3((float)node.x, 0.0f , (float) node.y);
}

bool AStar::isInClosedSet(const Node& node, const std::unordered_set<Node>& closedSet) const {
    return closedSet.find(node) != closedSet.end();
}

Node* AStar::getNodeFromOpenSet(const Node& node, std::vector<Node*>& openSet) const {
    for (Node* n : openSet) {
        if (*n == node) {
            return n;
        }
    }
    return nullptr;
}

Node* AStar::getLowestFNode(std::vector<Node*>& openSet) {
    Node* low = openSet[0];
    for(Node* n : openSet) {
        if (n->f() < low->f()) {
            low = n;
        }
    }
    return low;
}

std::vector<Node> AStar::reconstructPath(Node* node) {
    std::vector<Node> path;

    while(node != nullptr) {
        path.push_back(*node);
        node = node->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Node> AStar::getPath(glm::vec3 start, glm::vec3 end) {
    Node startNode = toGridNode(start);
    Node endNode = toGridNode(end);

    std::unordered_set<Node> closedSet;
    std::vector<Node*> openSet;
    std::unordered_map<Node, Node> cameFrom;

    openSet.push_back(new Node(startNode));

    while(!openSet.empty()) {
        Node* current = getLowestFNode(openSet);
        if(*current == endNode) {
            for(Node* n : openSet) {
                delete n;
            }
            return reconstructPath(current);
        }

        closedSet.insert(*current);
        openSet.erase(std::remove(openSet.begin(), openSet.end(), current), openSet.end());

        for(Node neighbor : graph.getNeighbors(*current)) {
            if(closedSet.count(neighbor)) continue;

            int G =  current->g + 1;
            bool inOpenSet = false;

            for(Node* node : openSet) {
                if(*node == neighbor) {
                    inOpenSet = true;
                    if(G < node->g) {
                        node->g = G;
                        node->parent = current;
                    }
                    break;
                }
            }

            if(!inOpenSet) {
                Node* node = new Node(neighbor);
                node->g = G;
                node->h = heuristic(*node, endNode);
                node->parent = current;
                openSet.push_back(node);
            }
        }
    }

    for(Node* n : openSet) {
        delete n;
    }
    return {};
}