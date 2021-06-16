#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<error.h>

#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>


using namespace std;
#define msg_size 1024
void R_signal(int client_fd);//处理客户端刷新战局的请求
void C_signal(char* msg,int fd);//处理客户端创建房间的请求
void E_signal(int client_fd);//处理客户端退出房间的请求
void J_signal(int fd,char* msg);//处理客户端加入房间的请求
void U_signal(int fd);//处理客户端更新对手准备状态的请求


void initialization_server(struct sockaddr_in& server_addr,int &server_fd,int argc,char *argv[])
{   
    server_fd=socket(PF_INET,SOCK_STREAM|SOCK_NONBLOCK,IPPROTO_TCP);
    server_addr.sin_family=AF_INET;
    switch(argc)
    {
        case 2:
        {
            server_addr.sin_port=htons(atoi(argv[1]));
            server_addr.sin_addr.s_addr=INADDR_ANY;
        }break;
        default:
        {
            server_addr.sin_port=htons(4396);
            server_addr.sin_addr.s_addr=INADDR_ANY;
        }
    }
}
void Error_msg(string msg)
{
    cout<<"Error_msg:"<<msg<<endl;
}

struct client_information
{
	int opponent_fd;//对手的套接字
	bool prepare;//准备状态
    bool master;//是否为房间的创建者
    int room_num;//房间号
	client_information() :opponent_fd(0), prepare(0),room_num(-1),master(false){}
};
struct room_information
{   
    int client_fd;//房间中客人的套接字
    string room_name;//房间的名称
    int master_fd;//房间中主人的套接字
    room_information(string name,int fd):room_name(name),master_fd(fd),client_fd(-1){}
};

map<int,client_information>hash_client;//每一个套接字对应一个客户端信息
map<int,struct sockaddr_in>client_addrs;//每一个套接字对应一个客户端的ip地址等信息
vector<room_information>rooms;//房间
vector<int>client_fds;//所有客户端套接字

int main(int argc,char* argv[])
{   
    int idle_fd=open("/dev/null",O_RDONLY|O_CLOEXEC);
    int server_fd,client_fd;
    struct sockaddr_in server_addr,client_addr;

    socklen_t client_sz;
    int ret=0;;
    char msg[msg_size];
    initialization_server(server_addr,server_fd,argc,argv);

    int optset=1;
    ret=setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&optset,sizeof(optset));assert(ret==0);
    ret=bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));assert(ret==0);
    ret=listen(server_fd,5);assert(ret==0);

    struct epoll_event event;
    vector<struct epoll_event>events(16);
    int epoll_fd;

    epoll_fd=epoll_create(5555);
    event.data.fd=server_fd;
    event.events=EPOLLIN;

    epoll_ctl(epoll_fd,EPOLL_CTL_ADD,server_fd,&event);


    //使用EPOLL模型
    while(1)
    {
        int event_cnt=epoll_wait(epoll_fd,&*events.begin(),static_cast<int>(events.size()),-1);
        if(event_cnt==-1)
        {
            if(errno==EINTR)
                continue;
            Error_msg("epoll_wait");
        }
        if(event_cnt==0)
            continue;
        if((size_t)event_cnt==events.size())
            events.resize(events.size()*2);
        for(int i=0;i<event_cnt;i++)
        {
            if(events[i].data.fd==server_fd)
            {
                client_sz=sizeof(client_sz);
                client_fd=accept4(server_fd,(struct sockaddr*)&client_addr,&client_sz,O_NONBLOCK);
                //client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&client_sz);

                if(client_fd==-1)
                {
                    if(errno==EMFILE)
                    {
                        close(idle_fd);
                        idle_fd=accept(server_fd,NULL,NULL);
                        close(idle_fd);
                        idle_fd=open("/dev/null",O_RDONLY|O_NONBLOCK);
                        continue;
                    }
                    else
                    Error_msg("accept4?");
                }
                printf("[%d][Client]<IP:%s><PT:%d><***CONNECT***>\n",__LINE__,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
                client_addrs[client_fd]=client_addr;
                event.data.fd=client_fd;
                event.events=EPOLLIN|EPOLLET;
                epoll_ctl(epoll_fd,EPOLL_CTL_ADD,client_fd,&event);
                client_fds.push_back(client_fd);

                hash_client[client_fd];//**************r
            }
            else if(events[i].events&EPOLLIN)
            {
                client_fd=events[i].data.fd;
                if(client_fd<0)
                    continue;
                memset(msg,0,sizeof(msg));
                ret=read(client_fd,msg,sizeof(msg));

                if(ret<=0)
                {   
                    printf("[%d][CLient]<FD:%d><***CLOSE***>\n",__LINE__,client_fd);
                    E_signal(client_fd);
                    close(client_fd);
                    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,client_fd,NULL);

                   client_fds.erase(remove(client_fds.begin(),client_fds.end(),client_fd),client_fds.end());
                   continue;
                }
                if(msg[0]=='O')//当消息头字母为O时候，代表为opponent消息，此类消息直接原地传回对手客户端处理
                switch(msg[1])
                {
                    case 'M':
                    {
                        write(hash_client[client_fd].opponent_fd,msg,strlen(msg));
                    }break;
                    case 'B':
                    {
                        write(hash_client[client_fd].opponent_fd,msg,strlen(msg));
                    }break;
                    case 'N':
                    {
                        write(hash_client[client_fd].opponent_fd,msg,strlen(msg));
                    }break;
                    case 'R':
                    {
                        write(hash_client[client_fd].opponent_fd,msg,strlen(msg));
                    }break;
                    case 'S':
                    {
                        write(hash_client[client_fd].opponent_fd,msg,strlen(msg));
                    }
                }
                //以下三个if语句中消息处理分别表示接受到客户端的准备请求（服务器这边会更新准备信息）、原地转发先手并给对手传送后手的消息、原地转发后手并给对手传送先手的消息
                if(strcmp(msg,"prepare")==0)
                {
                    hash_client[client_fd].prepare=!hash_client[client_fd].prepare;
                    if(hash_client[client_fd].prepare&&hash_client[client_fd].opponent_fd>0&&hash_client[hash_client[client_fd].opponent_fd].prepare)
                    {   
                        //printf("[%d]game_start",__LINE__);
                        write(client_fd,"/Zstart",strlen("/Zstart"));
                        write(hash_client[client_fd].opponent_fd,"/Zstart",strlen("/Zstart"));
                    }
                }
                if(strcmp(msg,"color1")==0)
                {
                    write(client_fd,"c1",strlen("c1"));
                    write(hash_client[client_fd].opponent_fd,"c0",strlen("c0"));
                }
                if(strcmp(msg,"color0")==0)
                {
                    write(client_fd,"c0",strlen("c0"));
                    write(hash_client[client_fd].opponent_fd,"c1",strlen("c1"));
                }
                //特殊信息处理，一般是用于游戏开始前的客户端服务端交互
                switch(msg[0])
                {
                    case 'R':R_signal(client_fd);break;
                    case 'C':C_signal(msg,client_fd);break;
                    case 'E':E_signal(client_fd);break;
                    case 'J':J_signal(client_fd,msg);break;
                    case 'U':U_signal(client_fd);break;
                    //default:break;
                }
                //printf("[%d][CLient%d]<%d>:%s\n",__LINE__,client_fd,ret,msg);
                //write(client_fd,msg,strlen(msg));
            }
        }
    }
    close(server_fd);
    close(epoll_fd);
    return 0;
}
void R_signal(int client_fd)
{
    int sum=0;

    char msg_[1024];
    for(auto x:rooms)
    {
        if(x.client_fd==-1)
            sum++;
    }
    memset(msg_,0,sizeof(msg_));
    sprintf(msg_,"/S%ld/S%d",client_fds.size(),sum);
    //printf("[%d]%d\n",__LINE__,sum);
    write(client_fd,msg_,strlen(msg_));
    for(auto x:rooms)
    {
        if(x.client_fd==-1)
        {   
            memset(msg_,0,sizeof(msg_));
            sprintf(msg_,"/N%s",x.room_name.c_str());
            //printf("[%d]%s\n",__LINE__,msg_);
            write(client_fd,msg_,strlen(msg_));
            
            memset(msg_,0,sizeof(msg_));
            sprintf(msg_,"/I%s",inet_ntoa(client_addrs[x.master_fd].sin_addr));
            //printf("[%d]%s\n",__LINE__,msg_);
            write(client_fd,msg_,strlen(msg_));

            memset(msg_,0,sizeof(msg_));
            sprintf(msg_,"/F%d",x.master_fd);
            //printf("[%d]%s\n",__LINE__,msg_);
            write(client_fd,msg_,strlen(msg_));
        }
    }
}
void C_signal(char* msg,int fd)
{   
    char buf[1024];
    memset(buf,0,sizeof(buf));
    for(int i=2;msg[i]!='\0';i++)
        buf[i-2]=msg[i];
    //printf("[%d]%s\n",__LINE__,buf);
    room_information room(buf,fd);
    rooms.push_back(room);
    hash_client[fd].room_num=rooms.size()-1;
    hash_client[fd].master=true;
}
void E_signal(int fd)
{   
    char msg[1024];
    memset(msg,0,sizeof(msg));
    if(hash_client[fd].room_num==-1)
        return ;
    if(!hash_client[fd].master)
    {
        rooms[hash_client[fd].room_num].client_fd=-1;
        // hash_client[fd].room_num=-1;
        // hash_client[fd].prepare=0;
        // hash_client[fd].opponent_fd=0;
        hash_client[hash_client[fd].opponent_fd].opponent_fd=0;
        //sprintf(msg,"/O0");
        //write(hash_client[fd].opponent_fd,msg,strlen(msg));
        hash_client[fd]=client_information();
        return ;
    }
    else
    {
        if(hash_client[fd].opponent_fd>0)
        {
            int client_fd=hash_client[fd].opponent_fd;
            int room_num=hash_client[fd].room_num;
            hash_client[client_fd].opponent_fd=0;
            hash_client[client_fd].master=true;
            rooms[room_num].master_fd=client_fd;
            rooms[room_num].client_fd=-1;
        }
        else
        {
            int r=hash_client[fd].room_num;
            rooms.erase(rooms.begin()+r,rooms.begin()+r+1);
            for(int i=r;i<rooms.size();i++)
            {
                if(rooms[i].client_fd>0)
                    hash_client[rooms[i].client_fd].room_num=i;
                hash_client[rooms[i].master_fd].room_num=i;
            }
        }
            hash_client[fd]=client_information();
    }
}
void J_signal(int fd,char* msg)
{
    int sum=0;
    for(int i=1;msg[i]!='\0';i++)
        sum=sum*10+msg[i]-'0';
    if(sum<=0||hash_client[sum].room_num<0||hash_client[sum].opponent_fd>0)
    {
        write(fd,"/Zerror",strlen("/Zerror"));
        return;
    }
    hash_client[sum].opponent_fd=fd;
    rooms[hash_client[sum].room_num].client_fd=fd;
    hash_client[fd].opponent_fd=sum;
    hash_client[fd].room_num=hash_client[sum].room_num;
    write(fd,"/Zsuccess",strlen("/Zsuccess"));
}
void U_signal(int fd)
{
    char msg[1024];
    memset(msg,0,sizeof(msg));
    if(hash_client[fd].opponent_fd>0)
        sprintf(msg,"/Z1/Z%d/Z%s/Z%d",hash_client[hash_client[fd].opponent_fd].prepare,
        inet_ntoa(client_addrs[hash_client[fd].opponent_fd].sin_addr),hash_client[fd].opponent_fd);
    else
        sprintf(msg,"/Z0/Z /Z /Z ");
    write(fd,msg,strlen(msg));
}
