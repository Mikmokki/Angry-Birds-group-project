#include "game.hpp"
#include "math.h"

void Game::LoadLevel(std::string filename)
{
    b2Vec2 bsp(3.0f, 3.0f);
    current_level_ = Level("Example", bsp);
}

void Game::Start()
{
    if (current_level_.GetName() == "")
    {
        std::cout << "You need to load a level before starting the game" << std::endl;
    }
    sf::RenderWindow window(sf::VideoMode(viewwidth, viewheight), "Angry Birds", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(framerate);

    sf::View game_view(window.getDefaultView());

    bool settled = true;
    float direction = 0;
    float power = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                window.close();
                break;
            case sf::Event::EventType::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (settled)
                    {
                        //Shoot bird
                        float x = cos(direction * (M_PI / 180)) * power / 20; // use global converter
                        float y = sin(direction * (M_PI / 180)) * power / 20;
                        current_level_.ThrowBird(0, b2Vec2(x, y));
                    }
                }
                break;

            case sf::Event::EventType::KeyPressed:

                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    game_view.move(0, -10);
                    break;

                case sf::Keyboard::Down:
                    game_view.move(0, 10);
                    break;

                case sf::Keyboard::Left:
                    game_view.move(-10, 0);
                    break;

                case sf::Keyboard::Right:
                    game_view.move(10, 0);
                    break;

                default:
                    break;
                }
            default:
                break;
            }
        }

        window.clear(sf::Color::White);
        window.setView(game_view);
        current_level_.GetWorld()->Step(time_step, velocity_iterations, position_iterations);
        settled = !current_level_.DrawLevel(window);
        // Draw the aiming arrow
        std::tuple<float, float> tuple = current_level_.DrawArrow(window);
        direction = std::get<0>(tuple);
        power = std::get<1>(tuple);
        if (settled)
        {
            current_level_.ResetBird();
        }
        window.display();
    }
}
