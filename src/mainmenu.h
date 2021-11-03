#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "gameview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainMenu *ui;
    GameView *game;
};
#endif // MAINMENU_H
