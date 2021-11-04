#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "gameview.h"
#include "mainmenu.h"
#include "mycanvas.h"
#include "sfml_widget.h"

#include <QFrame>
#include <QApplication>
MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}


MainMenu::~MainMenu()
{
    delete ui;
}


void MainMenu::on_pushButton_clicked()
{
    this->hide();

    /*
    QFrame* MainFrame = new QFrame;
    MainFrame->setWindowTitle("Qt SFML");
    MainFrame->resize(400, 400);
    MainFrame->show();
    MyCanvas* SFMLView = new MyCanvas(MainFrame, QPoint(20, 20), QSize(360, 360));
    SFMLView->show();
    */
    game = new GameView(this);
    game->show();
}

