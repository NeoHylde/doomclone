#ifndef NODE_CLASS_H
#define NODE_CLASS_H

class Node {
public:
    int x,y;
    int g;
    int h;
    int f() const {return g+h;};

    Node* parent = nullptr;

    Node(int x, int y) : x(x) , y(y) {}

    bool operator==(const Node& other) {
        return x == other.x && y == other.y; 
    }

    bool operator>(const Node& other) {
        return f() > other.f();
    }
};

#endif