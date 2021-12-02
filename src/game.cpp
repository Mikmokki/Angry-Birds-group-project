#include "game.hpp"
#include <SFML/Graphics.hpp>

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

            case sf::Event::EventType::KeyPressed:
                // std::cout << event.KeyPressed << std::endl;
                if (event.KeyPressed == 5)
                {
                    current_level_.CycleHover();
                }
                break;

            case sf::Event::EventType::MouseButtonPressed:
                current_level_.AddObject(window);
                break;

            case sf::Event::MouseWheelScrolled:
                current_level_.RotateHover(event.mouseWheelScroll.delta);
                break;

            default:
                break;
            }
        }

        current_level_.GetWorld()->Step(time_step, velocity_iterations, position_iterations);
        bool settled = !current_level_.RenderLevel(window);
        if (settled)
        {
            //current_level_.ThrowBird(0, b2Vec2(5.0f, 5.0f));
        }
    }
}