//
// Created by Thuy Le on 8/1/25.
//

#include "RedBlackTree.h"
#include <iostream>
using namespace std;

//node constructor
RedBlackTree::Node::Node(const weightedGame& d)
    : data(d), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

//initialize TNULL sentinel
void RedBlackTree::initTNULL() {
    TNULL = new Node(weightedGame(Game("", "", ""), 0));
    TNULL->color = BLACK;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
}

//constructor
RedBlackTree::RedBlackTree() {
    initTNULL();
    root = TNULL;
}

//left rotate
void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    //move y's left subtree to x->right
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    //link x's parent to y
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    //put x as y's left child
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    //move y's right subtree to x->left
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    //link x's parent to y
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    //put x as y's right child
    y->right = x;
    x->parent = y;
}

//insertion
void RedBlackTree::insert(const weightedGame& key) {
    Node* node = new Node(key);
    node->left = TNULL;
    node->right = TNULL;
    node->parent = nullptr;

    Node* y = nullptr;
    Node* x = root;

    //bst insert
    while (x != TNULL) {
        y = x;
        if (node->data.score < x->data.score) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    }
    else if (node->data.score < y->data.score) {
        y->left = node;
    }
    else {
        y->right = node;
    }

    //new node is red by default + fix violations
    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }
    if (node->parent->parent == nullptr) {
        return;
    }

    insertFix(node);
}

//fix-up to maintain RedBlack properties
void RedBlackTree::insertFix(Node* k) {
    Node* u;
    while (k->parent && k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            u = k->parent->parent->right;
            if (u && u->color == RED) {
                //case 1: uncle is red
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    //case 2: triangle formation
                    k = k->parent;
                    leftRotate(k);
                }
                //case 3: line formation
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->left;
            if (u && u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    //case 2: triangle formation
                    k = k->parent;
                    rightRotate(k);
                }
                //case 3: line formation
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        }
        if (k == root) break;
    }
    root->color = BLACK;
}

//reverse inorder traversal to collect high scores
void RedBlackTree::reverseInOrder(Node* node, vector<weightedGame>& out, int& count, int k) {
    if (node == TNULL || count >= k) {
        return;
    }
    reverseInOrder(node->right, out, count, k);
    if (count < k) {
        out.push_back(node->data);
        count++;
        reverseInOrder(node->left, out, count, k);
    }
}

//get top k entries
vector<weightedGame> RedBlackTree::getTopK(int k) {
    vector<weightedGame> result;
    int count = 0;
    reverseInOrder(root, result, count, k);
    return result;
}
