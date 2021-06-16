/********************************************************************************
** Form generated from reading UI file 'wuziqi.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WUZIQI_H
#define UI_WUZIQI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wuziqi
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QPushButton *Button_back;
    QPushButton *Button_new;
    QPushButton *Button_exit;
    QLabel *label_show;
    QLabel *label_over;

    void setupUi(QWidget *wuziqi)
    {
        if (wuziqi->objectName().isEmpty())
            wuziqi->setObjectName(QString::fromUtf8("wuziqi"));
        wuziqi->resize(1000, 800);
        wuziqi->setMinimumSize(QSize(1000, 800));
        wuziqi->setMaximumSize(QSize(1000, 800));
        stackedWidget = new QStackedWidget(wuziqi);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(750, 0, 250, 800));
        stackedWidget->setMinimumSize(QSize(250, 800));
        stackedWidget->setMaximumSize(QSize(250, 800));
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        Button_back = new QPushButton(page_1);
        Button_back->setObjectName(QString::fromUtf8("Button_back"));
        Button_back->setGeometry(QRect(50, 420, 150, 75));
        QFont font;
        font.setPointSize(17);
        Button_back->setFont(font);
        Button_new = new QPushButton(page_1);
        Button_new->setObjectName(QString::fromUtf8("Button_new"));
        Button_new->setGeometry(QRect(50, 520, 150, 75));
        Button_new->setFont(font);
        Button_exit = new QPushButton(page_1);
        Button_exit->setObjectName(QString::fromUtf8("Button_exit"));
        Button_exit->setGeometry(QRect(50, 620, 150, 75));
        Button_exit->setFont(font);
        label_show = new QLabel(page_1);
        label_show->setObjectName(QString::fromUtf8("label_show"));
        label_show->setGeometry(QRect(75, 100, 100, 100));
        stackedWidget->addWidget(page_1);
        label_over = new QLabel(wuziqi);
        label_over->setObjectName(QString::fromUtf8("label_over"));
        label_over->setGeometry(QRect(0, 0, 800, 800));
        QFont font1;
        font1.setPointSize(64);
        font1.setBold(true);
        font1.setWeight(75);
        label_over->setFont(font1);
        label_over->setLayoutDirection(Qt::LeftToRight);
        label_over->setAlignment(Qt::AlignCenter);

        retranslateUi(wuziqi);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(wuziqi);
    } // setupUi

    void retranslateUi(QWidget *wuziqi)
    {
        wuziqi->setWindowTitle(QApplication::translate("wuziqi", "Form", nullptr));
        Button_back->setText(QApplication::translate("wuziqi", "\346\202\224\346\243\213", nullptr));
        Button_new->setText(QApplication::translate("wuziqi", "\346\226\260\346\270\270\346\210\217", nullptr));
        Button_exit->setText(QApplication::translate("wuziqi", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        label_show->setText(QString());
        label_over->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class wuziqi: public Ui_wuziqi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WUZIQI_H
