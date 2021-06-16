#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QWidget>
#include<QtWidgets>
#include "internet.h"
#include<QtWidgets>
#include<QDebug>
#include<stdio.h>
#include<stdlib.h>
#include"wuziqi.h"
#include"wuziqi_internet.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Main_Menu; }
QT_END_NAMESPACE

class Main_Menu : public QWidget
{
    Q_OBJECT

public:
    Main_Menu(QWidget *parent = nullptr);
    ~Main_Menu();
    internet *client;
    int timerId;

    QStandardItemModel *tableModel;
    QStringList columnTitles;
    //int bug1=0;//在加入其他房间游戏时，有时候会打开两个游戏，原因猜测是多次点击join按钮
    void join_game();

protected:
    void timerEvent(QTimerEvent* event);

private slots:
    void on_Button_local_game_clicked();

    void on_Button_exit_clicked();

    void on_Button_net_game_clicked();

    void on_Button_exit_net_clicked();

    void on_Button_reconnect_clicked();

    void on_Button_create_clicked();

    void on_Button_refresh_clicked();

    void on_Button_author_clicked();

    void on_Button_set_clicked();

    void on_Button_save_set_clicked();

    void on_Button_initialization_clicked();

private:
    Ui::Main_Menu *ui;
};
#endif // MAIN_MENU_H
