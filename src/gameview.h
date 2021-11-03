#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QMainWindow>

namespace Ui {
class GameView;
}

class GameView : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView();

private:
    Ui::GameView *ui;
};

#endif // GAMEVIEW_H
