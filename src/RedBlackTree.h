//
// Created by Thuy Le on 8/1/25.
//

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include "Game.h"
#include <vector>
using namespace std;
// RedBlack Tree for weightedGame entries (ordered by score)

enum Color { RED, BLACK };

class RedBlackTree {
private:
    struct Node {
        weightedGame data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;
        Node(const weightedGame& d);
    };

    Node* root;
    Node* TNULL;  // sentinel

    void initTNULL();
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void insertFix(Node* k);
    void reverseInOrder(Node* node, vector<weightedGame>& out, int& count, int k);

public:
    RedBlackTree();
    void insert(const weightedGame& key);
    vector<weightedGame> getTopK(int k);
};

#endif // REDBLACKTREE_H
