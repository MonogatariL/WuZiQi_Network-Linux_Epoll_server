#include "wuziqi_internet.h"
#include "ui_wuziqi_internet.h"

#define ChessBoard_size 15

wuziqi_internet::wuziqi_internet(int x,int y,internet *client_,QString room_name,QWidget *parent):client(client_),QWidget(parent),ui(new Ui::wuziqi_internet)
{
    ui->setupUi(this);
    this->setFixedSize(1000,800);
    this->move(x,y);
    ui->Title->setText(room_name);
    setWindowTitle("五子棋网络对战");

    ui->stackedWidget->setCurrentIndex(0);
    ui->Button_black->hide();
    ui->Button_white->hide();
    ui->Button_black->setStyleSheet("QPushButton{""color:white;""border-image:url(:/new/prefix1/res/kuro.png);""}");
    ui->Button_white->setStyleSheet("QPushButton{""border-image:url(:/new/prefix1/res/shiro.png);""}");

    this->setWindowIcon(QPixmap(":/new/prefix1/res/Title1.png"));
    white_chess.load(":/new/prefix1/res/shiro.png");
    black_chess.load(":/new/prefix1/res/kuro.png");
    background.load(":/new/prefix1/res/BackGround1.png");
    ui->label_prepare->setStyleSheet("QLabel{color:rgba(0,0,0,0.3);}");
    ui->label_opponent->setStyleSheet("QLabel{""border-image:url(:/new/prefix1/res/opponent_no.png);""}");
    ui->label_prepare_->setStyleSheet("QLabel{""color:red;""}");
    ui->label_victory->setStyleSheet("QLabel{""color:red;""}");
    ui->label_wait_answer->setStyleSheet("QLabel{""color:red;""}");
    ui->label_anwser->setStyleSheet("QLabel{""color:yellow;""}");
    ui->label_victory->hide();
    ui->Label_your_color->hide();
    ui->Button_agreen->hide();
    ui->Button_refuse->hide();
    ui->label_wait_answer->hide();
    ui->label_anwser->hide();
    ui->label_msg->hide();

    wait=false;
    ban_mouse=false;
    prepare=false;
    color=-1;
    running=false;
    turn=false;
    timerId1=startTimer(500);

    back.resize(0);
    square=800/(ChessBoard_size+1);
    for(int i=0;i<ChessBoard_size;i++)
    {
        press_board.push_back(QVector<QPair<QRect,int>>());
        for(int j=0;j<ChessBoard_size;j++)
            press_board[i].push_back(QPair<QRect,int>(QRect((i+1)*square-square/3,(j+1)*square-square/3,square/3*2.5,square/3*2.5),-1));
    }
}

wuziqi_internet::~wuziqi_internet()
{
    qDebug()<<"网络游戏触发析构函数啦"<<endl;
    client->send_msg("E");
    delete ui;
}

void wuziqi_internet::initialization()
{
    //prepare=false;
    back.resize(0);
    for(auto &x:press_board)
    {
        for(auto &y:x)
            y.second=-1;
    }
    update();
}

void wuziqi_internet::take_chess(int x, int y)
{
    if(!running)return;
    if(!turn)return;
    qDebug()<<"落子坐标"<<x<<" "<<y<<endl;
    QRect R(x,y,5,5);//点击的触摸大小
    //核心是判断是否点击在周围的格子，这里是一个难点*
    for(int i=0;i<press_board.size();i++)
    {
        for(int j=0;j<press_board[i].size();j++)
        {
            if(press_board[i][j].first.intersects(R)&&press_board[i][j].second==-1)
            {
                //qDebug()<<(i+1)*50<<" "<<(j+1)*50<<endl;
                press_board[i][j].second=color;
                back.push(QPair<int,int>(i,j));
                //qDebug()<<i<<" "<<j<<endl;
                QString msg="OM00";
                switch(i)
                {
                    case 10:msg[2]='a';break;
                    case 11:msg[2]='b';break;
                    case 12:msg[2]='c';break;
                    case 13:msg[2]='d';break;
                    case 14:msg[2]='e';break;
                default:msg[2]=i+'0';
                }
                switch(j)
                {
                    case 10:msg[3]='a';break;
                    case 11:msg[3]='b';break;
                    case 12:msg[3]='c';break;
                    case 13:msg[3]='d';break;
                    case 14:msg[3]='e';break;
                default:msg[3]=j+'0';
                }
                client->send_msg(msg);
                win(i,j);
            }
        }
    }

    update();
}

void wuziqi_internet::win(char x, char y)
{
    int position1[4][2]={   {-1,0},//上下
                            {0,-1},//左右
                            {-1,-1},//左上右下
                            {1,-1}};//左下右上
    int position2[4][2]={   {1,0},//上下
                            {0,1},//左右
                            {1,1},//左上右下
                            {-1,1}};//左下右上
    bool black=turn?color:!color;
    for(int i=0;i<4;i++)
    {
        int sum=0;
        int a,b;
        a=x;b=y;
        for(int j=0;j<=4;j++)
        {
            a+=position1[i][0];
            b+=position1[i][1];
            if(a>=0&&b>=0&&a<press_board.size()&&b<press_board.size()&&press_board[a][b].second==black)
                sum++;
            else
                break;
        }
        a=x;b=y;
        for(int j=0;j<=4;j++)
        {
            a+=position2[i][0];
            b+=position2[i][1];
            if(a>=0&&b>=0&&a<press_board.size()&&b<press_board.size()&&press_board[a][b].second==black)
                sum++;
            else
                break;
        }
        if(sum>=4)
        {
            ui->label_prepare->show();
            if(black)
            {
                ui->label_victory->setText("黑棋胜利");
            }
            else
            {
                ui->label_victory->setText("白棋胜利");
            }
            on_Button_prepare_clicked();
            ui->label_prepare->show();
            ui->label_victory->show();
            ui->stackedWidget->setCurrentIndex(0);
            color=-1;
            running=false;
            return ;
        }
    }
    turn=!turn;
}

void wuziqi_internet::go_back()
{
    if(back.empty())return;
    int x=back.top().first;
    int y=back.top().second;
    back.pop();
    press_board[x][y].second=-1;
    turn=!turn;
    update();
}

void wuziqi_internet::get_prepare_information()
{
    QString msg;
    client->clear();
    client->send_msg("U");
    while(client->queue_size()<4&&client->connecting());
    msg=client->get_msg();
    msg=="1"?ui->label_opponent->setStyleSheet("QLabel{""border-image:url(:/new/prefix1/res/opponent_ok.png);""}"):
             ui->label_opponent->setStyleSheet("QLabel{""border-image:url(:/new/prefix1/res/opponent_no.png);""}");
    msg=client->get_msg();
    msg=="1"?ui->label_prepare_->setText("已准备"):ui->label_prepare_->setText("未准备");
    msg=="1"?ui->label_prepare_->setStyleSheet("QLabel{""color:green;""}"):ui->label_prepare_->setStyleSheet("QLabel{""color:red;""}");
    msg=QString("IP:%1").arg(client->get_msg());
    ui->label_ip->setText(msg);
    msg=QString("FD:%1").arg(client->get_msg());
    ui->label_fd->setText(msg);
    update();
}

void wuziqi_internet::wait_over()
{
    wait=false;
    ui->Button_back->setDisabled(false);
    ui->label_prepare->hide();
    ui->label_wait_answer->hide();
    ui->label_victory->hide();
    ui->Button_agreen->hide();
    ui->Button_refuse->hide();
    ban_mouse=false;
    //ui->label_prepare->setText("等待对方响应悔棋请求...");
}

void wuziqi_internet::closeEvent(QCloseEvent *event)
{
    qDebug()<<"网络游戏触发关闭事件啦"<<endl;
    if(running)
    {
        client->send_msg("OR");
    }
    emit game_over();
}

void wuziqi_internet::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;pen.setWidth(3);painter.setPen(pen);//设置棋盘线的宽度
    painter.drawPixmap(0,0,width(),height(),background);//设置背景
    int one_width=800/(ChessBoard_size+1);
    int one_height=800/(ChessBoard_size+1);
    int value=ChessBoard_size+1;
    int w=0;
    int h=0;
    for(int i=0;i<ChessBoard_size;i++)//画15条线，这里的画线写法是一个学习点*
    {
        w+=one_width;
        h+=one_height;
        //painter.drawLine(w,0,w,height());
        painter.drawLine(w,one_height,w,800/value*(value-1));
        //painter.drawLine(0,h,width(),h);
        painter.drawLine(one_width,h,800/value*(value-1),h);
    }
    pen.setWidth(8);painter.setPen(pen);
    painter.drawPoint(800/2,800/2);//中心点标注

    //以上是绘制棋盘，接下来就是绘制棋子
    for(auto x:press_board)
    {
        for(auto y:x)
        {
            //painter.drawRect(y.first);
            switch(y.second)
            {
                case 1:painter.drawPixmap(y.first,black_chess);break;
                case 0:painter.drawPixmap(y.first,white_chess);break;
                case -1:break;
                default:break;
            }
        }
    }
    if(running)
        if(turn)
        {
            ui->label_msg->setText("你的回合");
            ui->label_msg->setStyleSheet("QLabel{""color:green;""}");
        }
        else
        {
            ui->label_msg->setText("对手回合");
            ui->label_msg->setStyleSheet("QLabel{""color:red;""}");
        }
}

void wuziqi_internet::mousePressEvent(QMouseEvent *event)
{
    if(!ban_mouse)
        take_chess(event->x(),event->y());
}

void wuziqi_internet::timerEvent(QTimerEvent *event)
{
    if(!client->connecting())
    {
        QMessageBox::information(this,"Warnning","网络连接中断",QMessageBox::Ok);
        client->clear();
        close();
        return ;
    }
    if(!running)
    {
        ui->label_msg->hide();
        if(!client->queue_empty()&&client->get_msg()=="start")
        {
            initialization();
            ui->label_victory->hide();
            ui->stackedWidget->setCurrentIndex(1);
            ui->Button_black->show();
            ui->Button_white->show();
            ui->label_msg->show();
            ui->label_prepare->hide();
            ui->Label_your_color->hide();
            running=true;
            Sleep(300);
            return;
        }
        get_prepare_information();
    }
    else if(!wait)
    {
        if(color==-1)
        {
            while(!client->queue_empty())
            {
                QString msg=client->get_msg();
                if(msg=="c1")
                {
                    color=1;
                    turn=true;
                    ui->Button_black->hide();
                    ui->Button_white->hide();
                    ui->Label_your_color->show();
                    ui->Label_your_color->setStyleSheet("QLabel{""border-image:url(:/new/prefix1/res/kuro.png);""}");
                }
                else if(msg=="c0")
                {
                    color=0;
                    turn=false;
                    ui->Button_black->hide();
                    ui->Button_white->hide();
                    ui->Label_your_color->show();
                    ui->Label_your_color->setStyleSheet("QLabel{""border-image:url(:/new/prefix1/res/shiro.png);""}");
                }
            }
        }
        else
        {
            while(!client->queue_empty())
            {
                QString recv=client->get_msg();
                string msg=recv.toStdString();
                if(msg[0]=='O')
                switch(msg[1])
                {
                    case 'M':
                    {
                        int x,y;
                        if(msg[2]>='a'&&msg[2]<='e')
                        {
                            x=msg[2]-'a'+10;
                        }
                        else
                            x=msg[2]-'0';
                        if(msg[3]>='a'&&msg[3]<='e')
                        {
                            y=msg[3]-'a'+10;
                        }
                        else
                            y=msg[3]-'0';
                        press_board[x][y].second=!color;
                        back.push(QPair<int,int>(x,y));;
                        update();
                        win(x,y);
                    }break;
                    case 'B':
                    {
                        ui->label_victory->setText("是否同意对手悔棋");
                        ui->label_victory->show();
                        ui->Button_agreen->show();
                        ui->Button_refuse->show();
                        ui->Button_back->setDisabled(true);
                        ban_mouse=true;
                    }break;
                    case 'N':
                {
                    ui->LE_recv->append("[对手]:"+recv.mid(2));
                }
                    break;
                    case 'R':
                {
                    on_Button_prepare_clicked();
                    ui->label_prepare->show();
                    QTimer *timer=new QTimer(this);
                    timer->start(5000);
                    connect(timer,&QTimer::timeout,this,[=](){ui->label_victory->hide();timer->stop();delete(timer);});
                    ui->label_victory->setText("对手离开了游戏!!!");
                    ui->label_victory->show();
                    ui->stackedWidget->setCurrentIndex(0);
                    color=-1;
                    running=false;
                }break;
                case 'S':
                {
                    on_Button_prepare_clicked();
                    ui->label_prepare->show();
                    ui->label_victory->setText("对手认输了");
                    ui->label_victory->show();
                    ui->stackedWidget->setCurrentIndex(0);
                    color=-1;
                    running=false;
                    return ;
                }
                    default:break;
                }
            }
        }
    }
    else
    {
        while(!client->queue_empty())
        {
            string msg=client->get_msg().toStdString();
            qDebug()<<__LINE__<<endl;
            if(msg[0]=='O'&&msg.size()==3)
            switch(msg[1])
            {
                case 'B':
                {
                    QTimer *timer=new QTimer(this);
                    if(msg[2]=='1')
                    {
                        ui->label_anwser->setText("对手同意悔棋");
                        ui->label_anwser->show();
                        if(turn){go_back();go_back();}
                        else go_back();
                    }
                    else
                    {
                        ui->label_anwser->setText("对手不同意悔棋");
                    }
                    ui->label_anwser->show();

                    connect(timer,&QTimer::timeout,this,[=](){ui->label_anwser->hide();timer->stop();delete(timer);});
                    timer->start(3000);
                    wait_over();
                }break;
            }
        }
    }

}

void wuziqi_internet::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==16777220)
        on_Button_send_clicked();
}

void wuziqi_internet::on_Button_exit_room_clicked()
{
    close();
}

void wuziqi_internet::on_Button_prepare_clicked()
{
    int ret;
    //Sleep(500);
    client->send_msg("prepare");
    if(ret==SOCKET_ERROR)
        return;
    else if(prepare)
    {
        ui->label_prepare->setText("Please_Prepare...");
        ui->label_prepare->setStyleSheet("QLabel{color:rgba(255,0,0,0.3);}");
    }
    else
    {
        ui->label_prepare->setText("Please_Wait...");
        ui->label_prepare->setStyleSheet("QLabel{color:rgba(0,255,0,0.3);}");
    }
    prepare=!prepare;
}

void wuziqi_internet::on_Button_black_clicked()
{
    if(color!=-1)
        return;
    client->send_msg("color1");
}

void wuziqi_internet::on_Button_white_clicked()
{
    if(color!=-1)
        return;
    client->send_msg("color0");
}

void wuziqi_internet::on_Button_exiting_clicked()
{
    close();
}

void wuziqi_internet::on_Button_back_clicked()
{
    if(!running||back.size()==0||color==-1)
    {
        return;
    }
    client->send_msg("OB");
    ban_mouse=true;
    wait=true;
    ui->Button_back->setDisabled(true);
    ui->label_wait_answer->setText("等待对方响应悔棋请求");
    ui->label_wait_answer->show();

}

void wuziqi_internet::on_Button_agreen_clicked()
{
    client->send_msg("OB1");
    if(!turn){go_back();go_back();}else go_back();
    wait_over();
}

void wuziqi_internet::on_Button_refuse_clicked()
{
    client->send_msg("OB0");
    wait_over();
}


void wuziqi_internet::on_Button_send_clicked()
{
    QString msg="ON"+ui->LE_send->text();
    ui->LE_recv->append("[你]:"+ui->LE_send->text());
    ui->LE_send->clear();
    client->send_msg(msg);
}

void wuziqi_internet::on_Button_back_surrender_clicked()
{
    if(!running||color==-1)
    {
        return;
    }
    client->send_msg("OS");
    on_Button_prepare_clicked();
    ui->label_victory->setText("你已经认输");
    ui->label_prepare->show();
    ui->label_victory->show();
    ui->stackedWidget->setCurrentIndex(0);
    color=-1;
    running=false;
}
