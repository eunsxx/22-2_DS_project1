#include "Manager.h"
#include "rawreader.cpp"
#include <string>
#include <iostream>
using namespace std;

Manager::~Manager() // destructor
{
    if (fout.is_open())
        fout.close();

    if (ferr.is_open())
        ferr.close();
}

void Manager::Run(const char* filepath) {// command file
    fout.open(RESULT_LOG_PATH); // result log.txt
    ferr.open(ERROR_LOG_PATH); // error log.txt

    string command, str, dir, name;
    int num;

    fstream file;
    string path;
//    file.open(filepath, ios::in);
    file.open("command.txt");
    if (file.is_open()) {
        while (!file.eof()) {
            string line;
            getline(file, line);
            istringstream iss(line);
            string str_buf[10];
            int i = 0;
            while (getline(iss, str_buf[i], ' ')) i++;
            command = str_buf[0];
            if (command == "LOAD") {
                path = "image_files/filesnumbers.csv";
                if (Load(path) == 0) { // if path.is_open success
                    list.LOAD();
                    fout << "==========LOAD===========" << endl;
                    list.printNode(fout);
                    fout << "=========================" << endl << endl;
                } else { // fail
                    ferr << "==========ERROR==========" << endl;
                    ferr << Load(path) << endl;
                    ferr << "=========================" << endl << endl;
                }
            } else if (command == "ADD") {
                if (i < 2) PrintError(ParameterLack); // parameter is lack
                else {
                    dir = str_buf[1];
                    name = str_buf[2];
                    path = dir + '/' + name;
                    if (list.getDirHead() == nullptr) { // if any list not exist
                        PrintError(LoadedListNotExist);
                    } else if (Load(path) != Success) { // if path.is_open is failed
                        PrintError(AddFileNotExist);
                    } else { // success
                        if (list.findFileNode(dir) == nullptr) { // directory is not exist
                            list.ADD(dir, name, fout);
                        } else { // directory is already exist
                            NODE_COUNT -= list.deleteFileNode(list.findFileNode(dir));
                            list.ADD(dir, name, fout);
                        }
                    }
                }
            }else if (command == "MODIFY") {
                dir = str_buf[1];
                char separator = '"';
                istringstream iss(line);
                string buf[3];
                int j = 0;
                while(getline(iss, buf[j], separator)) j++;
                name = buf[1];
                num = stoi(buf[2]);
                if (list.searchNum(num) != Success) { // if already this number exist
                    PrintError(list.searchNum(num));
                }
                if (list.MODIFY(dir, name, num) == 1) { // Modify is failed
                    PrintError(ModifyError);
                } else {
                    fout << "=========MODIFY==========" << endl;
                    fout << "SUCCESS" << endl;
                    fout << "=========================" << endl << endl;
                }
            } else if (command == "MOVE") {
                if (list.getDirHead() == nullptr) { // if Linked_List not exist
                    PrintError(MoveError);
                } else {
                    Node *moveNode = list.getImageTail()->getPrev(); // last node is first move node
                    Loaded_LIST_Node *moveDir = list.getDirTail();
                    bst.MOVE(moveNode, moveDir, list.getDirHead());
                    moveDir = list.getDirHead();
                    while (moveDir != nullptr) { // If all nodes move and become empty,
                        list.deleteFileNode(moveDir); // delete this Directory List
                        moveDir = moveDir->getFileNext();
                    }
                    fout << "==========MOVE===========" << endl;
                    fout << "SUCCESS" << endl;
                    fout << "=========================" << endl << endl;
                }
            } else if (command == "PRINT") {
                if (bst.BSTisEmpty() == Success) {
                    fout << "==========PRINT===========" << endl;
                    bst.Print(fout);
                    fout << "=========================" << endl << endl;
                }
                else PrintError(bst.BSTisEmpty()); // When there is no BST to print out
            } else if (command == "SEARCH") {
                char separator = '"';
                istringstream iss(line);
                string buf[3], word;
                int j = 0;
                while(getline(iss, buf[j], separator)) j++;
                word = buf[1];
                if (j<1 || bst.BSTisEmpty() != Success) PrintError(SearchError); // when there is no BST or parameter is lack
                else {
                    fout << "==========SEARCH===========" << endl;
                    bst.Iter_Postorder(s, out, word, fout); // Iterative post-order traversal
                    fout << "=========================" << endl << endl;
                }
            } else if (command == "SELECT") {
                num = stoi(str_buf[1]);
                name = bst.SearchImage(num); // search number
                path = name + ".RAW";
                if (path == "0") {
                    PrintError(SelectError); // not find this number
                } else { // find this number
                    fout << "=========SELECT==========" << endl;
                    fout << "SUCCESS" << endl;
                    fout << "=========================" << endl << endl;
                }
            } else if (command == "EDIT") {
                string option = str_buf[1];
                Result result;
                if (option == "-f") {
                    if (i != 2) PrintError(EditError); // parameter is lacking or numerous
                    result = flipped(name);
                } else if (option == "-l") { // parameter is lacking or numerous
                    if (i != 3) PrintError(EditError);
                    int light = stoi(str_buf[2]);
                    result = adjusted(name, light);
                } else if (option == "-r") { // parameter is lacking or numerous
                    if (i != 2) PrintError(EditError);
                    result = resized(name);
                }
                if (result == Success) {
                    fout << "=========EDIT=========" << endl;
                    fout << "success" << endl;
                    fout << "======================" << endl;
                }
            } else if(command == "EXIT") {
                fout << "=========EXIT=========" << endl;
                fout << "success" << endl;
                fout << "======================" << endl;
            } else {
                ferr << WrongCommandImput << endl;
            }
        }
        if (!file.is_open()) ferr << "Error code: " << CommandFileNotExist << endl;
        // TODO: implement
    }
}

void Manager::PrintError(Result result) {
    ferr << "==========ERROR==========" << endl;
    ferr << result << std::endl;
    ferr << "=========================" << endl;
}

Result Manager::Load(string filepath) {

    fstream file;

    file.open(filepath);

    if (file.is_open()) {
        return Success;
    } else {
        return LoadFileNotExist;
    }
}