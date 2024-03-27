#include "network.h"
#include <set>
#include <queue>
#include <iostream>
#include <stack>


network::network(){
    users_ = std::vector<user>();
}
void network::add_user(const user &u){
    users_.push_back(u);
}
int network::add_connection(std::string s1, std::string s2){
    std::size_t i1 = get_id(s1);
    std::size_t i2 = get_id(s2);
    if(i1 == -1 || i2 == -1){
        return -1;
    }
    for(auto &i: users_[i1].get_friends()){
        if(i == i2){
            return -2;
        }
    }
    users_[i1].add_friend(i2);
    users_[i2].add_friend(i1);
    return 0;
}
int network::remove_connection(std::string s1, std::string s2){
    std::size_t i1 = get_id(s1);
    std::size_t i2 = get_id(s2);
    if(i1 == -1 || i2 == -1){
        return -1;
    }
    bool isfriend = false;
    for(auto &i: users_[i1].get_friends()){
        if(i == i2){
            isfriend = true;
        }
    }
    if(!isfriend){
        return -2;
    }
    users_[i1].delete_friend(i2);
    users_[i2].delete_friend(i1);
    return 0;
}
std::size_t network::get_id(std::string name){
    std::string temp;
    std::size_t id = 0;
    for(auto &i: users_){
        temp = i.get_name();
        if(name == temp){
            return id;
        }
        id += 1;
    }
    //if fail to find name
    return -1;
}
int network::read_friends(char* fname){
    std::cout<<"fname: "<<fname<<std::endl;
    std::ifstream myfile;
    myfile.open(fname);
    if (!myfile.is_open()){
        std::cout<<"file open failed"<<std::endl;
    }
    std::string line;
    std::string val, name, firstname, lastname;
    std::size_t id, i;
    std::vector<std::size_t> v;
    int year, zip;
    std::stringstream ss;
    int count;
    getline(myfile, line);
    std::cout<<"line: "<<line<<std::endl;
    while(getline(myfile, line)){
        count++;
        ss.clear();
        ss.str(line);
        ss >> id;
        getline(myfile, line);
        ss.clear();
        ss.str(line);
        ss >> firstname >> lastname;
        getline(myfile, line);
        ss.clear();
        ss.str(line);
        ss >> year;
        getline(myfile, line);
        ss.clear();
        ss.str(line);
        ss >> zip;
        getline(myfile, line);
        ss.clear();
        ss.str(line);
        while(ss >> i){
            v.push_back(i);
            //std::cout<<"friend of "<<id<<": "<<i<<std::endl;
        }
        users_.push_back(user(id, firstname +" "+ lastname , year, zip, v));
        v.clear();
    }
    myfile.close();
    //std::cout<<count;
    return count;
}
int network::write_friends(char* fname){
    int count = 0;
    std::ofstream myfile;
    myfile.open(fname);
    if (!myfile.is_open()){
        return -1;
    }
    for(auto &i: users_){
        myfile << i.get_id() << " " << i.get_name() << " " << i.get_year() << " " << i.get_zip();
        for(auto &j : i.get_friends()){
            myfile << j;
        }
        myfile << std::endl;
        count+=1;
    }
    myfile.close();
    return count;
}
std::size_t network::num_users(){
    return users_.size();
}
user& network::get_user(std::size_t id){
    return users_[id];
}

std::vector<int> network::shortest_path(int from, int to){
    clear_dp();
    std::set<int> visited;
    std::queue<int> q;
    std::vector<int> v;
    int d = 0;
    int p = 0;

    q.push(from);
    visited.insert(from);


    if(q.front() == to){
        v.push_back(from);
        return v;
    }

    while(!q.empty()){
        p = q.front();
        d = users_[q.front()].depth + 1;
        for(auto &i: users_[q.front()].get_friends()){
            if(visited.count(i)==0){
                visited.insert(i);
                q.push(i);
                users_[i].predecessor = p;
                users_[i].depth = d;
            }
        }
        q.pop();
    }

    if(users_[to].depth == 0){
        return v;
    }

    for(auto p = to; p!= from; p=users_[p].predecessor){
        v.push_back(p);
    }
    v.push_back(from);
    return v;

}
int network::suggest_friend(int id){
    for(auto u: users_){
        int i = u.get_id();
        bool b = true;
        for(auto f: users_[id].get_friends()){
            if(f == i){
                b = false;
            }
            if(f == id){
                b = false;
            }
        }
        if(b){
            return i;
        }
    }
    return -1;
}
std::vector<std::vector<int> > network::groups(){
    std::set<int> visited;
    std::queue<int> q;
    std::vector<std::vector<int> > v;
    int g = -1;

    for(int i = 0; i < users_.size(); i++){
        if(visited.count(i)==0){
            //std::cout<<"I: "<<i<<std::endl;
            g++;
            //std::cout<<"1 "<<std::endl;
            visited.insert(i);
            //std::cout<<"2 "<<std::endl;
            q.push(i);
            //std::cout<<"3 "<<std::endl;
            v.push_back(std::vector<int>());
            v[g].push_back(i);
            //std::cout<<"I: "<<i<<std::endl;
            while(!q.empty()){
                //std::cout<<"While q.front:: "<<q.front()<<std::endl;
                for(auto &j: users_[q.front()].get_friends()){
                    if(visited.count(j)==0){
                        //std::cout<<"J: "<<j<<std::endl;
                        visited.insert(j);
                        q.push(j);
                        v[g].push_back(j);
                    }
                }
                q.pop();
            }

        }


    }

    return v;
}
void network::clear_dp(){
    for(auto &i : users_){
        i.depth = 0;
        i.predecessor = 0;
    }
}

std::vector<int> network::suggest_friends(int who, int& score){
    score = 2;
    std::vector<int> vs;
    std::set<int> f;


    for(auto &i:users_[who].get_friends()){ //loop of int
        f.insert(i);
    }

    for(int i = 0; i < num_users(); i++){
        bool b = false;//is friend
        if(i == who){
            b = true;
        }
        for(auto &j: users_[i].get_friends()){
            if(j == who){
                b = true;
            }
        }
        if(!b){
            std::set<int> s;
            for(auto &j : users_[i].get_friends()){
                if(f.find(j)!=f.end() && s.find(j)==s.end()){
                    s.insert(j);
                    //std::cout<<i<<": "<<j<<std::endl;
                }
            }
            if(s.size()>score){
                score = s.size();
                vs.clear();
                vs.push_back(i);
            }else if(s.size() == score){
                vs.push_back(i);
            }
            s.clear();
        }

    }
    if(vs.empty()){
        score = -1;
    }
    return vs;
}

std::vector<int> network::distance_user(int from, int& to, int distance){
    clear_dp();
    int d = 0;
    int top;
    //std::cout<<"Test: from:"<<from<<std::endl;

    std::vector<bool> v;
    std::stack<int> s;
    s.push(from);

    for(auto &i: users_){
        v.push_back(false);
    }

    v[from] = true;
    std::vector<int> vr;




    //std::cout<<"start while loop"<<std::endl;
    while (!s.empty()){
        d=users_[s.top()].depth + 1;
        top=s.top();
        if(d == distance){
            for(auto &i: users_[top].get_friends()){
                if(!v[i]){
                    to = i;
                    //std::cout<<"Test: initializing loop"<<std::endl;
                    users_[i].predecessor = top;
                    //std::cout<<"Test: d:"<<d<<std::endl;

                    for(int j = i; j != from; j = users_[j].predecessor){
                        std::cout<<"Test: J:"<<j<<std::endl;

                        vr.push_back(j);
                    }
                    return vr;
                }
            }
            s.pop();
        }else{
            for(auto &i: users_[top].get_friends()){
                if(!v[i]){
                    v[i] = true;
                    users_[i].depth = d;
                    users_[i].predecessor = top;
                    s.push(i);
                }
            }
            s.pop();
        }
    }


    return vr;

}

std::vector<std::string> network::displayPosts(std::string name,int howmany){
    std::vector<std::string> v = users_[get_id(name)].displayPosts(0, howmany);
    return v;
    //std::cout<<"Test: network::displayPosts"<<std::endl;
}
void network::displayDM(std::string from,std::string to, int howmany){
    //std::cout<<users_[get_id(from)].displayDMs(get_id(to), 0, howmany);
}
void network::addPost(std::string who,std::string message,int likes,int id){
    users_[get_id(who)].add_post(new post(id, message, get_id(who), likes));
}

void network::addDM(std::string who,std::string message,int likes,int id,std::string recipient){
    users_[get_id(who)].add_post(new DirectMessage(id, message, get_id(who), likes, get_id(recipient)));
    users_[get_id(recipient)].add_post(new DirectMessage(id, message, get_id(who), likes, get_id(who)));
}

int network::read_message(char* fname){

    //std::cout<<"fname: "<<fname<<std::endl;
    std::ifstream myfile;
    myfile.open(fname);
    if (!myfile.is_open()){
        std::cout<<"file open failed"<<std::endl;
    }
    std::string line;
    std::string message, DM;
    std::size_t id, author, recipient, likes, i;
    std::stringstream ss;
    int count;
    getline(myfile, line);
    std::cout<<"line: "<<line<<std::endl;
    while(getline(myfile, line)){
        count++;
        ss.clear();
        ss.str(line);
        ss >> id;
        getline(myfile, message);
        getline(myfile, line);
        ss.clear();
        ss.str(line);
        ss >> author;
        getline(myfile, line);
        ss.clear();
        ss.str(line);
        ss >> likes;
        getline(myfile, line);
        ss.clear();
        ss.str(line);
        ss >> DM;
        if(DM == "DM"){
            getline(myfile, line);
            ss.clear();
            ss.str(line);
            ss >> recipient;
            addDM(users_[author].get_name(),message,likes,id,users_[recipient].get_name());
        }else{
            addPost(users_[author].get_name(),message, likes, id);
        }
        DM = "";
    }
    myfile.close();
    //std::cout<<count;
    return count;
}
