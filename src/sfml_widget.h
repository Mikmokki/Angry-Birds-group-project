#ifndef SFML_WIDGET
#define SFML_WIDGET

#include <SFML/Graphics.hpp>
#include <qwidget.h>
#include <qtimer.h>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
public :

    QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);
    QSFMLCanvas(QWidget* Parent);

    virtual ~QSFMLCanvas();

private :

    virtual void OnInit();

    virtual void OnUpdate();

    virtual QPaintEngine* paintEngine() const;

    virtual void showEvent(QShowEvent*);

    virtual void paintEvent(QPaintEvent*);

    QTimer myTimer;
    bool   myInitialized;
};

#endif // SFML_WIDGET
