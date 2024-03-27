#ifndef POST_H
#define POST_H

#include <string>
#include <vector>

class post{
private:
    int id_;
    std::string message_;
    int author_;
    int likes_;

public:
    post();
    post(int id, std::string message, int author, int likes);

    std::string displayPost();
    void set_id(int id);
    int get_id();
    virtual std::vector<int> get_author();
    int get_likes();
    std::string get_message();

    virtual std::string identify();
};

#endif
