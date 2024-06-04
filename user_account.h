#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

class user{
    private:
        string naam;
        vector<user*> followers;
        vector<user*> following;

    public:
        user();
        user(string name);
        void setnaam(string name);
        string getnaam();
        void add_follower(user* flwr);
        vector<user*> get_followers();
        void add_following(user* flwng);
        vector<user*> get_following();
};

