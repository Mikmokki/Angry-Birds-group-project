#include "game.hpp"

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
    sf::RenderWindow window(sf::VideoMode(viewwidth, viewheight), "Angry Birds");
    window.setFramerateLimit(framerate);

    sf::View game_view(window.getDefaultView());

    MainMenu menu = MainMenu();
    sf::RectangleShape pause(sf::Vector2f(100.0f, 100.0f));
    sf::Texture pauseImage;
    pauseImage.loadFromFile("../resources/images/pause.png");
    pause.setTexture(&pauseImage);

    bool settled = true; // Is the world in a settled state (nothing is moving)
    float direction = 0; // Direction of the aiming arrow in degrees
    float power = 0;     // Power of the aiming arrow (0-100)

    while (window.isOpen())
    {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        sf::Vector2f converted_mouse_position = window.mapPixelToCoords(mouse_position);
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
                    sf::Vector2f pause_position = pause.getPosition();
                    if (converted_mouse_position.x < pause_position.x + 100 && converted_mouse_position.y < pause_position.y + 100)
                    {

                        game_view = window.getDefaultView();
                        window.setView(game_view);
                        menu.Open();
                    }
                    else if (settled && !menu.IsOpen())
                    {
                        //Shoot bird
                        float x = cos(utils::DegreesToRadians(direction)) * power / 20;
                        float y = sin(utils::DegreesToRadians(direction)) * power / 20;
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
                case sf::Keyboard::Escape:
                    game_view = window.getDefaultView();
                    window.setView(game_view);
                    menu.Open();

                default:
                    break;
                }
            case sf::Event::EventType::Resized:
                float new_res = (1.f * event.size.width) / (1.f * event.size.height);
                float game_area_res = (window.getDefaultView().getSize().x / window.getDefaultView().getSize().y);
                float k;

                sf::Vector2f window_size = window.getDefaultView().getSize();

                if (new_res > game_area_res)
                {
                    k = window_size.y / (1.f * event.size.height);
                }
                else
                {
                    k = window_size.x / (1.f * event.size.width);
                }

                game_view.setSize(k * event.size.width, k * event.size.height);
                game_view.setCenter(window.getDefaultView().getSize() * 0.5f);
                break;
            }
        }
        window.clear(sf::Color::White);
        if (menu.IsOpen())
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && converted_mouse_position.x >= 1006 && converted_mouse_position.x <= 1160 && converted_mouse_position.y >= 220 && converted_mouse_position.y <= 300)
            {
                menu.Close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && converted_mouse_position.x >= 1006 && converted_mouse_position.x <= 1136 && converted_mouse_position.y >= 520 && converted_mouse_position.y <= 580)
            {
                window.close();
            }
            menu.Draw(window);
        }
        else
        {
            window.setView(game_view);

            sf::Vector2f bird_position = utils::B2ToSfCoords(current_level_.GetBird()->GetBody()->GetPosition());
            sf::Vector2f default_center = window.getDefaultView().getCenter();

            // Used std min for the y since sfml coordinates are from top left downwards
            game_view.setCenter(std::max(bird_position.x, window.getDefaultView().getCenter().x), std::min(bird_position.y, default_center.y));

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

            pause.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
            window.draw(pause);
        }
        window.display();
    }
}
