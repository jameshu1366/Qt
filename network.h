#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class network{
public:
    network();

    void add_user(const user &u);
    int add_connection(std::string s1, std::string s2);
    int remove_connection(std::string s1, std::string s2);

    std::size_t get_id(std::string name);
    user& get_user(std::size_t id);
    std::size_t num_users();

    int read_message(char* fname);
    int read_friends(char* fname);
    int write_friends(char* fname);

    std::vector<int> shortest_path(int from, int to);
    std::vector<std::vector<int> > groups();
    void clear_dp();

    std::vector<int> suggest_friends(int who, int& score);
    int suggest_friend(int id);
    std::vector<int> distance_user(int from, int& to, int distance);

    std::vector<std::string> displayPosts(std::string name,int howmany);
    void displayDM(std::string from,std::string to, int howmany);
    void addPost(std::string who,std::string message,int likes,int id);
    void addDM(std::string who,std::string message,int likes,int id,std::string recipient);
private:
    std::vector<user> users_;
};
#endif
