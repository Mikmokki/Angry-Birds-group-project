#include "game.hpp"

void Game::LoadLevel(std::string filename)
{
    std::ifstream file(filename);
    if (file.rdstate() & (file.failbit | file.badbit))
    {
        std::cerr << "Level loading failed for file: " << filename << std::endl;
    }
    else
    {
        current_level_ = Level(file);
    }
}

void Game::SaveLevel()
{
    std::ofstream file = utils::OpenFileSafe("testi");
    current_level_.SaveState(file);
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

    LevelSelector level_selector = LevelSelector();

    sf::RectangleShape pause(sf::Vector2f(100.0f, 100.0f));
    sf::Texture pauseImage;
    pauseImage.loadFromFile("../resources/images/pause.png");
    pause.setTexture(&pauseImage);

    bool settled = true;          // Is the world in a settled state (nothing is moving)
    bool has_just_settled = true; // Has the world just settled
    float direction = 0;          // Direction of the aiming arrow in degrees
    float power = 0;              // Power of the aiming arrow (0-100)

    while (window.isOpen())
    {
        sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
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
                    if (mouse_position.x < pause_position.x + 100 && mouse_position.y < pause_position.y + 100)
                    {

                        game_view = window.getDefaultView();
                        window.setView(game_view);
                        menu.Open();
                    }
                    else if (settled && !menu.IsOpen() && power != 0)
                    {
                        //Shoot bird
                        float x = cos(utils::DegreesToRadians(direction)) * power / 20;
                        float y = sin(utils::DegreesToRadians(direction)) * power / 20;
                        current_level_.ThrowBird(0, b2Vec2(x, y));
                    }
                }
                break;

            case sf::Event::EventType::Resized:
            {
                float width = static_cast<float>(event.size.width);
                float height = static_cast<float>(event.size.height);
                float aspect_ratio = width / height;
                sf::View default_view = window.getDefaultView();
                sf::Vector2f default_size = default_view.getSize();
                float default_aspect_ratio = default_size.x / default_size.y;
                float k;

                if (aspect_ratio > default_aspect_ratio)
                {
                    k = default_size.y / height;
                }
                else
                {
                    k = default_size.x / width;
                }

                game_view.setSize(k * width, k * height);
                game_view.setCenter(default_view.getCenter());
                break;
            }

            case sf::Event::EventType::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    if (settled)
                        game_view.move(0, -10);
                    break;

                case sf::Keyboard::Down:
                    if (settled)
                        game_view.move(0, 10);
                    break;

                case sf::Keyboard::Left:
                    if (settled)
                        game_view.move(-10, 0);
                    break;

                case sf::Keyboard::Right:
                    if (settled)
                        game_view.move(10, 0);
                    break;

                case sf::Keyboard::Escape:
                    game_view = window.getDefaultView();
                    window.setView(game_view);
                    menu.Open();
                    break;

                default:
                    break;
                }
                break;
            }
        }
        window.clear(sf::Color::White);
        if (menu.IsOpen())
        {
            level_selector.Open();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (mouse_position.x >= 1006 && mouse_position.x <= 1160 && mouse_position.y >= 220 && mouse_position.y <= 300)
                {
                    menu.Close();
                }
                else if (mouse_position.x >= 1006 && mouse_position.x <= 1136 && mouse_position.y >= 520 && mouse_position.y <= 580)
                {
                    window.close();
                }
            }
            menu.Draw(window);
        }
        else if (level_selector.IsOpen())
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (mouse_position.x >= 100 && mouse_position.x <= 400 && mouse_position.y >= 700 && mouse_position.y <= 780)
                {
                    LoadLevel("level1.ab");
                    std::cout << "Loaded level 1" << std::endl;
                    level_selector.Close();
                }
                else if (mouse_position.x >= 600 && mouse_position.x <= 900 && mouse_position.y >= 700 && mouse_position.y <= 780)
                {
                    LoadLevel("level2.ab");
                    std::cout << "Loaded level 2" << std::endl;
                    level_selector.Close();
                }
                else if (mouse_position.x >= 1100 && mouse_position.x <= 1500 && mouse_position.y >= 700 && mouse_position.y <= 780)
                {
                    LoadLevel("level3.ab");
                    std::cout << "Loaded level 3" << std::endl;
                    level_selector.Close();
                }
            }
            level_selector.Draw(window);
        }
        else
        {
            window.setView(game_view);

            sf::Vector2f bird_position = utils::B2ToSfCoords(current_level_.GetBird()->GetBody()->GetPosition());
            sf::Vector2f default_center = window.getDefaultView().getCenter();

            // Follow bird when thrown
            if (!settled)
            {
                // Used std min for the y since sfml coordinates are from top left downwards
                game_view.setCenter(std::max(bird_position.x, window.getDefaultView().getCenter().x), std::min(bird_position.y, default_center.y));
            }

            current_level_.GetWorld()
                ->Step(time_step, velocity_iterations, position_iterations);

            bool prev_settled = settled;
            settled = !current_level_.DrawLevel(window);
            has_just_settled = settled && !prev_settled;
            // Draw the aiming arrow
            std::tuple<float, float>
                tuple = current_level_.DrawArrow(window);
            // Update arrow direction and power
            direction = std::get<0>(tuple);
            power = std::get<1>(tuple);

            // Reset bird and view when world settles
            if (has_just_settled)
            {
                current_level_.ResetBird();
                // Update bird_position after reset
                bird_position = utils::B2ToSfCoords(current_level_.GetBird()->GetBody()->GetPosition());
                game_view.setCenter(std::max(bird_position.x, window.getDefaultView().getCenter().x), std::min(bird_position.y, default_center.y));

                // Save world to file
                //SaveLevel();
            }

            pause.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
            window.draw(pause);
        }
        window.display();
    }
}
