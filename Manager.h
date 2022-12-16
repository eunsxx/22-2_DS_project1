//
// Created by 이은서 on 2022/10/04.
//

#ifndef PROJECT1_MANEGER_H
#define PROJECT1_MANEGER_H

//#include "Result.h"
#include "Database_BST.cpp"
#include <fstream>
#include <iostream>
using namespace std;


class Manager {
private:
    // the filepath for the result log
    const char* RESULT_LOG_PATH = "log.txt"; // save result log
    const char* ERROR_LOG_PATH = "error.txt"; // save error log
    std::ofstream fout;
    std::ofstream ferr;
    Loaded_LIST list;
    Database_BST bst;
    Stack s, out;

public:
    ~Manager();
    void Run(const char* filepath); // run file
    void PrintError(Result result);

private:
    Result Load(string filepath);
};

#endif //PROJECT1_MANEGER_H
