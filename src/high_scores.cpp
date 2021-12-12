#include "high_scores.hpp"

HighScores::HighScores(Level level) : Menu()
{
    SetLevel(level);
}

void HighScores::SetLevel(Level level)
{
    std::list<std::tuple<std::string, int>> high_scores = level.GetHighScores();
    high_scores.sort(utils::CmpHighScore);
    high_scores.reverse();
    std::vector<std::tuple<std::string, int>> hs_vector{std::begin(high_scores), std::end(high_scores)};

    for (int i = 0; i < list_length_; i++)
    {
        std::stringstream text;
        std::tuple<std::string, int> tuple = hs_vector[i];
        text << std::get<0>(tuple) << ": " << std::get<1>(tuple);
        high_scores_[i].setFont(font_);
        high_scores_[i].setFillColor(sf::Color::White);
        high_scores_[i].setString(text.str());
        high_scores_[i].setCharacterSize(40);
        sf::FloatRect rc = high_scores_[i].getLocalBounds();
        high_scores_[i].setOrigin(rc.width / 2, rc.height / 2);
        high_scores_[i].setPosition(800, 200 + i * 60);
    }

    for (int i = 0; i < 3; i++)
    {
        level_buttons_[i].setFont(font_);
        level_buttons_[i].setFillColor(sf::Color::White);
        level_buttons_[i].setString("Level " + std::to_string(i + 1));
        level_buttons_[i].setCharacterSize(60);
        level_buttons_[i].setPosition(1200, 300 + i * 100);
        level_buttons_[i].setOutlineColor(sf::Color::Black);
        if (level.GetName() == "Level " + std::to_string(i + 1))
        {
            level_buttons_[i].setOutlineThickness(3);
        }
        else
        {
            level_buttons_[i].setOutlineThickness(0);
        }
    }

    rect_.setFillColor(sf::Color(0, 0, 0, 170));
    rect_.setSize(sf::Vector2f(600, 700));
    sf::FloatRect rc = rect_.getLocalBounds();
    rect_.setOrigin(rc.width / 2, rc.height / 2);
    rect_.setPosition(800, 500);

    back_button_.setFont(font_);
    back_button_.setFillColor(sf::Color::White);
    back_button_.setString("Back");
    back_button_.setCharacterSize(80);
    back_button_.setPosition(0, 100);

    header_.setFont(font_);
    header_.setFillColor(sf::Color::White);
    header_.setString("High scores");
    header_.setCharacterSize(100);
    rc = header_.getLocalBounds();
    header_.setOrigin(rc.width / 2, rc.height / 2);
    header_.setPosition(800, 50);
}

void HighScores::Draw(sf::RenderWindow &window)
{
    window.draw(background_);
    window.draw(back_button_);
    window.draw(header_);
    window.draw(rect_);
    for (auto high_score : high_scores_)
    {
        window.draw(high_score);
    }
    for (auto level_button : level_buttons_)
    {
        window.draw(level_button);
    }
};
