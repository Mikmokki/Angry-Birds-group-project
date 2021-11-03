    #include "mainmenu.h"
#include "ui_mainmenu.h"
#include "gameview.h"

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
   game = new GameView(this);
    game->show();
}

