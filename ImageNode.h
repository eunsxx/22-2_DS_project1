#ifndef IMAGENODE_H
#define IMAGENODE_H

#include <iostream>
#include "Result.h"
using namespace std;
int NODE_COUNT = 0;

int FindDelim(string str, char delim) {
    int i = 0;
    while (str[i] != delim) i++;
    return i;
}

class Node { // imageNode
private:
    string name;
    int number;
    string dirName;
    Node* next = nullptr;
    Node* prev = nullptr;

public:
    Node() {};
    ~Node(){};
    Node(string name, int num, string dirName) {
        this->name = name;
        this->number = num;
        this->dirName = dirName;
    }

    string getName() {return name;}
    int getNum() {return number;}
    string getDriName() {return dirName; }
    Node* getNext() {return next;}
    Node* getPrev() {return prev;}

    void setName(string name) {this->name = name;}
    void setNum(int num) {this->number = num;}
    void setDirName(string dirName) {this->dirName = dirName; }
    void setNext(Node* next) {this->next = next;}
    void setPrev(Node* prev) {this->prev = prev;}
};

class Loaded_LIST_Node { // fileNode
private:
	string dir;
    Loaded_LIST_Node* fileNext = nullptr;
    Node* headImage = nullptr;
public:
    Loaded_LIST_Node(string name, string directory, int num) {
        dir = directory;
        Node* newNode = new Node(name, num, directory);
        headImage = newNode;
    }
    ~Loaded_LIST_Node(){};

    string getDir() {return dir;}
    Loaded_LIST_Node* getFileNext() {return fileNext;} // get next File node
    Node* getHeadImage() {return headImage;}

    void setDir(string dir) {this->dir = dir;}
    void setFileNext(Loaded_LIST_Node* next) {this->fileNext = next;}
    void setHeadImage(Node* node) {this->headImage = node;}

    void printImage(ofstream& fout); // ImageNode print
    Result findNum(int num); // find unique number if it exists or not
};

void Loaded_LIST_Node::printImage(ofstream& fout) { // print Image node
    Node* currNode = headImage;
    while (currNode != nullptr) {
        fout << currNode->getName() << '/' << currNode->getNum() << endl;
        currNode = currNode->getNext();
    }
}

Result Loaded_LIST_Node::findNum(int num) { // find num
    Node* currNode = headImage;
    while (currNode != nullptr) {
        if (currNode->getNum() == num) {
            return UniqueNumExist;
        }
        currNode = currNode->getNext();
    }
    return Success;
}

class Loaded_LIST{ // all File and Image Node list
private:
    Loaded_LIST_Node* dirHead; // first file node
    Loaded_LIST_Node* dirTail; // last file node
    Node* imageTail;

public:
    Loaded_LIST() {
        dirHead = dirTail = nullptr;
        imageTail = nullptr;
    }
    ~Loaded_LIST(){};
    Loaded_LIST_Node* getDirHead() { return dirHead; }
    Loaded_LIST_Node* getDirTail() {return dirTail; }
    Node* getImageTail() { return imageTail; }

    void deleteFirstNode() { // when NODECOUNT is more 300, we need to delete first node
        if (dirHead->getHeadImage() != nullptr) { // general case
            Node* delImage = dirHead->getHeadImage();
            dirHead->setHeadImage(delImage->getNext());
            delete delImage;
            if (dirHead->getHeadImage() == nullptr) {// when don't exist any image in directory
                Loaded_LIST_Node *delFile = dirHead;
                if (delFile->getFileNext() != nullptr) { // when exist next imageFileNode
                    dirHead = delFile->getFileNext();
                    delete delFile;
                } else { // when don't exist any file in List
                    dirHead = nullptr;
                }
            }
        }
    }

    int deleteFileNode(Loaded_LIST_Node* del) {
        Loaded_LIST_Node* delFile = del;
        Loaded_LIST_Node* curr = dirHead;
        int delNodeCount = 0;
        if (delFile != dirHead) { // If delete File List is not dirHead
            while(curr->getFileNext() != delFile) curr = curr->getFileNext();
//            cout << "curr getDir = " << curr->getDir() << endl; // check
            if (delFile->getFileNext() != nullptr) { // and if deleteFileList is not tail
                curr->setFileNext(delFile->getFileNext());
                Node* delNode = delFile->getHeadImage();
                while (delNode != nullptr) {
                    Node* prevNode = delNode;
                    delNode = delNode->getNext();
                    delete prevNode;
                    delNodeCount++;
                }
//                cout << "delNodeCount: " << delNodeCount << endl; // check
                delete delFile;
            } else { // if delete File is tail
                curr->setFileNext(nullptr);
                Node* delNode = delFile->getHeadImage();
                while (delNode != nullptr) {
                    Node* prevNode = delNode;
                    delNode = delNode->getNext();
                    delete prevNode;
                    delNodeCount++;
                }
//                cout << "delNodeCount: " << delNodeCount << endl; // check
                delete delFile;
            }
        } else { // if deleteFile is head
            // curr is dirHead
            if (delFile->getFileNext() != nullptr) { // and if deleteFile next File exist
                dirHead = delFile->getFileNext();
                Node* delNode = delFile->getHeadImage();
                while (delNode != nullptr) {
                    Node* prevNode = delNode;
                    delNode = delNode->getNext();
                    delete prevNode;
                    delNodeCount++;
                }
                cout << "delNodeCount: " << delNodeCount << endl;
                delete delFile;
            } else if (delFile->getFileNext() == nullptr) {// When delFile is dirHead, and delFile next File not eixst
                dirHead = nullptr;
                Node* delNode = delFile->getHeadImage();
                while (delNode != nullptr) {
                    Node* prevNode = delNode;
                    delNode = delNode->getNext();
                    delete prevNode;
                    delNodeCount++;
                }
                delete delFile;
            }
        }
        return delNodeCount;
    }
    void addNode(string name, string directory, int num) {
        if (dirHead == nullptr) { // if any file node not exist
            dirHead = new Loaded_LIST_Node(name, directory, num);
            dirTail = dirHead;
            imageTail = dirHead->getHeadImage();
        } else { // if file node exist
            Loaded_LIST_Node* currFile = dirHead;
            while (currFile != nullptr) {
                if (currFile->getDir() == directory) { // compare fileNode to directory name
                    Node * currImage = currFile->getHeadImage();
                    while (currImage->getNext() != nullptr) currImage = currImage->getNext();
                    Node * newNode = new Node(name, num, directory);
                    currImage->setNext(newNode);
                    newNode->setPrev(currImage);
                    imageTail = newNode;
                    return;
                }
                currFile = currFile->getFileNext();
            }
            Loaded_LIST_Node* newFileNode = new Loaded_LIST_Node(name, directory, num);
            dirTail->setFileNext(newFileNode);
            dirTail = newFileNode;
            imageTail = dirTail->getHeadImage();
            return;
        }
    }

    Loaded_LIST_Node* findFileNode(string dir){ // find File node
        Loaded_LIST_Node* curr = dirHead;
        while (curr != nullptr) {
            if (curr->getDir() != dir) curr = curr->getFileNext();
            else if (curr->getDir() == dir) return curr;
        }
        return nullptr;
    }

    Node* findNode(string dir, string name) { // find Node
        Loaded_LIST_Node* currFile = findFileNode(dir);
        if (currFile != nullptr) {
            Node *currImage = currFile->getHeadImage();
            while (currImage != nullptr) {
                if (currImage->getName() != name) currImage = currImage->getNext();
                else if (currImage->getName() == name) return currImage;
            }
            return nullptr;
        } else return nullptr;
    }

    int modifyNode(string dir, string name, int changeNum) { // modify node
        Node* delNode = findNode(dir, name);
        Loaded_LIST_Node* currFile = findFileNode(dir);
        if (delNode != nullptr && currFile != nullptr) {
            Node *newNode = new Node(name, changeNum, dir);

            if (currFile->getHeadImage() == delNode) { // if delNode is first image node
                currFile->setHeadImage(newNode);
                newNode->setNext(delNode->getNext());
                delNode->getNext()->setPrev(newNode);
            } else if (delNode->getNext() != nullptr) { // general situation
                newNode->setPrev(delNode->getPrev());
                delNode->getPrev()->setNext(newNode);
                newNode->setNext(delNode->getNext());
                delNode->getNext()->setPrev(newNode);
            } else { // if delNode is last image node
                newNode->setPrev(delNode->getPrev());
                delNode->getPrev()->setNext(newNode);
                newNode->setNext(nullptr);
            }

            delete delNode;
            return 0; // SUCCESS
        } else {
            return 1; // FAIL
        }
    }

    void printNode(ofstream& fout) { // print node Image in this directory list
        Loaded_LIST_Node* currFile = dirHead;
        while (currFile != nullptr) {
            currFile->printImage(fout);
            currFile = currFile->getFileNext();
        }
    }

    Result searchNum(int num);
    void LOAD();
    void ADD(string directory, string fileName, ofstream& fout);
    void PrintList(ofstream& fout);
    int MODIFY(string directory, string imageName, int changeNum);
};

void Loaded_LIST::LOAD() {
    fstream file;
    string line, name, num;
    int number = 0;

    file.open("image_files/filesnumbers.csv");

    if (file.is_open()) {
        while(!file.eof()) {
            getline(file, line);
            if(line.length() != 0) {
                num = line.substr(0, 3);
                number = stoi(num);
                name = line.substr(4, FindDelim(line, '.') - 4);
                if(NODE_COUNT < 100) {
                    addNode(name, "img_files", number);
                    NODE_COUNT++;
                } else {
                    deleteFirstNode();
                    NODE_COUNT--;
                }
            }
        }
    } else {
        cout << "==========ERROR=========" << endl;
        cout << 100 << endl;
        cout << "========================" << endl;
    }

    file.close();
}

void Loaded_LIST:: ADD(string directory, string fileName, ofstream& fout) {
    fstream file;
    string line, num, name;
    int number;
    string path = directory + "/" + fileName;

    file.open(path);
    if (file.is_open()) {
        while(!file.eof()) {
            getline(file, line);
            if (line.length() != 0) {
                num = line.substr(0, 3);
                number =stoi(num);
                name = line.substr(4, FindDelim(line, '.') -4);
//                cout << "count: " << *count << endl; // check
                if(NODE_COUNT < 100) {
                    addNode(name, directory, number);
                    NODE_COUNT++;
                } else {
                    deleteFirstNode();
                    NODE_COUNT--;
//                    cout << "- after count: " << *count << endl; // check
                }
            }
        }

        fout << "==========ADD===========" << endl;
        fout << "SUCCESS" << endl;
        fout << "========================" << endl << endl;
    }
    file.close();
}

void Loaded_LIST::PrintList(ofstream& fout) { printNode(fout); }

Result Loaded_LIST:: searchNum(int num) {
    Result result = Success;
    Loaded_LIST_Node* currFile = dirHead;
    while (currFile != nullptr) {
        result = currFile->findNum(num);
        currFile = currFile->getFileNext();
    }
    return result;
}

int Loaded_LIST::MODIFY(string directory, string imageName, int changeNum) {

    int status = modifyNode(directory, imageName, changeNum);
    return status;
}

#endif