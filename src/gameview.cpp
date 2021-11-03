#include "gameview.h"
#include "ui_gameview.h"

GameView::GameView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameView)
{
    ui->setupUi(this);
}

GameView::~GameView()
{
    delete ui;
}
