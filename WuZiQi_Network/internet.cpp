#include "internet.h"
#include<QDebug>
unsigned WINAPI recv_msg(void *arg);
int i=0;
internet::internet()
{
    WSAStartup(MAKEWORD(2,2),&wsadata);
    client_fd=socket(PF_INET,SOCK_STREAM,0);

    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(4396);
    client_addr.sin_addr.s_addr=inet_addr("118.31.247.104");
    //client_addr.sin_addr.s_addr=inet_addr("192.168.33.129");
    connect_thread_running=false;
    connecting_=false;
    recving_=false;
}

internet::~internet()
{
    qDebug()<<"网络连接触发析构函数啦"<<endl;
    closesocket(client_fd);
    WSACleanup();
}

bool internet::connect()
{
    if(connecting_)
        return true;
    connect_thread_running=true;
    client_fd=socket(PF_INET,SOCK_STREAM,0);
    for(int i=0;i<10&&connect_thread_running;i++)
    {
        int ret=::connect(client_fd,(struct sockaddr*)&client_addr,sizeof(client_addr));
        if(ret==0)
        {
            connecting_=true;
            recving_=true;
            connect_thread_running=false;
            _beginthreadex(NULL,0,recv_msg,(void*)this,0,NULL);
            return true;
        }
        qDebug()<<"请求连接中"<<i<<endl;
    }
    connect_thread_running=false;
    return false;
}

void internet::disconnect()
{
    if(!connecting_)
        return;
    connecting_=false;
    recving_=false;
    closesocket(client_fd);
}

bool internet::connecting()
{
    return connecting_;
}

bool internet::queue_empty()
{
    return msg_queue.empty();
}

int internet::queue_size()
{
    return msg_queue.size();
}

SOCKET internet::get_client_fd()
{
    return client_fd;
}

void internet::clear()
{
    msg_queue.clear();
}

int internet::send_msg(QString res)
{
    if(connecting())
        return send(get_client_fd(),res.toUtf8().data(),strlen(res.toUtf8().data()),0);
    else
        return SOCKET_ERROR;
}

QString internet::get_msg()
{
    if(!connecting_||msg_queue.size()==0)
        return "";
    QString msg=msg_queue.front();
    //qDebug()<<"get_msg:"<<msg<<endl;
    msg_queue.pop_front();
    return msg;
}

void internet::set_addr(QString addr)
{
    if(connecting_)return;
    client_addr.sin_addr.s_addr=inet_addr(addr.toUtf8().data());
}

void internet::set_port(QString port)
{
    if(connecting_)return;
    client_addr.sin_port=htons(port.toInt());

}

void internet::put_msg(QString res)
{
    msg_queue.push_back(res);
    qDebug()<<"put_msg:"<<res<<endl;
}

void internet::msg_handle(QString res)
{
    for(int i=0;i<res.size();i++)
    {
        if(res[i]=='/'&&(i+1<res.size()))
        {
            switch(res[i+1].unicode())
            {
                case 'N':i=msg_end(i+2,res)-1;break;
                case 'S':i=msg_end(i+2,res)-1;break;
                case 'I':i=msg_end(i+2,res)-1;break;
                case 'F':i=msg_end(i+2,res)-1;break;
                case 'Z':i=msg_end(i+2,res)-1;break;
                default:i=msg_end(i+2,res)-1;break;
            }
        }
        else
        {
            put_msg(res);
            return;
        }
    }
}

int internet::msg_end(int index,QString msg)
{
    if(index==msg.size())
        return index;
    QString str;
    for(;index<msg.size();index++)
    {
        if(msg[index]=='/')
        {
           put_msg(str);
           return index;
        }
            str+=msg[index];
    }
    put_msg(str);
    return index;
}

unsigned WINAPI recv_msg(void *arg)
{
    internet *client=(internet*)arg;
    SOCKET client_fd=client->get_client_fd();
    int ret;
    char msg[1024];
    while(1)
    {
        memset(msg,0,sizeof(msg));
        ret=recv(client_fd,msg,sizeof(msg),0);
        //qDebug()<<"[recv]"<<endl;
        if(ret<=0)
        {
            qDebug()<<"服务器炸了"<<endl;
            client->disconnect();
            return NULL;
        }
        qDebug()<<"recv_msg:"<<msg<<endl;
        client->msg_handle(msg);
    }
    return NULL;
}
