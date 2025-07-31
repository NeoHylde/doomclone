#ifndef NODE_CLASS_H
#define NODE_CLASS_H

#include<glm/glm.hpp>
#include <functional>



class Node {
public:
    int h;
    int g = INT_MAX;
    int f;
    
    glm::vec2 worPos;
    
    int getF() const { return g + h; }

    Node(glm::vec2 position) : worPos(position) {}
    
    Node* parent = nullptr;

    bool operator==(const Node& a) const {
        return (this->worPos.x == a.worPos.x) && (this->worPos.y == a.worPos.y);
    }

    bool operator>(const Node& a) const {
        return (this->getF()) > (a.getF());
    }
private:
    
    
};

struct NodePtrHasher {
    std::size_t operator()(const Node* node) const {
        // Hash using position values (value-based hashing)
        std::hash<float> floatHasher;
        return floatHasher(node->worPos.x) ^ (floatHasher(node->worPos.y) << 1);
    }
};

struct NodePtrEqual {
    bool operator()(const Node* a, const Node* b) const {
        return a->worPos.x == b->worPos.x && a->worPos.y == b->worPos.y;
    }
};

#endif