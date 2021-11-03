/********************************************************************************
** Form generated from reading UI file 'gameview.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEVIEW_H
#define UI_GAMEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameView
{
public:
    QWidget *centralwidget;
    QToolButton *toolButton;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GameView)
    {
        if (GameView->objectName().isEmpty())
            GameView->setObjectName(QString::fromUtf8("GameView"));
        GameView->resize(764, 600);
        centralwidget = new QWidget(GameView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        toolButton = new QToolButton(centralwidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(10, 10, 42, 19));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(660, 10, 90, 26));
        label->setMaximumSize(QSize(100, 100));
        GameView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GameView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 764, 21));
        GameView->setMenuBar(menubar);
        statusbar = new QStatusBar(GameView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GameView->setStatusBar(statusbar);

        retranslateUi(GameView);

        QMetaObject::connectSlotsByName(GameView);
    } // setupUi

    void retranslateUi(QMainWindow *GameView)
    {
        GameView->setWindowTitle(QCoreApplication::translate("GameView", "MainWindow", nullptr));
        toolButton->setText(QCoreApplication::translate("GameView", "Pause", nullptr));
        label->setText(QCoreApplication::translate("GameView", "SCORE: 123\n"
"HIGHSCORE: 1234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameView: public Ui_GameView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEVIEW_H
