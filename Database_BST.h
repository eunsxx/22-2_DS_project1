//
// Created by 이은서 on 2022/10/12.
//

#ifndef PROJECT1_DATABASE_BST_H
#define PROJECT1_DATABASE_BST_H


#include "Stack.h"
#include "ImageNode.h"
#include "Database_BST_Node.h"


class Database_BST {
    friend class Stack;
private:
    Database_BST_Node* root;
    Database_BST_Node* tail;
    Database_BST_Node* stack[300];
    int top;

    void Inorder(Database_BST_Node* curr, ofstream& fout);

public:
    Database_BST();

    void Iter_Postorder(Stack s, Stack out, string word, ofstream& fout);
    Database_BST_Node* Iter_Preorder(int num);
    void AddTreeNode(Node* tail);
    string SearchImage(int num);
    void Print(ofstream& fout);
    void MOVE(Node* moveNode, Loaded_LIST_Node* moveFile, Loaded_LIST_Node* dirHead);
    void Table(string str, int size, int table[]);
    void BoyerMoore(string word, Database_BST_Node* str, ofstream& fout);
    Result BSTisEmpty() {
        if (root == nullptr) return PrintError;
        else return Success;
    }
};


#endif //PROJECT1_DATABASE_BST_H
