#include "user.h"
#include <iostream>
#include <map>

user::user(){
    id = 0;
    name = "";
    year = 0;
    zip = 0;
    friends_ = std::vector<std::size_t>();
    messages_ = std::vector<post*>();
}
user::user(std::size_t id_,std::string name_, int year_, int zip_, std::vector<std::size_t> friends){
    id = id_;
    name = name_;
    year = year_;
    zip = zip_;
    friends_ = friends;
    messages_ = std::vector<post*>();
}
void user::add_friend(int id){
    for(auto &i: friends_){
        if(i == id){
            return;
        }
    }
    friends_.push_back(id);
}
void user::delete_friend(int id){
    for(int i = 0; i < friends_.size(); i++){
        if(friends_[i] == id){
            friends_.erase(friends_.begin()+i);
            return;
        }
    }
}
std::vector<std::size_t> user::get_friends(){
    return friends_;
}
std::size_t user::get_id(){
    return id;
}
std::string user::get_name(){
    return name;
}
int user::get_year(){
    return year;
}
int user::get_zip(){
    return zip;
}
void user::add_post(post* p){
    //std::cout<<"messages_.size() "<<messages_.size()<<std::endl;
    p->set_id(getNextPostId());
    messages_.push_back(p);
    //std::cout<<"id: "<<id<<std::endl;
    //std::cout<<"messages_.size() "<<messages_.size()<<std::endl;
}
void user::add_DM(post* p){
    p->set_id(getNextDMId());
    messages_.push_back(p);
}
std::vector<std::string> user::displayPosts(int startIndex, int endIndex){
    std::vector<std::string> s;
    for(auto *i:messages_){
        if(i->identify() == "post"){
            if(i->get_id() >= startIndex && i->get_id() <= endIndex){
                s.push_back(i->get_message());
            }
        }
   }
    while(s.size() < (endIndex - startIndex + 1)){
        s.push_back("no more posts");
    }
    return s;

}
std::vector<std::string> user::displayDMs(int who_id,int startIndex, int endIndex){
    std::vector<std::string> s;
    int index  = 0;
    for(auto i:messages_){
        if(i->identify() == "DM"){
            if((i->get_author())[0] == who_id || (i->get_author())[1] == who_id){
                if(index >= startIndex && index <= endIndex){
                    s.push_back(i->get_message() + "    BY: "+ std::to_string(i->get_author()[0]));
                }
                index++;
            }
        }
   }
    while(s.size() < (endIndex - startIndex + 1)){
        s.push_back("no more messages");
    }
    return s;
}

int user::getNextPostId(){
    int i = 0;
    for(auto *p : messages_){
        if(p->identify() == "post"){
            i++;
        }
    }
    return i;
}
int user::getNextDMId(){
    int i = 0;
    for(auto *p : messages_){
        if(p->identify() == "DM"){
            i++;
        }
    }
    return i;
}
