
#ifndef SOCIALNETWORKUI_H
#define SOCIALNETWORKUI_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class SocialNetworkUI; }
QT_END_NAMESPACE
#include "network.h"


class SocialNetworkUI : public QMainWindow

{
    Q_OBJECT

public:
    SocialNetworkUI(QWidget *parent = nullptr);
    ~SocialNetworkUI();
private slots:
    int login();
    void friendClicked(int row, int column);
    void backClicked(int id);
    void shortestPath(int id);
    void suggestFriend(int id);
    void showChat(int id);
    void showMore(int id, int chat);
    void addFriendTable(int id);
    void addFriendSuggestion(int id);
    void addChat(int id);


private:
    int chat = 0;
    Ui::SocialNetworkUI *ui;
    network n;
};

#endif // SOCIALNETWORKUI_H
