#include "main_menu.h"
#include "wuziqi.h"
#include <QApplication>
#include "wuziqi_internet.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Main_Menu w;
    //wuziqi_internet w;
    w.show();

    //wuziqi c;
    //wuziqi *d=new wuziqi();
    //d->show();
    return a.exec();
}
//客户端：
//    R"refresh"
//    C"create:*****" 房间信息
//    G"go:* *"
//    N"newgame"
//    P"prepare"
//    B"back"
//    E"exit"
//    M"msg:****"
//    J"join:*****"
//服务端：
//    "black"
//    "room_list:x ***** *"  房间数量x x个房间的信息和房主的ip地址
//    "go:* *"
//    "newgame?"
//    "back?"
//    "exit!"
//    "msg:****"
//    "game_start"


/*
struct wz
{
    int fd;存放对手的套接字，为0则无
    int prepare;1为准备0为没准备-1为游戏开始中

}


*/
