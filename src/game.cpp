#include "game.hpp"
#include <string>

Game::Game() : window_(sf::VideoMode(viewwidth, viewheight), "Angry Birds")
{
    window_.setFramerateLimit(framerate);
}

void Game::LoadLevel(std::string filename)
{
    // current_level_ = Level("Level 1");
    std::ifstream file(filename);
    if (file.rdstate() & (file.failbit | file.badbit))
    {
        std::cerr << "Level loading failed for file: " << filename << std::endl;
    }
    else
    {
        current_level_file_name_ = filename;
        current_level_ = Level(file);
    }
}

void Game::LoadIcon()
{
    sf::Image icon;
    icon.loadFromFile("resources/images/bird.png");
    sf::Vector2u size = icon.getSize();
    window_.setIcon(size.x, size.y, icon.getPixelsPtr());
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

    sf::View game_view(window_.getDefaultView());

    MainMenu main_menu = MainMenu();

    LevelSelector level_selector = LevelSelector();

    PauseMenu pause_menu = PauseMenu();

    auto IsMenuOpen = [&]()
    {
        return main_menu.IsOpen() || level_selector.IsOpen() || pause_menu.IsOpen();
    };

    MainMenu menu = MainMenu();
    sf::Font font;
    font.loadFromFile("resources/fonts/Raleway-Medium.ttf");
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
    pauseImage.loadFromFile("resources/images/pause.png");
    pause.setTexture(&pauseImage);
    sf::RectangleShape obj_images[4];
    sf::Texture obj_textures[4];
    obj_textures[0].loadFromFile("resources/images/bird.png");
    obj_textures[1].loadFromFile("resources/images/bird2.png");
    obj_textures[2].loadFromFile("resources/images/bird3.png");
    obj_textures[3].loadFromFile("resources/images/pig.png");
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
    bool has_player_won = false;     // Did player just win the level
    float direction = 0;             // Direction of the aiming arrow in degrees
    float power = 0;                 // Power of the aiming arrow (0-100)
    while (window_.isOpen())
    {
        sf::Vector2f mouse_position = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
        sf::Event event;
        while (window_.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                window_.close();
                break;
            case sf::Event::EventType::MouseButtonPressed:

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2f pause_position = pause.getPosition();
                    if (mouse_position.x < pause_position.x + 100 && mouse_position.y < pause_position.y + 100 && !IsMenuOpen())
                    {

                        game_view = window_.getDefaultView();
                        window_.setView(game_view);
                        pause_menu.Open();
                    }
                    else if (current_level_.GetBird()->IsThrown() && !IsMenuOpen())
                    {
                        current_level_.GetBird()->NewPower();
                    }
                    else if (settled && !IsMenuOpen() && power != 0)
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
                sf::View default_view = window_.getDefaultView();
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
                    game_view = window_.getDefaultView();
                    window_.setView(game_view);
                    pause_menu.Open();
                    break;

                default:
                    break;
                }
            }
        }
        window_.clear(sf::Color::Blue);
        if (main_menu.IsOpen())
        {
            level_selector.Open();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (mouse_position.x >= 1006 && mouse_position.x <= 1160 && mouse_position.y >= 220 && mouse_position.y <= 300)
                {
                    main_menu.Close();
                }
                else if (mouse_position.x >= 1006 && mouse_position.x <= 1136 && mouse_position.y >= 520 && mouse_position.y <= 580)
                {
                    window_.close();
                }
            }
            main_menu.Draw(window_);
        }
        else if (level_selector.IsOpen())
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (mouse_position.x >= 100 && mouse_position.x <= 400 && mouse_position.y >= 400 && mouse_position.y <= 680)
                {
                    LoadLevel("resources/levels/level1.ab");
                    std::cout << "Loaded level 1" << std::endl;
                    pause_menu.Close();
                    level_selector.Close();
                }
                else if (mouse_position.x >= 600 && mouse_position.x <= 900 && mouse_position.y >= 400 && mouse_position.y <= 680)
                {
                    LoadLevel("resources/levels/level2.ab");
                    std::cout << "Loaded level 2" << std::endl;
                    pause_menu.Close();
                    level_selector.Close();
                }
                else if (mouse_position.x >= 1100 && mouse_position.x <= 1500 && mouse_position.y >= 400 && mouse_position.y <= 680)
                {
                    LoadLevel("resources/levels/level3.ab");
                    std::cout << "Loaded level 3" << std::endl;
                    pause_menu.Close();
                    level_selector.Close();
                }
            }
            level_selector.Draw(window_);
        }
        else if (pause_menu.IsOpen())
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (mouse_position.x >= 1000 && mouse_position.x <= 1300 && mouse_position.y >= 200 && mouse_position.y <= 280)
                {
                    pause_menu.Close();
                }
                else if (mouse_position.x >= 1000 && mouse_position.x <= 1400 && mouse_position.y >= 300 && mouse_position.y <= 380)
                {
                    main_menu.Open();
                }
            }
            pause_menu.Draw(window_);
        }
        else
        {
            window_.setView(game_view);
            current_level_.GetBird()->UsePower();

            sf::Vector2f bird_position = utils::B2ToSfCoords(current_level_.GetBird()->GetBody()->GetPosition());
            sf::Vector2f default_center = window_.getDefaultView().getCenter();

            // Follow bird when thrown
            if (!settled)
            {
                // Used std min for the y since sfml coordinates are from top left downwards
                game_view.setCenter(std::max(bird_position.x, window_.getDefaultView().getCenter().x), std::min(bird_position.y, default_center.y));
            }

            current_level_.GetWorld()
                ->Step(time_step, velocity_iterations, position_iterations);
            bool prev_settled = settled;

            settled = !current_level_.DrawLevel(window_);
            has_just_settled = settled && !prev_settled;
            // Draw the aiming arrow
            std::tuple<float, float> tuple = current_level_.DrawArrow(window_);
            // Update arrow direction and power
            direction = std::get<0>(tuple);
            power = std::get<1>(tuple);
            bool bird_has_been_thrown = current_level_.GetBird()->IsThrown();
            // Reset the bird and view when world settles after a throw
            if (has_just_settled && bird_has_been_thrown && current_level_.GetBird())
            {
                current_level_.ResetBird();
                // Update bird_position after reset
                bird_position = utils::B2ToSfCoords(current_level_.GetBird()->GetBody()->GetPosition());
                game_view.setCenter(std::max(bird_position.x, window_.getDefaultView().getCenter().x), std::min(bird_position.y, default_center.y));

                // Save world to file
                // SaveLevel();
            }
            score.setPosition(window_.mapPixelToCoords(sf::Vector2i(window_.getSize().x * 0.7, 0)));
            score.setString(std::string("Score: ") + std::to_string(current_level_.GetScore()));
            high_score.setPosition(window_.mapPixelToCoords(sf::Vector2i(window_.getSize().x * 0.7, 40)));
            high_score.setString(std::string("High Score: ") + std::to_string(current_level_.GetHighScore()));
            pause.setPosition(window_.mapPixelToCoords(sf::Vector2i(0, 0)));
            for (int i = 0; i < 4; i++)
            {
                if (current_level_.CountBirdTypes()[i] > 0 || i == 3)
                {
                    obj_images[i].setPosition(window_.mapPixelToCoords(sf::Vector2i(200 + i * 100, 0)));
                    obj_indicators[i].setPosition(window_.mapPixelToCoords(sf::Vector2i(250 + i * 100, 100)));
                    if (i != 3)
                        obj_indicators[i].setString(std::to_string((current_level_.CountBirdTypes()[i])));
                    else
                    {
                        obj_indicators[i].setString(std::to_string(current_level_.CountPigs()));
                    }
                    window_.draw(obj_images[i]);
                    window_.draw(obj_indicators[i]);
                }
            }

            window_.draw(score);
            window_.draw(high_score);

            window_.draw(pause);
        }

        if (current_level_.IsLevelEnded() && !has_player_won)
        {
            // Save highscore and Open endscreen
            std::list<int> high_scores = current_level_.UpdateHighScore();
            UpdateSavedHighScore(high_scores);
            has_player_won = true; // Only update highscores once
        }
        window_.display();
    }
}

void Game::UpdateSavedHighScore(std::list<int> high_scores)
{
    const int line_to_update = 2;
    // Read all lines to memory, this shouldn't be a problem since save files are quite small
    std::ifstream input(current_level_file_name_);
    std::vector<std::string> lines;
    std::string line;
    std::getline(input, line);
    while (input.good())
    {
        lines.push_back(line);
        std::getline(input, line);
    }

    input.close();

    std::stringstream high_scores_stream;

    for (auto score : high_scores)
    {
        high_scores_stream << score << ";";
    }
    // Replace second row
    lines[1] = high_scores_stream.str();

    std::ofstream output(current_level_file_name_);
    for (auto line : lines)
    {
        output << line << std::endl;
    }
    output.close();
}