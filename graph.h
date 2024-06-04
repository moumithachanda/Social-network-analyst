#include "user_account.h"
using namespace std;

// the graph class reads the data from the input file and creates a directed graph 
// finds the root user and suggestions for the user to follow

class Graph{
    private:
        vector<user*> allusers;
    public:

    Graph(); 

    ~Graph(); // to delete allusers vector

    bool readinpfile(string fname);

    bool writeoutfile(string fname);

    user* search(string name);

    vector<user*> bfs(user* source);
    // implementing bfs algorithm for searching whom to follow within a depth of 2 for a given source.

};
