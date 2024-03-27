#include "directMessage.h"


DirectMessage::DirectMessage(){recipient_ = 0;}
DirectMessage::DirectMessage(int id, std::string message, int author, int likes, int recipient):post(id, message, author, likes){
    recipient_ = recipient;
}

/*
std::string DirectMessage::displayPost() override {
    //std::string s = post::displayPost() + "$" + std::to_string(recipient_) + "$";
    //return s;
}
*/
int DirectMessage::get_recipient(){return recipient_;}

std::string DirectMessage::identify()  {return "DM";}

std::vector<int> DirectMessage::get_author() {
    std::vector<int> v = post::get_author();
    v.push_back(recipient_);
    return v;
}
