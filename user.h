#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "post.h"
#include "directMessage.h"

class user{
public:
    user();
    user(std::size_t id_,std::string name_,int year_,int zip_,std::vector<std::size_t> friends);
    void add_friend(int id);
    void delete_friend(int id);

    std::vector<std::size_t> get_friends();
    std::size_t get_id();
    std::string get_name();
    int get_year();
    int get_zip();

    int depth, predecessor;

    void add_post(post* p);
    void add_DM(post* p);
    std::vector<std::string> displayPosts(int startIndex, int endIndex);
    std::vector<std::string> displayDMs(int who_id,int startIndex,int endIndex);

    std::vector<post*> messages_;
private:
    int getNextPostId();
    int getNextDMId();

    std::size_t id;
    std::string name;
    int year;
    int zip;
    std::vector<std::size_t> friends_;


};
#endif
