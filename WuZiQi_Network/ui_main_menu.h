/********************************************************************************
** Form generated from reading UI file 'main_menu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_MENU_H
#define UI_MAIN_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Main_Menu
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *Button_author;
    QPushButton *Button_local_game;
    QPushButton *Button_net_game;
    QPushButton *Button_exit;
    QPushButton *Button_set;
    QLineEdit *LE_IP;
    QLineEdit *LE_PT;
    QPushButton *Button_save_set;
    QPushButton *Button_initialization;
    QLabel *label_ip;
    QLabel *label_pt;
    QLabel *label_information;
    QPushButton *Button_update_diary;
    QWidget *page_2;
    QLabel *label_create_name;
    QTableView *tableView;
    QPushButton *Button_refresh;
    QLineEdit *LineEdit1;
    QPushButton *Button_reconnect;
    QPushButton *Button_create;
    QPushButton *Button_exit_net;
    QLabel *label_connect_stat;
    QLabel *label_people;

    void setupUi(QWidget *Main_Menu)
    {
        if (Main_Menu->objectName().isEmpty())
            Main_Menu->setObjectName(QString::fromUtf8("Main_Menu"));
        Main_Menu->resize(600, 600);
        stackedWidget = new QStackedWidget(Main_Menu);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setEnabled(true);
        stackedWidget->setGeometry(QRect(0, 0, 600, 600));
        stackedWidget->setMinimumSize(QSize(600, 600));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setStyleSheet(QString::fromUtf8("#page{border-image:url(:/new/prefix1/res/BackGround2.png)}"));
        Button_author = new QPushButton(page);
        Button_author->setObjectName(QString::fromUtf8("Button_author"));
        Button_author->setGeometry(QRect(40, 10, 20, 20));
        Button_author->setMinimumSize(QSize(20, 20));
        Button_author->setMaximumSize(QSize(20, 20));
        Button_author->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        Button_local_game = new QPushButton(page);
        Button_local_game->setObjectName(QString::fromUtf8("Button_local_game"));
        Button_local_game->setGeometry(QRect(200, 180, 200, 80));
        Button_local_game->setMinimumSize(QSize(200, 80));
        Button_local_game->setMaximumSize(QSize(200, 80));
        Button_local_game->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        Button_net_game = new QPushButton(page);
        Button_net_game->setObjectName(QString::fromUtf8("Button_net_game"));
        Button_net_game->setGeometry(QRect(200, 310, 200, 80));
        Button_net_game->setMinimumSize(QSize(200, 80));
        Button_net_game->setMaximumSize(QSize(200, 80));
        Button_net_game->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        Button_exit = new QPushButton(page);
        Button_exit->setObjectName(QString::fromUtf8("Button_exit"));
        Button_exit->setGeometry(QRect(200, 440, 200, 80));
        Button_exit->setMinimumSize(QSize(200, 80));
        Button_exit->setMaximumSize(QSize(200, 80));
        Button_exit->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        Button_set = new QPushButton(page);
        Button_set->setObjectName(QString::fromUtf8("Button_set"));
        Button_set->setGeometry(QRect(10, 10, 20, 20));
        Button_set->setMinimumSize(QSize(20, 20));
        Button_set->setMaximumSize(QSize(20, 20));
        Button_set->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        LE_IP = new QLineEdit(page);
        LE_IP->setObjectName(QString::fromUtf8("LE_IP"));
        LE_IP->setGeometry(QRect(20, 60, 100, 20));
        LE_PT = new QLineEdit(page);
        LE_PT->setObjectName(QString::fromUtf8("LE_PT"));
        LE_PT->setGeometry(QRect(20, 90, 100, 20));
        Button_save_set = new QPushButton(page);
        Button_save_set->setObjectName(QString::fromUtf8("Button_save_set"));
        Button_save_set->setGeometry(QRect(20, 120, 40, 20));
        Button_save_set->setMinimumSize(QSize(40, 20));
        Button_save_set->setMaximumSize(QSize(40, 20));
        Button_save_set->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        Button_initialization = new QPushButton(page);
        Button_initialization->setObjectName(QString::fromUtf8("Button_initialization"));
        Button_initialization->setGeometry(QRect(80, 120, 40, 20));
        Button_initialization->setMinimumSize(QSize(40, 20));
        Button_initialization->setMaximumSize(QSize(40, 20));
        Button_initialization->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        label_ip = new QLabel(page);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));
        label_ip->setGeometry(QRect(0, 60, 20, 20));
        label_pt = new QLabel(page);
        label_pt->setObjectName(QString::fromUtf8("label_pt"));
        label_pt->setGeometry(QRect(0, 90, 20, 20));
        label_information = new QLabel(page);
        label_information->setObjectName(QString::fromUtf8("label_information"));
        label_information->setGeometry(QRect(0, 40, 300, 20));
        Button_update_diary = new QPushButton(page);
        Button_update_diary->setObjectName(QString::fromUtf8("Button_update_diary"));
        Button_update_diary->setGeometry(QRect(70, 10, 20, 20));
        Button_update_diary->setMinimumSize(QSize(20, 20));
        Button_update_diary->setMaximumSize(QSize(20, 20));
        Button_update_diary->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setStyleSheet(QString::fromUtf8("#page_2{border-image:url(:/new/prefix1/res/BackGround2.png)}"));
        label_create_name = new QLabel(page_2);
        label_create_name->setObjectName(QString::fromUtf8("label_create_name"));
        label_create_name->setGeometry(QRect(22, 474, 100, 50));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_create_name->setFont(font);
        tableView = new QTableView(page_2);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(21, 11, 550, 400));
        tableView->setMinimumSize(QSize(550, 400));
        tableView->setMaximumSize(QSize(600, 400));
        Button_refresh = new QPushButton(page_2);
        Button_refresh->setObjectName(QString::fromUtf8("Button_refresh"));
        Button_refresh->setGeometry(QRect(428, 418, 150, 50));
        Button_refresh->setMinimumSize(QSize(150, 50));
        Button_refresh->setMaximumSize(QSize(150, 50));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setWeight(50);
        Button_refresh->setFont(font1);
        Button_refresh->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        LineEdit1 = new QLineEdit(page_2);
        LineEdit1->setObjectName(QString::fromUtf8("LineEdit1"));
        LineEdit1->setGeometry(QRect(122, 474, 300, 50));
        LineEdit1->setMinimumSize(QSize(300, 50));
        LineEdit1->setMaximumSize(QSize(300, 50));
        QFont font2;
        font2.setPointSize(10);
        LineEdit1->setFont(font2);
        LineEdit1->setMaxLength(64);
        LineEdit1->setCursorPosition(16);
        Button_reconnect = new QPushButton(page_2);
        Button_reconnect->setObjectName(QString::fromUtf8("Button_reconnect"));
        Button_reconnect->setGeometry(QRect(22, 530, 400, 50));
        Button_reconnect->setMinimumSize(QSize(400, 50));
        Button_reconnect->setMaximumSize(QSize(400, 50));
        QFont font3;
        font3.setPointSize(19);
        font3.setBold(false);
        font3.setWeight(50);
        Button_reconnect->setFont(font3);
        Button_reconnect->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        Button_create = new QPushButton(page_2);
        Button_create->setObjectName(QString::fromUtf8("Button_create"));
        Button_create->setGeometry(QRect(428, 474, 150, 50));
        Button_create->setMinimumSize(QSize(150, 50));
        Button_create->setMaximumSize(QSize(150, 50));
        Button_create->setFont(font1);
        Button_create->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        Button_exit_net = new QPushButton(page_2);
        Button_exit_net->setObjectName(QString::fromUtf8("Button_exit_net"));
        Button_exit_net->setGeometry(QRect(428, 530, 150, 50));
        Button_exit_net->setMinimumSize(QSize(150, 50));
        Button_exit_net->setMaximumSize(QSize(150, 50));
        Button_exit_net->setFont(font1);
        Button_exit_net->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround1.png)"));
        label_connect_stat = new QLabel(page_2);
        label_connect_stat->setObjectName(QString::fromUtf8("label_connect_stat"));
        label_connect_stat->setGeometry(QRect(22, 418, 400, 50));
        label_connect_stat->setMinimumSize(QSize(400, 50));
        label_connect_stat->setMaximumSize(QSize(400, 50));
        QFont font4;
        font4.setPointSize(16);
        font4.setBold(true);
        font4.setWeight(75);
        label_connect_stat->setFont(font4);
        label_connect_stat->setAlignment(Qt::AlignCenter);
        label_people = new QLabel(page_2);
        label_people->setObjectName(QString::fromUtf8("label_people"));
        label_people->setGeometry(QRect(500, 580, 100, 20));
        stackedWidget->addWidget(page_2);

        retranslateUi(Main_Menu);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Main_Menu);
    } // setupUi

    void retranslateUi(QWidget *Main_Menu)
    {
        Main_Menu->setWindowTitle(QApplication::translate("Main_Menu", "Main_Menu", nullptr));
        Button_author->setText(QString());
        Button_local_game->setText(QApplication::translate("Main_Menu", "\346\234\254\345\234\260\346\270\270\346\210\217", nullptr));
        Button_net_game->setText(QApplication::translate("Main_Menu", "\347\275\221\347\273\234\346\270\270\346\210\217", nullptr));
        Button_exit->setText(QApplication::translate("Main_Menu", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        Button_set->setText(QString());
        LE_IP->setText(QApplication::translate("Main_Menu", "81.69.223.92", nullptr));
        LE_PT->setText(QApplication::translate("Main_Menu", "4396", nullptr));
        Button_save_set->setText(QApplication::translate("Main_Menu", "save", nullptr));
        Button_initialization->setText(QApplication::translate("Main_Menu", "\345\256\230\345\214\271", nullptr));
        label_ip->setText(QApplication::translate("Main_Menu", "IP", nullptr));
        label_pt->setText(QApplication::translate("Main_Menu", "PT", nullptr));
        label_information->setText(QApplication::translate("Main_Menu", "\350\276\223\345\205\245IP\345\234\260\345\235\200\345\222\214\347\253\257\345\217\243\345\217\267\345\220\216\347\202\271\345\207\273\344\277\235\345\255\230\350\277\233\350\241\214\347\275\221\347\273\234\346\270\270\346\210\217", nullptr));
        Button_update_diary->setText(QString());
        label_create_name->setText(QApplication::translate("Main_Menu", "\346\210\277\351\227\264\346\240\207\351\242\230\357\274\232", nullptr));
        Button_refresh->setText(QApplication::translate("Main_Menu", "\345\210\267\346\226\260\346\210\230\345\261\200", nullptr));
        LineEdit1->setText(QApplication::translate("Main_Menu", "\345\246\202\346\236\234\344\275\240\350\266\263\345\244\237\350\207\252\344\277\241\345\260\261\346\235\245\346\214\221\346\210\230\346\210\221\345\220\247\357\274\201\357\274\201\357\274\201", nullptr));
        Button_reconnect->setText(QApplication::translate("Main_Menu", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        Button_create->setText(QApplication::translate("Main_Menu", "\345\210\233\345\273\272\346\210\277\351\227\264", nullptr));
        Button_exit_net->setText(QApplication::translate("Main_Menu", "\351\200\200\345\207\272\347\275\221\347\273\234\345\257\271\346\210\230", nullptr));
        label_connect_stat->setText(QString());
        label_people->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Main_Menu: public Ui_Main_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_MENU_H
