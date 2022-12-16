#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#define RANGE 256

using namespace std;

class Database_BST_Node { // tree has information about name, directory name and unique number
public:
//    Database_BST_Node* next; // next stack. It is only used in Stack
    Database_BST_Node* left; // left node
    Database_BST_Node* right; // right node
    string name; // image name
    int num; // image unique number
    string dir; // directory name

    Database_BST_Node(string name, int num, string dir) {
        this->name = name;
        this->num = num;
        this->dir = dir;
        left = right = nullptr;
    }
};

#endif