#include "Database_BST.h"

void Database_BST::Inorder(Database_BST_Node* curr, ofstream& fout) { // In-order travelsal
    if (curr != nullptr) {
        Inorder(curr->left, fout);
        fout << curr->dir << " / \"" << curr->name << "\" / " << curr->num << endl;
        Inorder(curr->right, fout);
    }
}

Database_BST::Database_BST() {
    root = nullptr;
}

void Database_BST::Iter_Postorder(Stack s, Stack out, string word, ofstream& fout) { // Iterative Post-order traversal
    if (root == nullptr) return;
    s.push(root);

    while(!s.is_empty()) { // it is not empty
        Database_BST_Node* curr = s.Top();
        s.pop();

        out.push(curr);

        if (curr->left != nullptr) {
            s.push(curr->left);
        }
        if (curr->right != nullptr) {
            s.push(curr->right);
        }
    }

    while (!out.is_empty()) { // until out is empty
        Database_BST_Node* str = out.Top();
        BoyerMoore(word, str, fout);
        out.pop();
    }
}

Database_BST_Node* Database_BST::Iter_Preorder(int num) { // Iterative pre-order traversal
    Database_BST_Node* selectImageNode = nullptr;
    if (root == nullptr) return nullptr;
    Stack s;
    s.push(root);
//        Stack out; // From now on, it is used as queue

    while(!s.is_empty()) { // stack is not empty
        Database_BST_Node* curr = s.Top();
        s.pop();

        if (curr->num == num) { // visit node first
            selectImageNode = curr;
            return selectImageNode;
        }

        if (curr->right != nullptr) { // and then, visit right node
            s.push(curr->right);
        }
        if (curr->left != nullptr) { //finally, visit left node
            s.push(curr->left);
        }
        // right 먼저 해야 나올때 left먼저 나옴
    }

    return selectImageNode;
}

string Database_BST::SearchImage(int num) {
    Database_BST_Node* curr = Iter_Preorder(num);

    if (curr != nullptr) {
        return curr->name;
    } else return "0";
};

void Database_BST::Table(string str, int size, int *table) { // skip table
    for (int i = 0; i < RANGE; i++) {
        table[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        int index = (int)str[i];
        table[index] = i; // Save indexes where ASCII values of characters are located
    }
}

void Database_BST::BoyerMoore(string word, Database_BST_Node* str, ofstream& fout) {
    string file = str->name;
    int wordTable[RANGE];
    int moveCount = 0;

    int lenWord = word.length();
    int lenFile = file.length();

    Table(word, lenWord, wordTable);

    int j = 0;
    while (moveCount <= (lenFile - lenWord)) {
        j = lenWord - 1; //Number of moves if none of the characters fit

        while (file[j + moveCount] == word[j] && j >= 0) j--; // If the characters match at all, reduce j.
        if (j < 0) { // if j < 0, same string
            fout << "\"" << str->name << "\" / " << str->num << endl;
            return;
        } else { // When don't have the same string,

            if (1 > j - wordTable[file[moveCount + j]]) { // a letter that is not in the word you are looking for
                moveCount += 1;
            } else {
                moveCount += (j - wordTable[file[moveCount + j]]);
            }
        }
    }
}

void Database_BST::AddTreeNode(Node *tail) { // Add node in BST
    Node* addNode = tail;
    Database_BST_Node* newNode = new Database_BST_Node(addNode->getName(), addNode->getNum(), addNode->getDriName());
    Database_BST_Node* currNode;
    Database_BST_Node* prevNode;
    if (root == nullptr) { // when add node is first 
        root = newNode;
    } else {
        currNode = root;
        while(currNode != nullptr) { // when add node is not first
            prevNode = currNode;
            if (newNode->num < currNode->num) {
                currNode = currNode->left;
            } else {
                currNode = currNode->right;
            }
        }
        if (newNode->num < prevNode->num) {
            prevNode->left = newNode;
        } else if (newNode->num > prevNode->num) {
            prevNode->right = newNode;
        }
    }
}
void Database_BST::Print(ofstream& fout) {
    Inorder(root, fout); // check
}
void Database_BST::MOVE(Node* moveNode, Loaded_LIST_Node* File, Loaded_LIST_Node* dirHead) { // move Loaded_LIST_Node to Database_BST

    Loaded_LIST_Node* moveFile = File;

    while(moveFile != dirHead) { // move node is not directory head
        Loaded_LIST_Node* prevDir = dirHead;
        while (prevDir->getFileNext() != moveFile) { // set Prev Directory
            prevDir = prevDir->getFileNext();
        }
        while (moveNode != moveFile->getHeadImage()) { // tail Image move BST
            AddTreeNode(moveNode);
//            cout << "Add processing..." << endl; // check
//            cout << "moveFile : " << moveFile->getDir() << " moveNode: " << moveNode->getName() << endl;
            moveNode = moveNode->getPrev(); // tail is prev tail node;
        }
        // if all image that exist one file move to BST, prev file's images move to BST
        AddTreeNode(moveNode);
        prevDir->setFileNext(nullptr);
        moveFile = prevDir;
    }
    if (moveFile == dirHead) { // move File is directory head
        moveNode = moveFile->getHeadImage();
        while (moveNode->getNext() != NULL) {
            moveNode = moveNode->getNext();
        }
        while(moveNode != moveFile->getHeadImage()) {
            AddTreeNode(moveNode);
//            cout << "Add processing..." << endl; // checking
//            cout << "moveFile : " << moveFile->getDir() << " moveNode: " << moveNode->getName() << endl; // check
            moveNode = moveNode->getPrev();
        }
        AddTreeNode(moveNode);
//        cout << "success???" << endl; // check
    }
}
