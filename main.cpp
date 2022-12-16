#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdlib.h>
#include "Manager.cpp"
using namespace std;

int main(int argc, char* argv[]) {
    const char* commandFilepath = "command.txt";
    if (argc > 1)
        commandFilepath = argv[1];

    Manager m;
    m.Run(commandFilepath); // read command file

    return 0;
}