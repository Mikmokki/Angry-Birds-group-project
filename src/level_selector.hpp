#ifndef ANGRY_BIRDS_LEVEL_SELECTOR
#define ANGRY_BIRDS_LEVEL_SELECTOR

#include <SFML/Graphics.hpp>
#include <string>
#include "converters.hpp"

class LevelSelector
{
public:
    LevelSelector();
    void Draw(sf::RenderWindow &window);
    bool IsOpen();
    ~LevelSelector();
    void Close();
    void Open();

private:
    bool open_;
    sf::Font font_;
    const static int level_amount_ = 3;
    sf::RectangleShape background_;
    sf::Texture background_image_;
    sf::Text level_names_[level_amount_];
};

#endif
