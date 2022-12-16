//
// Created by 이은서 on 2022/10/12.
//

#ifndef PROJECT1_QUEUE_H
#define PROJECT1_QUEUE_H

#include "Database_BST_Node.h"

class Queue {
public:
    int data;
    int arr[256*256];
    int front;
    int rear;
    int size;

public:
    Queue() {
        front = 0;
        rear = 0;
        size = 0;
    }

    void push(int data) {
        if (!is_full()) {
            arr[rear] = data;
            rear = (rear+1) % (256*256);
            size++;
        } else cout << "Full" << endl;
    }

    int Front() {
        if (is_empty()) {
            cout << "empty" << endl;
            return 0;
        }
        else {
            return arr[front];
        }
    }

    bool is_empty() {
        return size == 0;
    }

    bool is_full() {
        return size == 256*256;
    }

    int pop() {
        int frontData = Front();
        front = (front + 1) % (256*256);
        size--;
        return frontData;
    }

};

#endif //PROJECT1_QUEUE_H
