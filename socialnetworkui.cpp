
#include "socialnetworkui.h"
#include "ui_socialnetworkui.h"
using namespace std;

SocialNetworkUI::SocialNetworkUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkUI)
{
    ui->setupUi(this);
    n = network();
    const char* c;

    ui->PromptF->setVisible(false);
    ui->tableWidget->setVisible(false);
    ui->BackButton->setVisible(false);
    ui->UserDisplay->setVisible(false);
    ui->ShortestPathDisplay->setVisible(false);
    ui->ShortestPathUser->setVisible(false);
    ui->ShortestPathButton->setVisible(false);
    ui->SuggestFriendDisplay->setVisible(false);
    ui->SuggestButton->setVisible(false);
    ui->AddButton->setVisible(false);
    ui->AddFriendButton->setVisible(false);
    ui->ChatNumber->setVisible(false);
    ui->ChatLine->setVisible(false);
    ui->ChatButton->setVisible(false);
    ui->ShowButton->setVisible(false);
    ui->ShowMoreButton->setVisible(false);
    ui->ChatTable->setVisible(false);
    ui->SendButton->setVisible(false);
    ui->Text->setVisible(false);

    ui->PromptF->setReadOnly(true);
    ui->ShortestPathDisplay->setReadOnly(true);
    ui->SuggestFriendDisplay->setReadOnly(true);

    /*
    c = "HW5/file.txt";
    n.read_friends(const_cast<char*>(c));
    std::cout<<n.num_users()<<std::endl;

    c = "post.txt";
    n.read_message(const_cast<char*>(c));
    std::cout<<n.num_users()<<std::endl;
*/
    //std::size_t id_,std::string name_,int year_,int zip_,std::vector<std::size_t> friends
    vector<size_t> v1{1,2,3,4,5};
    vector<size_t> v2{0,5};
    vector<size_t> v3{0,5};
    vector<size_t> v4{0,5};
    vector<size_t> v5{0,5};
    vector<size_t> v6{0,1,2,3,4};
    user u0 = user(0,"user0", 2000, 95053, v1);
    user u1 = user(1,"first last", 2000, 95053, v2);
    user u2 = user(2,"f2 l2", 2000, 95053, v3);
    user u3 = user(3,"f3 l3", 2000, 95053, v4);
    user u4 = user(4,"f4 l4", 2000, 95053, v5);
    user u5 = user(5,"f5 l5", 2000, 95053, v6);
    u0.add_post(new post(0,"post 1",0,0));
    u0.add_post(new post(1,"post 2",0,0));
    u0.add_post(new post(2,"post 3",0,0));
    u0.add_post(new post(3,"post 4",0,0));
    u0.add_post(new post(4,"post 5",0,0));
    u1.add_post(new post(0,"post 6",1,0));
    u2.add_post(new post(0,"post 7",2,0));
    u3.add_post(new post(0,"post 8",3,0));
    u4.add_post(new post(0,"post 9",4,0));
    u5.add_post(new post(0,"post 10",5,0));
    u5.add_post(new post(1,"post 11",5,0));
    u1.add_DM(new DirectMessage(0,"Hello",1,0,0));
    u1.add_DM(new DirectMessage(0,"Hello",0,0,1));
    u1.add_DM(new DirectMessage(0,"I'm First Last.",1,0,0));
    u1.add_DM(new DirectMessage(0,"I'm User0",0,0,1));
    u0.add_DM(new DirectMessage(0,"Hello",1,0,0));
    u0.add_DM(new DirectMessage(0,"Hello",0,0,1));
    u0.add_DM(new DirectMessage(0,"I'm First Last.",1,0,0));
    u0.add_DM(new DirectMessage(0,"I'm User0",0,0,1));
    n.add_user(u0);
    n.add_user(u1);
    n.add_user(u2);
    n.add_user(u3);
    n.add_user(u4);
    n.add_user(u5);
    std::cout<<"n.num_users(): "<<n.num_users()<<std::endl;
    //post(int id, std::string message, int author, int likes);



    connect(ui->UsernameButton, &QPushButton::clicked, this, [this]() {
        int id = login();
        cout<<"id: "<<id<<endl;
        int chat = 0;
        connect(ui->tableWidget, &QTableWidget::cellClicked, this,&SocialNetworkUI::friendClicked);
        connect(ui->BackButton, &QPushButton::clicked, this, [=]() {
            backClicked(id);
        });
        connect(ui->ShortestPathButton, &QPushButton::clicked, this, [=]() {
            shortestPath(id);
        });
        connect(ui->SuggestButton, &QPushButton::clicked, this, [=]() {
            suggestFriend(id);
        });
        connect(ui->AddButton, &QPushButton::clicked, this, [=]() {
            addFriendSuggestion(id);
        });
        connect(ui->AddFriendButton, &QPushButton::clicked, this, [=]() {
            addFriendTable(id);
        });
        connect(ui->ChatButton, &QPushButton::clicked, this, [=]() {
            showChat(id);
            static int chat = 0;
            chat = 0;
            connect(ui->ShowMoreButton, &QPushButton::clicked, this, [=]() {
                showMore(id, chat);
                cout<<"chat: "<<chat<<endl;
                chat++;
            });
        });
        connect(ui->ShowButton, &QPushButton::clicked, this, [=]() {
            showChat(id);
            static int chat = 0;
            chat = 0;
            connect(ui->ShowMoreButton, &QPushButton::clicked, this, [=]() {
                showMore(id, chat);
                cout<<"chat: "<<chat<<endl;
                chat++;
            });
        });
        connect(ui->SendButton, &QPushButton::clicked, this, [=]() {
            addChat(id);
        });
    });




}

SocialNetworkUI::~SocialNetworkUI()
{
    delete ui;
}

int SocialNetworkUI::login() {
    QString qstr = ui->UsernameEdit->text();
    string str = qstr.toStdString();

    int i = n.get_id(str);
    if(i == -1){
        ui->PromptF->setVisible(true);
    }else{
        //cout<<"i: "<<i<<endl;
        ui->UserDisplay->setText(QString::fromStdString(n.get_user(i).get_name()));
        ui->UserDisplay->setVisible(true);

        ui->UsernameButton->setVisible(false);
        ui->UsernameEdit->setVisible(false);
        ui->PromptF->setVisible(false);

        ui->tableWidget->setColumnCount(2);
        ui->tableWidget->setRowCount(5);

        vector<string> s = n.get_user(i).displayPosts(0,4);
        vector<size_t> v = n.get_user(i).get_friends();

        for(std::size_t i=0; i<s.size()&&i<5; ++i){
            cout<<"s.size(): "<<s.size()<<std::endl;
            string s2= s[i];
            QString qs = QString::fromStdString(s2);

            QTableWidgetItem* qtwi = new QTableWidgetItem(qs);
            ui->tableWidget->setItem(i, 0, qtwi);
        }
        for(std::size_t i=0; i<v.size()&&i<5; ++i){
            string s1= n.get_user(v[i]).get_name();
            QString qs = QString::fromStdString(s1);
            QTableWidgetItem* qtwi = new QTableWidgetItem(qs);
            ui->tableWidget->setItem(i, 1, qtwi);
        }
        ui->tableWidget->setVisible(true);


    ui->tableWidget->setVisible(true);
    ui->BackButton->setVisible(true);
    ui->UserDisplay->setVisible(true);
    ui->ShortestPathDisplay->setVisible(true);
    ui->ShortestPathUser->setVisible(true);
    ui->ShortestPathButton->setVisible(true);
    ui->SuggestFriendDisplay->setVisible(true);
    ui->SuggestButton->setVisible(true);
    ui->AddButton->setVisible(true);
    ui->AddFriendButton->setVisible(true);
    ui->ChatNumber->setVisible(true);
    ui->ChatLine->setVisible(true);
    ui->ChatButton->setVisible(true);
    ui->ShowButton->setVisible(true);
    ui->ShowMoreButton->setVisible(true);
    ui->ChatTable->setVisible(true);
    ui->SendButton->setVisible(true);
    ui->Text->setVisible(true);
    }
    return i;
}

void SocialNetworkUI::friendClicked(int row, int column){
    QString qstr = ui->tableWidget->item(row,column)->text();
    cout<<"Row: "<<row<<endl;
    string str = qstr.toStdString();
    cout<<"str: "<<str<<endl;

    ui->UserDisplay->setText(qstr);
    ui->UserDisplay->setVisible(true);

    int i = n.get_id(str);
    if(i == -1){
        return;
    }
    vector<string> s = n.get_user(i).displayPosts(0,4);
    vector<size_t> v = n.get_user(i).get_friends();

    for(std::size_t i=0;i<5; ++i){
        QTableWidgetItem* qtwi = new QTableWidgetItem();
        ui->tableWidget->setItem(i, 0, qtwi);
    }
    for(std::size_t i=0;i<5; ++i){
        QTableWidgetItem* qtwi = new QTableWidgetItem();
        ui->tableWidget->setItem(i, 1, qtwi);
    }
    for(std::size_t i=0; i<s.size()&&i<5; ++i){
        string s2= s[i];
        QString qs = QString::fromStdString(s2);

        QTableWidgetItem* qtwi = new QTableWidgetItem(qs);
        ui->tableWidget->setItem(i, 0, qtwi);
    }
    for(std::size_t i=0; i<v.size()&&i<5; ++i){
        string s1= n.get_user(v[i]).get_name();
        QString qs = QString::fromStdString(s1);
        QTableWidgetItem* qtwi = new QTableWidgetItem(qs);
        ui->tableWidget->setItem(i, 1, qtwi);
    }
    ui->BackButton->setVisible(true);
}

void SocialNetworkUI::backClicked(int id){

    ui->UserDisplay->setText(QString::fromStdString(n.get_user(id).get_name()));
    vector<string> s = n.get_user(id).displayPosts(0,4);
    vector<size_t> v = n.get_user(id).get_friends();

    for(std::size_t i=0;i<5; ++i){
        QTableWidgetItem* qtwi = new QTableWidgetItem();
        ui->tableWidget->setItem(i, 0, qtwi);
    }
    for(std::size_t i=0;i<5; ++i){
        QTableWidgetItem* qtwi = new QTableWidgetItem();
        ui->tableWidget->setItem(i, 1, qtwi);
    }
    for(std::size_t i=0; i<s.size()&&i<5; ++i){
        string s2= s[i];
        QString qs = QString::fromStdString(s2);

        QTableWidgetItem* qtwi = new QTableWidgetItem(qs);
        ui->tableWidget->setItem(i, 0, qtwi);
    }
    for(std::size_t i=0; i<v.size()&&i<5; ++i){
        string s1= n.get_user(v[i]).get_name();
        QString qs = QString::fromStdString(s1);
        QTableWidgetItem* qtwi = new QTableWidgetItem(qs);
        ui->tableWidget->setItem(i, 1, qtwi);
    }
    ui->BackButton->setVisible(false);
}

void SocialNetworkUI::shortestPath(int id){
    QString qname = ui->ShortestPathUser->text();
    string name = qname.toStdString();
    std::vector<int> v;
    v = n.shortest_path(id, n.get_id(name));
    if(v.empty()){
        ui->ShortestPathDisplay->setText(QString::fromStdString("none"));
    }else{
        string display = "";
        auto iter = v.rbegin();
        for(; iter != v.rend() - 1; iter++){
            display = display + n.get_user(*iter).get_name()+"->";
            std::cout<<"iter: "<<(*iter)<<std::endl;
        }
        display = display + n.get_user(*(v.rend()-1)).get_name();
        ui->ShortestPathDisplay->setText(QString::fromStdString(display));
    }
    //n.add_connection(name, n.get_user(id).get_name());

}
void SocialNetworkUI::suggestFriend(int id){
    int i = n.suggest_friend(id);
    std::cout<<"id of suggest friend: "<<i<<std::endl;
    if(i == -1){
        ui->SuggestFriendDisplay->setText(QString::fromStdString("All users are your friends"));
    }else{
        ui->SuggestFriendDisplay->setText(QString::fromStdString(n.get_user(i).get_name()));
    }
}
void SocialNetworkUI::showMore(int id, int chat){
    QString qname = ui->ChatLine->text();
    string name = qname.toStdString();
    QString qnumber = ui->ChatNumber->text();
    string snumber = qnumber.toStdString();
    if(n.get_id(name) == -1){
        ui->ChatNumber->setText(QString::fromStdString("Enter a friend name"));
        return;
    }
    if(snumber == ""){
        ui->ChatNumber->setText(QString::fromStdString("Enter a number"));
        return;
    }
    for (char c : snumber) {
        std::cout<<"char: "<<c<<std::endl;
        if (!std::isdigit(c)) {
            ui->ChatNumber->setText(QString::fromStdString("Enter a number"));
            return;
        }
    }

    int number = stoi(snumber);
    ui->ChatTable->setRowCount(number);
    ui->ChatTable->setColumnCount(1);
    vector<string> s = n.get_user(id).displayDMs(n.get_id(name),chat+ 0,chat + number-1);
    for(std::size_t i=0;i<number; ++i){
        QTableWidgetItem* qtwi = new QTableWidgetItem();
        ui->ChatTable->setItem(i, 0, qtwi);
    }
    for(std::size_t i=0; i<s.size()&&i<number; ++i){
        string s2= s[i];
        std::cout<<"s2: "<<s2<<std::endl;
        QString qs = QString::fromStdString(s2);

        QTableWidgetItem* qtwi = new QTableWidgetItem(qs);
        ui->ChatTable->setItem(i, 0, qtwi);
    }

}
void SocialNetworkUI::addFriendTable(int id){
    QString qname = ui->SuggestFriendDisplay->text();
    string name = qname.toStdString();
    n.add_connection(n.get_user(id).get_name(), name);
}
void SocialNetworkUI::addFriendSuggestion(int id){
    QString qname = ui->UserDisplay->text();
    string name = qname.toStdString();
    n.add_connection(n.get_user(id).get_name(), name);
}
void SocialNetworkUI::showChat(int id){
    QString qname = ui->ChatLine->text();
    string name = qname.toStdString();
    QString qnumber = ui->ChatNumber->text();
    string snumber = qnumber.toStdString();
    if(n.get_id(name) == -1){
        ui->ChatNumber->setText(QString::fromStdString("Enter a friend name"));
        return;
    }
    if(snumber == ""){
        ui->ChatNumber->setText(QString::fromStdString("Enter a number"));
        return;
    }
    for (char c : snumber) {
        std::cout<<"char: "<<c<<std::endl;
        if (!std::isdigit(c)) {
            ui->ChatNumber->setText(QString::fromStdString("Enter a number"));
            return;
        }
    }

    int number = stoi(snumber);
    ui->ChatTable->setRowCount(number);
    ui->ChatTable->setColumnCount(1);
    vector<string> s = n.get_user(id).displayDMs(n.get_id(name),0,number-1);

    for(std::size_t i=0;i<number; ++i){
        QTableWidgetItem* qtwi = new QTableWidgetItem();
        ui->ChatTable->setItem(i, 0, qtwi);
    }
    for(std::size_t i=0; i<s.size()&&i<number; ++i){
        string s2= s[i];
        std::cout<<"s2: "<<s2<<std::endl;
        QString qs = QString::fromStdString(s2);

        QTableWidgetItem* qtwi = new QTableWidgetItem(qs);
        ui->ChatTable->setItem(i, 0, qtwi);
    }
    }
void SocialNetworkUI::addChat(int id){
    QString qname = ui->ChatLine->text();
    string name = qname.toStdString();
    if(n.get_id(name) == -1){
        ui->ChatNumber->setText(QString::fromStdString("Enter a friend name"));
        return;
    }
    QString qtext = ui->Text->text();
    string stext = qtext.toStdString();
    cout<<"stext: "<<stext<<endl;
    n.get_user(n.get_id(name)).add_DM(new DirectMessage(0,stext,id,0,n.get_id(name)));
    n.get_user(id).add_DM(new DirectMessage(0,stext,id,0,n.get_id(name)));
}
