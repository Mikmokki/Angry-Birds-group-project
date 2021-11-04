#ifndef MY_CANVAS
#define MY_CANVAS

#include "sfml_widget.h"

class MyCanvas : public QSFMLCanvas
{
public :

    MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size) {}
    ~MyCanvas() {};

private :

    void OnInit()
    {
        // Load the image
        // myImage.loadFromFile("datas/qt/sfml.png");

        // Setup the sprite
        mySprite.setColor(sf::Color(0,128,0));
        mySprite.setScale(100, 100);
        //mySprite.SetCenter(mySprite.GetSize() / 2.f);
    }

    void OnUpdate()
    {
        // Clear screen
        clear(sf::Color(0, 255, 0));

        // Rotate the sprite   GetFrameTime()
        mySprite.rotate(100.f);
        // Draw it
        draw(mySprite);
    }

    sf::Image  myImage;
    sf::Sprite mySprite;
};

#endif  // MY_CANVAS
