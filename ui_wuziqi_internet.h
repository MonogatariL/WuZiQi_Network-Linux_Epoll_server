/********************************************************************************
** Form generated from reading UI file 'wuziqi_internet.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WUZIQI_INTERNET_H
#define UI_WUZIQI_INTERNET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wuziqi_internet
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *Button_prepare;
    QPushButton *Button_exit_room;
    QLabel *label_opponent;
    QLabel *label_prepare_;
    QLabel *label_ip;
    QLabel *label_fd;
    QWidget *page_2;
    QTextEdit *LE_recv;
    QLineEdit *LE_send;
    QPushButton *Button_back;
    QPushButton *Button_exiting;
    QLabel *Label_your_color;
    QPushButton *Button_send;
    QLabel *label_msg;
    QPushButton *Button_back_surrender;
    QLabel *Title;
    QLabel *label_prepare;
    QPushButton *Button_black;
    QPushButton *Button_white;
    QLabel *label_victory;
    QPushButton *Button_agreen;
    QPushButton *Button_refuse;
    QLabel *label_wait_answer;
    QLabel *label_anwser;

    void setupUi(QWidget *wuziqi_internet)
    {
        if (wuziqi_internet->objectName().isEmpty())
            wuziqi_internet->setObjectName(QString::fromUtf8("wuziqi_internet"));
        wuziqi_internet->resize(1000, 800);
        stackedWidget = new QStackedWidget(wuziqi_internet);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(750, 0, 250, 800));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        Button_prepare = new QPushButton(page);
        Button_prepare->setObjectName(QString::fromUtf8("Button_prepare"));
        Button_prepare->setGeometry(QRect(55, 480, 140, 75));
        Button_prepare->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround2.png)"));
        Button_exit_room = new QPushButton(page);
        Button_exit_room->setObjectName(QString::fromUtf8("Button_exit_room"));
        Button_exit_room->setGeometry(QRect(55, 600, 140, 75));
        Button_exit_room->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround2.png)"));
        label_opponent = new QLabel(page);
        label_opponent->setObjectName(QString::fromUtf8("label_opponent"));
        label_opponent->setGeometry(QRect(55, 30, 150, 150));
        label_prepare_ = new QLabel(page);
        label_prepare_->setObjectName(QString::fromUtf8("label_prepare_"));
        label_prepare_->setGeometry(QRect(55, 220, 150, 30));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        label_prepare_->setFont(font);
        label_prepare_->setAlignment(Qt::AlignCenter);
        label_ip = new QLabel(page);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));
        label_ip->setGeometry(QRect(0, 270, 250, 30));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setItalic(true);
        font1.setWeight(50);
        label_ip->setFont(font1);
        label_ip->setAlignment(Qt::AlignCenter);
        label_fd = new QLabel(page);
        label_fd->setObjectName(QString::fromUtf8("label_fd"));
        label_fd->setGeometry(QRect(55, 320, 150, 30));
        label_fd->setFont(font1);
        label_fd->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        LE_recv = new QTextEdit(page_2);
        LE_recv->setObjectName(QString::fromUtf8("LE_recv"));
        LE_recv->setGeometry(QRect(35, 20, 180, 250));
        LE_recv->setReadOnly(true);
        LE_send = new QLineEdit(page_2);
        LE_send->setObjectName(QString::fromUtf8("LE_send"));
        LE_send->setGeometry(QRect(35, 280, 150, 30));
        Button_back = new QPushButton(page_2);
        Button_back->setObjectName(QString::fromUtf8("Button_back"));
        Button_back->setGeometry(QRect(35, 500, 180, 80));
        Button_back->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround2.png)"));
        Button_exiting = new QPushButton(page_2);
        Button_exiting->setObjectName(QString::fromUtf8("Button_exiting"));
        Button_exiting->setGeometry(QRect(35, 700, 180, 80));
        Button_exiting->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround2.png)"));
        Label_your_color = new QLabel(page_2);
        Label_your_color->setObjectName(QString::fromUtf8("Label_your_color"));
        Label_your_color->setGeometry(QRect(75, 320, 100, 100));
        Button_send = new QPushButton(page_2);
        Button_send->setObjectName(QString::fromUtf8("Button_send"));
        Button_send->setGeometry(QRect(185, 280, 30, 30));
        Button_send->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround2.png)"));
        label_msg = new QLabel(page_2);
        label_msg->setObjectName(QString::fromUtf8("label_msg"));
        label_msg->setGeometry(QRect(40, 430, 180, 50));
        QFont font2;
        font2.setPointSize(14);
        label_msg->setFont(font2);
        label_msg->setAlignment(Qt::AlignCenter);
        Button_back_surrender = new QPushButton(page_2);
        Button_back_surrender->setObjectName(QString::fromUtf8("Button_back_surrender"));
        Button_back_surrender->setGeometry(QRect(35, 600, 180, 80));
        Button_back_surrender->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround2.png)"));
        stackedWidget->addWidget(page_2);
        Title = new QLabel(wuziqi_internet);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setGeometry(QRect(0, 0, 500, 50));
        QFont font3;
        font3.setPointSize(11);
        Title->setFont(font3);
        Title->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_prepare = new QLabel(wuziqi_internet);
        label_prepare->setObjectName(QString::fromUtf8("label_prepare"));
        label_prepare->setGeometry(QRect(0, 0, 800, 800));
        QFont font4;
        font4.setPointSize(64);
        font4.setItalic(true);
        label_prepare->setFont(font4);
        label_prepare->setAlignment(Qt::AlignCenter);
        Button_black = new QPushButton(wuziqi_internet);
        Button_black->setObjectName(QString::fromUtf8("Button_black"));
        Button_black->setGeometry(QRect(300, 60, 200, 200));
        QFont font5;
        font5.setPointSize(32);
        font5.setBold(true);
        font5.setWeight(75);
        Button_black->setFont(font5);
        Button_black->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround2.png)"));
        Button_white = new QPushButton(wuziqi_internet);
        Button_white->setObjectName(QString::fromUtf8("Button_white"));
        Button_white->setGeometry(QRect(300, 540, 200, 200));
        Button_white->setFont(font5);
        Button_white->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround2.png)"));
        label_victory = new QLabel(wuziqi_internet);
        label_victory->setObjectName(QString::fromUtf8("label_victory"));
        label_victory->setGeometry(QRect(0, 0, 800, 200));
        QFont font6;
        font6.setPointSize(64);
        font6.setItalic(false);
        label_victory->setFont(font6);
        label_victory->setAlignment(Qt::AlignCenter);
        Button_agreen = new QPushButton(wuziqi_internet);
        Button_agreen->setObjectName(QString::fromUtf8("Button_agreen"));
        Button_agreen->setGeometry(QRect(100, 300, 200, 150));
        QFont font7;
        font7.setPointSize(36);
        font7.setBold(false);
        font7.setWeight(50);
        Button_agreen->setFont(font7);
        Button_agreen->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround2.png)"));
        Button_refuse = new QPushButton(wuziqi_internet);
        Button_refuse->setObjectName(QString::fromUtf8("Button_refuse"));
        Button_refuse->setGeometry(QRect(500, 300, 200, 150));
        Button_refuse->setFont(font7);
        Button_refuse->setStyleSheet(QString::fromUtf8("background-image:url(:/new/prefix1/res/BackGround2.png)"));
        label_wait_answer = new QLabel(wuziqi_internet);
        label_wait_answer->setObjectName(QString::fromUtf8("label_wait_answer"));
        label_wait_answer->setGeometry(QRect(0, 0, 800, 800));
        QFont font8;
        font8.setPointSize(44);
        font8.setItalic(false);
        label_wait_answer->setFont(font8);
        label_wait_answer->setAlignment(Qt::AlignCenter);
        label_anwser = new QLabel(wuziqi_internet);
        label_anwser->setObjectName(QString::fromUtf8("label_anwser"));
        label_anwser->setGeometry(QRect(0, 0, 800, 200));
        label_anwser->setFont(font6);
        label_anwser->setAlignment(Qt::AlignCenter);

        retranslateUi(wuziqi_internet);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(wuziqi_internet);
    } // setupUi

    void retranslateUi(QWidget *wuziqi_internet)
    {
        wuziqi_internet->setWindowTitle(QApplication::translate("wuziqi_internet", "Form", nullptr));
        Button_prepare->setText(QApplication::translate("wuziqi_internet", "\345\207\206\345\244\207", nullptr));
        Button_exit_room->setText(QApplication::translate("wuziqi_internet", "\351\200\200\345\207\272\346\210\277\351\227\264", nullptr));
        label_opponent->setText(QString());
        label_prepare_->setText(QApplication::translate("wuziqi_internet", "\346\234\252\345\207\206\345\244\207", nullptr));
        label_ip->setText(QApplication::translate("wuziqi_internet", "IP: ", nullptr));
        label_fd->setText(QApplication::translate("wuziqi_internet", "FD: ", nullptr));
        Button_back->setText(QApplication::translate("wuziqi_internet", "\346\202\224\346\243\213", nullptr));
        Button_exiting->setText(QApplication::translate("wuziqi_internet", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        Label_your_color->setText(QString());
        Button_send->setText(QString());
        label_msg->setText(QString());
        Button_back_surrender->setText(QApplication::translate("wuziqi_internet", "\350\256\244\350\276\223", nullptr));
        Title->setText(QApplication::translate("wuziqi_internet", "\346\210\277\351\227\264\345\220\215", nullptr));
        label_prepare->setText(QApplication::translate("wuziqi_internet", "Please_Prepare...", nullptr));
        Button_black->setText(QApplication::translate("wuziqi_internet", "\345\205\210\346\211\213", nullptr));
        Button_white->setText(QApplication::translate("wuziqi_internet", "\345\220\216\346\211\213", nullptr));
        label_victory->setText(QApplication::translate("wuziqi_internet", "\351\273\221\346\243\213\350\203\234\345\210\251", nullptr));
        Button_agreen->setText(QApplication::translate("wuziqi_internet", "\345\220\214\346\204\217", nullptr));
        Button_refuse->setText(QApplication::translate("wuziqi_internet", "\346\213\222\347\273\235", nullptr));
        label_wait_answer->setText(QApplication::translate("wuziqi_internet", "\347\255\211\345\276\205\345\257\271\346\226\271\345\223\215\345\272\224\350\257\267\346\261\202", nullptr));
        label_anwser->setText(QApplication::translate("wuziqi_internet", "ADSFASDFA", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wuziqi_internet: public Ui_wuziqi_internet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WUZIQI_INTERNET_H
