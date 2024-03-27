#include "post.h"
#include <iostream>

post::post(){
    id_ = 0;
    message_ = "";
    author_ = 0;
    likes_ = 0;
}
post::post(int id, std::string message, int author, int likes){
    id_ = id;
    message_ = message;
    author_ = author;
    likes_ = likes;
}

std::string post::displayPost(){
    //std::string s;
    //s=get_message()+"\nliked by "+std::to_string(get_likes())+" people";
    //return s;
    return message_;
}
void post::set_id(int id){
    id_ = id;
}

std::string post::identify(){return "post";}
int post::get_id(){return id_;}
std::vector<int> post::get_author(){
    std::vector<int> v;
    v.push_back(author_);
    return v;
}
int post::get_likes(){return likes_;}
std::string post::get_message(){return message_;}
