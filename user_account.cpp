#include "user_account.h"
using namespace std;

user::user(){
    naam = "";
}
user::user(string name){
    naam = name;
}

void user::setnaam(string name){
    naam = name;
}

string user::getnaam(){
    return naam;
}

void user::add_follower(user* flwr){
    followers.push_back(flwr);
}

vector<user*> user::get_followers(){
    return followers;
}

void user::add_following(user* flwng){
    following.push_back(flwng);
}

vector<user*> user::get_following(){
    return following;
}




