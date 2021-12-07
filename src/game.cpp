#include "game.hpp"
#include <string>
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
    sf::Font font;
    font.loadFromFile("../resources/fonts/Raleway-Medium.ttf");
    sf::Text score;
    score.setFont(font);
    score.setFillColor(sf::Color::White);
    score.setString(std::string("Score: ") + std::to_string(current_level_.GetScore()));
    score.setCharacterSize(40);
    sf::Text high_score;
    high_score.setFont(font);
    high_score.setFillColor(sf::Color::White);
    high_score.setString(std::string("High Score: ") + std::to_string(current_level_.GetHighScore()));
    high_score.setCharacterSize(40);
    sf::RectangleShape pause(sf::Vector2f(100.0f, 100.0f));
    sf::Texture pauseImage;
    pauseImage.loadFromFile("../resources/images/pause.png");
    pause.setTexture(&pauseImage);
    sf::RectangleShape obj_images[4];
    sf::Texture obj_textures[4];
    obj_textures[0].loadFromFile("../resources/images/bird.png");
    obj_textures[1].loadFromFile("../resources/images/bird2.png");
    obj_textures[2].loadFromFile("../resources/images/bird3.png");
    obj_textures[3].loadFromFile("../resources/images/pig.png");
    sf::Text obj_indicators[4];
    for (int i = 0; i < 4; i++)
    {
        obj_images[i].setSize(sf::Vector2f(100.0f, 100.0f));
        obj_images[i].setTexture(&obj_textures[i]);
        obj_indicators[i].setFont(font);
        obj_indicators[i].setFillColor(sf::Color::White);
        obj_indicators[i].setCharacterSize(20);
    }

    bool settled = false;            // Is the world in a settled state (nothing is moving)
    bool has_just_settled = settled; // Has the world settled on the previous simulation step
    float direction = 0;             // Direction of the aiming arrow in degrees
    float power = 0;                 // Power of the aiming arrow (0-100)
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
                    else if (current_level_.GetBird()->IsThrown())
                    {
                        current_level_.GetBird()->NewPower();
                    }
                    else if (settled && !menu.IsOpen() && power != 0)
                    {
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
            }
        }
        window.clear(sf::Color::Blue);
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
            current_level_.GetBird()->UsePower();

            sf::Vector2f bird_position = utils::B2ToSfCoords(current_level_.GetBird()->GetBody()->GetPosition());
            sf::Vector2f default_center = window.getDefaultView().getCenter();

            // Reset view when world settles
            if (!settled || has_just_settled)
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
            std::tuple<float, float> tuple = current_level_.DrawArrow(window);
            // Update arrow direction and power
            direction = std::get<0>(tuple);
            power = std::get<1>(tuple);
            bool bird_has_been_thrown = current_level_.GetBird()->IsThrown();
            if (has_just_settled && bird_has_been_thrown && current_level_.GetBird())
            {
                current_level_.ResetBird();
            }
            score.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x * 0.7, 0)));
            score.setString(std::string("Score: ") + std::to_string(current_level_.GetScore()));
            high_score.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x * 0.7, 40)));
            high_score.setString(std::string("High Score: ") + std::to_string(current_level_.GetScore()));
            pause.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
            if (std::get<0>(current_level_.CountBirdTypes()) > 0)
            {
                obj_images[0].setPosition(window.mapPixelToCoords(sf::Vector2i(200, 0)));
                obj_indicators[0].setPosition(window.mapPixelToCoords(sf::Vector2i(250, 100)));
                obj_indicators[0].setString(std::to_string(std::get<0>(current_level_.CountBirdTypes())));
                window.draw(obj_images[0]);
                window.draw(obj_indicators[0]);
            }
            if (std::get<1>(current_level_.CountBirdTypes()) > 0)
            {
                obj_images[1].setPosition(window.mapPixelToCoords(sf::Vector2i(300, 0)));
                obj_indicators[1].setPosition(window.mapPixelToCoords(sf::Vector2i(350, 100)));
                obj_indicators[1].setString(std::to_string(std::get<1>(current_level_.CountBirdTypes())));
                window.draw(obj_images[1]);
                window.draw(obj_indicators[1]);
            }
            if (std::get<2>(current_level_.CountBirdTypes()) > 0)
            {
                obj_images[2].setPosition(window.mapPixelToCoords(sf::Vector2i(400, 0)));
                obj_indicators[2].setPosition(window.mapPixelToCoords(sf::Vector2i(450, 100)));
                obj_indicators[2].setString(std::to_string(std::get<2>(current_level_.CountBirdTypes())));
                window.draw(obj_images[2]);
                window.draw(obj_indicators[2]);
            }
            if (current_level_.CountPigs() > 0)
            {
                obj_images[3].setPosition(window.mapPixelToCoords(sf::Vector2i(500, 0)));
                obj_indicators[3].setPosition(window.mapPixelToCoords(sf::Vector2i(550, 100)));
                obj_indicators[3].setString(std::to_string(current_level_.CountPigs()));
                window.draw(obj_images[3]);
                window.draw(obj_indicators[3]);
            }
            window.draw(score);
            window.draw(high_score);

            window.draw(pause);
        }
        window.display();
    }
}
