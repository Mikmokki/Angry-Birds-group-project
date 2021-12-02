#include "game.hpp"
#include "math.h"

#define M_PI 3.14159265358979323846

sf::Vector2f toSFVector_(b2Vec2 original)
{
    return sf::Vector2f(original.x * scale, 800 - (original.y * scale));
}

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

    bool settled = true; // Is the world in a settled state (nothing is moving)
    float direction = 0; // Direction of the aiming arrow in degrees
    float power = 0;     // Power of the aiming arrow (0-100)

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

        sf::Vector2f bird_position = toSFVector_(current_level_.GetBird()->GetBody()->GetPosition());
        sf::Vector2f default_center = window.getDefaultView().getCenter();

        // Used std min for the y since sfml coordinates are from top left downwards
        game_view.setCenter(bird_position.x, std::min(bird_position.y, default_center.y));

        current_level_.GetWorld()
            ->Step(time_step, velocity_iterations, position_iterations);
        settled = !current_level_.DrawLevel(window);
        // Draw the aiming arrow
        std::tuple<float, float> tuple = current_level_.DrawArrow(window);
        // Update arrow direction and power
        direction = std::get<0>(tuple);
        power = std::get<1>(tuple);
        if (settled)
        {
            current_level_.ResetBird();
        }
        window.display();
    }
}
