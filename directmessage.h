#ifndef DIRECTMESSAGE_H
#define DIRECTMESSAGE_H
#include "post.h"
#include<string>

class DirectMessage:public post{
public:
    DirectMessage();
    DirectMessage(int id, std::string message, int author, int likes, int recipient);

    //std::string displayPost() override;

    int get_recipient();
    std::vector<int> get_author() override;

    std::string identify() override;

private:
    int recipient_;
};

#endif
