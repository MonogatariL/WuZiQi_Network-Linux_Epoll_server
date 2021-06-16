#include "wuziqi.h"
#include "ui_wuziqi.h"

#define ChessBoard_size 15

wuziqi::wuziqi(QWidget *parent) :QWidget(parent),ui(new Ui::wuziqi)
{
    ui->setupUi(this);
    back.resize(0);
    setWindowTitle("五子棋");
    this->setWindowIcon(QPixmap(":/new/prefix1/res/Title1.png"));
    white_chess.load(":/new/prefix1/res/shiro.png");
    black_chess.load(":/new/prefix1/res/kuro.png");
    background.load(":/new/prefix1/res/BackGround1.png");

    square=800/(ChessBoard_size+1);
    for(int i=0;i<ChessBoard_size;i++)
    {
        press_board.push_back(QVector<QPair<QRect,int>>());
        for(int j=0;j<ChessBoard_size;j++)
            press_board[i].push_back(QPair<QRect,int>(QRect((i+1)*square-square/3,(j+1)*square-square/3,square/3*2.5,square/3*2.5),-1));
    }
    initialization();
}

//wuziqi::wuziqi(internet *client_, QWidget *parent):client(client_),QWidget(parent),ui(new Ui::wuziqi)
//{

//    ui->setupUi(this);
//    //setFixedSize(800,800);
//    setWindowTitle("五子棋");
//    //this->setWindowIcon(QPixmap(":/new/prefix1/res/Title1.png"));
//    white_chess.load(":/new/prefix1/res/shiro.png");
//    black_chess.load(":/new/prefix1/res/kuro.png");
//    background.load(":/new/prefix1/res/BackGround1.png");
//    initialization();
//    internet_game=true;
//}

wuziqi::~wuziqi()
{
    qDebug()<<"本地游戏关闭"<<endl;
    delete ui;
}

void wuziqi::initialization()
{
    ui->label_over->setText("");
    ui->label_over->setStyleSheet("QLabel{"
                               "color:red;"//格式上非常奇怪
                               "}");
    running=true;
    back.resize(0);
    ui->Button_back->setDisabled(false);
    for(auto &x:press_board)
    {
        for(auto &y:x)
            y.second=-1;
    }
    black=true;
    update();
}

void wuziqi::win(int x, int y)
{
    int position1[4][2]={   {-1,0},//上下
                            {0,-1},//左右
                            {-1,-1},//左上右下
                            {1,-1}};//左下右上
    int position2[4][2]={   {1,0},//上下
                            {0,1},//左右
                            {1,1},//左上右下
                            {-1,1}};//左下右上
    for(int i=0;i<4;i++)
    {
        int sum=0;
        int a,b;
        a=x;b=y;
        for(int j=0;j<=4;j++)
        {
            a+=position1[i][0];
            b+=position1[i][1];
            if(a>=0&&b>=0&&a<press_board.size()&&b<press_board.size()&&press_board[a][b].second==(!black))
                sum++;
            else
                break;
        }
        a=x;b=y;
        for(int j=0;j<=4;j++)
        {
            a+=position2[i][0];
            b+=position2[i][1];
            if(a>=0&&b>=0&&a<press_board.size()&&b<press_board.size()&&press_board[a][b].second==(!black))
                sum++;
            else
                break;
        }
        if(sum>=4)
        {
            QString str;
            if(black)
            {
                str=("白棋胜利");
                ui->label_over->setText("白棋胜利");
            }
            else
            {
                str=("黑棋胜利");
                ui->label_over->setText("黑棋胜利");
            }
            ui->Button_back->setDisabled(true);
            //int ret=QMessageBox::information(this,"游戏结束",str,QMessageBox::Ok);
            running=false;
        }
    }
}

void wuziqi::take_chess(int x, int y)
{
    if(!running)return;
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
                press_board[i][j].second=black;
                black=!black;
                back.push(QPair<int,int>(i,j));
                qDebug()<<i<<" "<<j<<endl;
                win(i,j);
            }
        }
    }

    update();
}

void wuziqi::closeEvent(QCloseEvent *event)
{
    qDebug()<<"触发关闭事件啦"<<endl;
    emit game_over();
}

void wuziqi::paintEvent(QPaintEvent *)
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
    if(black)
        ui->label_show->setStyleSheet("QLabel{"
                                      "border-image:url(:/new/prefix1/res/kuro.png);"
                                      "}");
    else
        ui->label_show->setStyleSheet("QLabel{"
                                      "border-image:url(:/new/prefix1/res/shiro.png);"
                                      "}");
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

}

void wuziqi::mousePressEvent(QMouseEvent *event)
{
    take_chess(event->x(),event->y());
}



void wuziqi::on_Button_back_clicked()
{
    if(back.empty())return;
    int x=back.top().first;
    int y=back.top().second;
    back.pop();
    press_board[x][y].second=-1;
    black=!black;
    update();
}

void wuziqi::on_Button_new_clicked()
{
    initialization();
}

void wuziqi::on_Button_exit_clicked()
{
    close();
}
