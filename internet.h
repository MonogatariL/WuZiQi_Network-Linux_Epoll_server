#ifndef INTERNET_H
#define INTERNET_H

#include<QQueue>
#include<QString>
#include<winsock2.h>
#include<stdio.h>
#include<iostream>
#include<process.h>

using namespace std;

class internet
{
public:
    internet();
    ~internet();

    bool connect();
    void disconnect();
    bool connecting();

    bool queue_empty();
    int queue_size();
    SOCKET get_client_fd();
    void clear();

    int send_msg(QString res);
    QString get_msg();
    void set_addr(QString);
    void set_port(QString);
    void put_msg(QString res);

    void msg_handle(QString);
    int msg_end(int,QString);
    bool connect_thread_running;
private:

    WSADATA wsadata;
    SOCKADDR_IN client_addr;
    SOCKET client_fd;

    bool connecting_;
    bool recving_;

    QQueue<QString> msg_queue;
};

unsigned WINAPI recv_msg(void* arg);

#endif // INTERNET_H
