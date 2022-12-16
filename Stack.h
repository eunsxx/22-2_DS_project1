//
// Created by 이은서 on 2022/10/12.
//

#ifndef PROJECT1_STACK_H
#define PROJECT1_STACK_H

#include "Database_BST_Node.h"
#include "ImageNode.h"

class Stack {
    friend class Database_BST;
public:
    Database_BST_Node* stack[300];
    int top;

    Stack() {
        top = -1;
    }

    Database_BST_Node* pop() {
        Database_BST_Node* node = nullptr;
        if (top == -1) return node; // if top is negative, this Stack is empty
        node = stack[top];
        top--;
        return node;
    }

    void push(Database_BST_Node* node) {
        if (top > 300) return;
        top++;
        stack[top] = node;
    }

    bool is_empty() {
        if(top == -1 ) return true;
        else return false;
    }

    Database_BST_Node* Top() { return stack[top]; }
};

class fileStack {
    int data;
    int arr[512*512];
    int top;
public:
    fileStack(){ top = -1; }

    void Push(int data) {
        arr[++top] = data;
    }

    bool empty() {
        return (top < 0);
    }

    int Pop() {
        if (empty()) {
            return -1;
        }
        return arr[top--];
    }

    int size() {
        return top + 1;
    }

    int Top() {
        if (empty()) {
            return -1;
        }
        return arr[top];
    }
};


#endif
