#include "gameview.h"
#include "ui_gameview.h"
#include "mainmenu.h"
#include "mycanvas.h"
#include "sfml_widget.h"

#include <QFrame>
#include <QApplication>
#include <SFML/Graphics.hpp>

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
