#ifndef ANGRY_BIRDS_HIGH_SCORES
#define ANGRY_BIRDS_HIGH_SCORES

#include "level.hpp"
#include "menu.hpp"
#include "utils.hpp"
#include <string>

class HighScores : public Menu
{
public:
    HighScores(Level level);
    void Draw(sf::RenderWindow &window);
    void SetLevel(Level level);

private:
    const static int list_length_ = 10;
    sf::Text high_scores_[list_length_];
    sf::Text header_;
    sf::Text back_button_;
    sf::Text level_buttons_[3];
    sf::RectangleShape rect_;
};

#endif