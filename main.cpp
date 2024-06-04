#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
//#include "user_account.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[]){
    string inFile = argv[1];
    string outFile = argv[2];

    Graph G;
    G.readinpfile(inFile);
    G.writeoutfile(outFile);

}