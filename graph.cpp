#include "graph.h"
#include <vector>

using namespace std;

//default constructor
Graph::Graph(){

}

Graph::~Graph(){
    //delete allusers
    for(int i=0;i<allusers.size();i++){
        delete allusers[i];
    }
}

bool Graph::readinpfile(string fname){
    string username1,username2;

    user* user1,*user2;
    //cout << "line 22" << endl;

    ifstream ifile;
    ifile.open(fname.c_str());
    //c_str() converts to a C-style string (const string*) which is needed for open()
    if(!ifile.is_open()){
        cerr << "error: unable to read from file " << fname << ". Aborting. " << endl;
        return false;
    }
    while(ifile >> username1 >> username2){// while not end of file
        
        //cout << "line 34" << endl;
        if((username1.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") == string::npos) && (username2.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") == string::npos) && username1.length()<= 15 && username2.length() <= 15){
            // find_first_not_of() is used to search for the first character in a string that does not match any of the characters specified in another string
            // string::npos : to denote failure when a valid position or index for a substring is not found in the string
            //find(), rfind(), find_first_of(), find_last_of(), substr(), and erase() in these npos is used to denote failure
            if(!ifile.fail()){
                //check if already present
                user1 = search(username1);
                user2 = search(username2);

                if(!user1){
                    user1 = new user(username1);
                    allusers.push_back(user1);
                }
                if(!user2){
                    user2 = new user(username2);
                    allusers.push_back(user2);
                }
                // user2 is following user1
                // so add user2 in followers of useer1 
                //and add user1 in following of user2
                // "Following” is the term for the users who you follow. "Followers" are the users who follow you.
                user2->add_following(user1);
                user1->add_follower(user2);
            }
        }
    }
    //check if the file is empty
    if(allusers.size() == 0){
        cerr << "error: unable to read from file " << fname << ". Aborting. " << endl;
        return false;
    }
    //close the file
    ifile.close();
    return true;
}


user* Graph::search(string n){
    for(int i=0;i< allusers.size();i++){
        if(n == allusers[i]->getnaam()){
            return allusers[i];
        }
    }
    return NULL;
}

bool Graph::writeoutfile(string fname){
    ofstream ofile;
    ofile.open(fname.c_str());
    //cout << "line 84" << endl;

    if(!ofile.is_open()){
        cerr << "error: unable to write to file " << fname << endl;
        return false;
    }

    //temp variables
    string n1 = "";
    string n2 = "";
    string n3 = "";
    string n4 = "";

    //stores maximum centrality
    int max = 0;

    //stores the position where the centrality is maximum
    int pos = 0;
    //cout << "line 102" << endl;
    //finding max centrality in the directed graph. It breaks tie by alphabetical order
    for(int i=0;i<allusers.size();i++){
        //code to break a tie
        //cout << "line 106" << endl;
        if(allusers[i]->get_followers().size() == max){
            n1 = allusers[i]->getnaam();
            n2 = allusers[pos]->getnaam();
            //convert names to lower alphabets
            for(int j=0;j<n1.length();j++){
                n1[j] = tolower(n1[j]);
            }
            for(int j=0;j<n2.length();j++){
                n2[j] = tolower(n2[j]);
            }
            if(n1.compare(n2) < 0){
                pos = i;
            }
        }
        else{
            //code to find max centrality
            if(allusers[i]->get_followers().size() > max){
                pos = i;
                max = allusers[i]->get_followers().size();
            }
        }
    }

    // sugg(short of suggestions) vector stores the vector of unique users for the root user to follow.
    vector<user*> sugg;
    //cout << "line 132" << endl;
    sugg = bfs(allusers[pos]);
    //cout << "line 134" << endl;
    //sort the vector in the descending order of centrality
    // used bubble sort
    for(int i=0;i< sugg.size() - 1;i++){
        for(int j=0;j< sugg.size()-i-1;j++){
            if(sugg[j]->get_followers().size() < sugg[j+1]->get_followers().size()){
                user* tmp = sugg[j];
                sugg[j] = sugg[j+1];
                sugg[j+1] = tmp;
            }
            //if tie - see alphabetically
            if(sugg[j]->get_followers().size() == sugg[j+1]->get_followers().size()){
                n3 = sugg[j]->getnaam();
                for(int k=0;k<n3.length();k++){
                    n3[k] = tolower(n3[k]);
                }
                n4 = sugg[j+1]->getnaam();
                for(int k=0;k<n4.length();k++){
                    n4[k] = tolower(n4[k]);
                }
                if(n3.compare(n4) > 0){ // n3 is lexicographically greater than n4
                    user* tmp = sugg[j];
                    sugg[j] = sugg[j+1];
                    sugg[j+1] = tmp;
                }
            }
        }
    }

    // now printing to a output file.
    ofile << "Looking for new accounts for ** "  << allusers[pos]->getnaam() <<  " ** to follow" << endl;
    for(int i=0;i< sugg.size();i++){
        ofile << sugg[i]->getnaam() << " (" <<  sugg[i]->get_followers().size() << ") " << endl;
    }

    ofile.close();
    return true;

}

vector<user*> Graph::bfs(user* root){
    vector<user*> v1; // frontier queue
    vector<user*> v2; // discovered set
    bool vis = false;
    //cout << "line 178" << endl;
    user* curr;
    v1.push_back(root);
    v2.push_back(root);
    //cout << "line 182" << endl;
    while(v1.size() != 0){
        curr = v1[0];
        v1.erase(v1.begin());
        //cout << "line 186" << endl;
        //users followed by the ppl whom the root user is following and not in the discovered set;
        for(int i =0; i< curr->get_following().size();i++){
            for(int l =0; l< curr->get_following().at(i)->get_following().size();l++){
                for(int j = 0; j< v2.size();j++){
                    if(v2[j]->getnaam() == curr->get_following().at(i)->get_following().at(l)->getnaam()){
                        vis = true;
                    }
                }
                if(!vis){
                    v2.push_back(curr->get_following().at(i)->get_following().at(l));
                }
                else{
                    vis = false;
                }
            }
        }
        //cout << "line 203" << endl;
    }

    v2.erase(v2.begin());
    //check if any user isa already followed by the user and remove it
    for(int i =0;i< root->get_following().size();i++){
        for(int j =0;j< v2.size();j++){
            if(root->get_following().at(i)->getnaam() == v2[j]->getnaam()){
                v2.erase(v2.begin()+j);
            }
        }
    }
    return v2;
}




