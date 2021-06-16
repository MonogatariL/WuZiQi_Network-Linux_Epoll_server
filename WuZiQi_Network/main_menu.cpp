#include "main_menu.h"
#include "ui_main_menu.h"

unsigned WINAPI connect_thread(void *arg);

Main_Menu::Main_Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Main_Menu)
{
    ui->setupUi(this);
    //this->move(0,0);
    this->setFixedSize(600,600);
    setWindowTitle("五子棋网络对战");
    this->setWindowIcon(QPixmap(":/new/prefix1/res/Title1.png"));
    client=new internet();
    ui->stackedWidget->setCurrentIndex(0);

    tableModel = new QStandardItemModel(this);
    ui->tableView->setModel(tableModel);

    columnTitles << "房间信息" << "IP地址" <<"套接字"<<"进入房间";
    tableModel->setHorizontalHeaderLabels(columnTitles);

//    ui->stackedWidget->setStyleSheet("QLabel{"
//                                     "border-image:url(:/new/prefix1/res/1.png);"
//                                     "}")

    ui->tableView->setColumnWidth(0,265);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setColumnWidth(3,130);
    ui->Button_update_diary->hide();

    ui->Button_save_set->hide();
    ui->Button_initialization->hide();
    ui->LE_IP->hide();
    ui->LE_PT->hide();
    ui->label_ip->hide();
    ui->label_pt->hide();
    ui->label_information->hide();
}

Main_Menu::~Main_Menu()
{
    qDebug()<<"主界面析构函数"<<endl;
    delete client;
    delete ui;
    delete tableModel;
}

void Main_Menu::timerEvent(QTimerEvent *event)
{
    if(client->connect_thread_running)
    {
          ui->label_connect_stat->setStyleSheet("QLabel{""color:blue;""}");
          ui->label_connect_stat->setText("<正在连接服务器...>");
          return;
    }
    else if(client->connecting())
    {
        ui->Button_refresh->setDisabled(false);
        ui->Button_create->setDisabled(false);
        ui->label_connect_stat->setStyleSheet("QLabel{""color:green;""}");
        ui->label_connect_stat->setText("已连接服务器-<创建或者加入对局>");
        return;
    }
    else
    {
        ui->label_connect_stat->setStyleSheet("QLabel{""color:red;""}");
        ui->label_connect_stat->setText("<请连接服务器>");
        ui->Button_refresh->setDisabled(true);
        ui->Button_create->setDisabled(true);
        return ;
    }

}

void Main_Menu::on_Button_local_game_clicked()
{
    wuziqi *wuziqi_local=new wuziqi();
    wuziqi_local->show();
    this->hide();
    connect(wuziqi_local,&wuziqi::game_over,this,[=](){this->show();delete wuziqi_local;});
}

void Main_Menu::on_Button_exit_clicked()
{
    close();
}

void Main_Menu::on_Button_net_game_clicked()
{
    timerId=startTimer(500);
    on_Button_reconnect_clicked();
//    Sleep(100);
//    if(client->connecting())
//        on_Button_refresh_clicked();
    ui->label_connect_stat->setStyleSheet("QLabel{""color:red;""}");
    ui->label_create_name->setStyleSheet("QLabel{""color:orange;""}");
    ui->label_connect_stat->setText("<请连接服务器>");
    ui->stackedWidget->setCurrentIndex(1);
    ui->Button_refresh->setDisabled(true);
    ui->Button_create->setDisabled(true);
}

void Main_Menu::on_Button_exit_net_clicked()
{
    tableModel->removeRows(0,tableModel->rowCount());
    killTimer(timerId);
    if(client->connect_thread_running)
        client->connect_thread_running=false;
    if(client->connecting())
        client->disconnect();
    ui->stackedWidget->setCurrentIndex(0);
}

void Main_Menu::on_Button_reconnect_clicked()
{
    if(client->connecting())
        return ;
    HANDLE thread=(HANDLE)_beginthreadex(NULL,0,connect_thread,(void*)client,0,NULL);
}

unsigned WINAPI connect_thread(void *arg)
{
    internet *client=(internet*)arg;
    qDebug()<<"线程开始"<<endl;
    client->connect();
    qDebug()<<"线程结束"<<endl;
}

void Main_Menu::on_Button_create_clicked()
{
    if(!client->connecting())
        return;
    QString room_name="C:"+ui->LineEdit1->text();
    int ret=client->send_msg(room_name);
    if(ret==SOCKET_ERROR)
    {
        QMessageBox::information(this,"网络对战","房间创建失败,请重试",QMessageBox::Ok);
        return ;
    }
    client->clear();
    wuziqi_internet *wuziqi_internet_game=new wuziqi_internet(this->x(),this->y(),client,ui->LineEdit1->text());
    wuziqi_internet_game->show();
    this->hide();
    connect(wuziqi_internet_game,&wuziqi_internet::game_over,this,[=](){qDebug()<<"www"<<endl;delete wuziqi_internet_game;this->show();});
}

void Main_Menu::on_Button_refresh_clicked()
{
    client->clear();
    if(!client->connecting())
        return ;
    client->send_msg("R");
    Sleep(300);
    int people=client->get_msg().toInt();
    ui->label_people->setText(QString("在线人数:%1").arg(people));
    string str=client->get_msg().toStdString();
    int sum=0;
    for(int i=0;i<str.size();i++)
        sum=sum*10+str[i]-'0';
    tableModel->removeRows(0,tableModel->rowCount());
    for(int i=0;i<sum;i++)
    {
        QString get;
        QPushButton *button = new QPushButton("Join");

        get=client->get_msg();
        tableModel->setItem(i, 0, new QStandardItem(get));
        button->setProperty("Name",get);

        get=client->get_msg();
        tableModel->setItem(i, 1, new QStandardItem(get));
        button->setProperty("Ip",get);

        get=client->get_msg();
        tableModel->setItem(i, 2, new QStandardItem(get));
        button->setProperty("Fd",get);

        ui->tableView->setIndexWidget(tableModel->index(i, 3), button);
        connect(button,&QPushButton::pressed,this,&Main_Menu::join_game);
    }
    if(sum==0)
        ui->tableView->setColumnWidth(0,265);
    else
        ui->tableView->setColumnWidth(0,250);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setColumnWidth(3,130);
    client->clear();
}

void Main_Menu::join_game()
{
    client->clear();
    QPushButton *button = (QPushButton *)sender();
    QString msg="J"+button->property("Fd").toString();
    if(!client->connecting())
            return;
    int ret=client->send_msg(msg);
    Sleep(300);
    if(ret==SOCKET_ERROR||client->queue_empty()||client->get_msg()!="success")
    {
        QMessageBox::information(this,"网络对战","房间加入失败,请重试",QMessageBox::Ok);
        on_Button_refresh_clicked();
        return ;
    }
    client->clear();
    qDebug()<<"加入房间啦:"<<button->property("Fd").toString()<<endl;
    tableModel->removeRows(0,tableModel->rowCount());
    wuziqi_internet *wuziqi_internet_game=new wuziqi_internet(this->x(),this->y(),client,button->property("Name").toString());
    wuziqi_internet_game->show();
    this->hide();
    connect(wuziqi_internet_game,&wuziqi_internet::game_over,this,[=](){delete wuziqi_internet_game;on_Button_refresh_clicked();this->show();});
}


void Main_Menu::on_Button_author_clicked()
{
    QMessageBox::information(this,"STAFF","制作者:MonogatariL\nQQ:1060483009",QMessageBox::Ok);
}

void Main_Menu::on_Button_set_clicked()
{
    ui->Button_save_set->isVisible()?ui->Button_save_set->hide():ui->Button_save_set->show();
    ui->Button_initialization->isVisible()?ui->Button_initialization->hide():ui->Button_initialization->show();
    ui->LE_IP->isVisible()?ui->LE_IP->hide():ui->LE_IP->show();
    ui->LE_PT->isVisible()?ui->LE_PT->hide():ui->LE_PT->show();
    ui->label_ip->isVisible()?ui->label_ip->hide():ui->label_ip->show();
    ui->label_pt->isVisible()?ui->label_pt->hide():ui->label_pt->show();
    ui->label_information->isVisible()?ui->label_information->hide():ui->label_information->show();
}

void Main_Menu::on_Button_save_set_clicked()
{
    client->set_addr(ui->LE_IP->text());
    client->set_port(ui->LE_PT->text());
}

void Main_Menu::on_Button_initialization_clicked()
{
    ui->LE_IP->setText("81.69.223.92");
    ui->LE_PT->setText("4396");
}
