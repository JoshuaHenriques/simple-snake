#include <memory>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <SFML/Window/Event.hpp>

#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

GamePlay::GamePlay(std::shared_ptr<Context>& context) : m_context(context), 
m_snakeDirection({16.f, 0.f}),
m_elapsedTime(sf::Time::Zero), m_score(0),
m_isPaused(false) {
    srand(time(nullptr));
}

GamePlay::~GamePlay() {}

void GamePlay::Init() {
    m_context->m_assets->AddTexture(GRASS, "assets/textures/grass.png", true);
    m_context->m_assets->AddTexture(WALL, "assets/textures/wall.png", true);
    m_context->m_assets->AddTexture(FOOD, "assets/textures/food.png", false);
    m_context->m_assets->AddTexture(SNAKE, "assets/textures/snake.png", false);
    m_context->m_assets->AddTexture(SNAKEHEADRIGHT, "assets/textures/head-right.png", false);
    m_context->m_assets->AddTexture(SNAKEBODYHORI, "assets/textures/body-hori.png", false);
    m_context->m_assets->AddTexture(SNAKETAILLEFT, "assets/textures/tail-left.png", false);

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    for(auto& wall : m_walls) {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }

    m_walls[0].setTextureRect({0, 0, m_context->m_window->getSize().x, 16});
    m_walls[1].setTextureRect({0, 0, m_context->m_window->getSize().x, 16});
    m_walls[1].setPosition(0, m_context->m_window->getSize().y - 16);

    m_walls[2].setTextureRect({0, 0, 16, m_context->m_window->getSize().y});
    m_walls[3].setTextureRect({0, 0, 16, m_context->m_window->getSize().y});
    m_walls[3].setPosition(m_context->m_window->getSize().x - 16, 0);

    m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);

    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score: " + std::to_string(m_score));
    m_scoreText.setCharacterSize(15);
    
    // std::cout << "m_food height:" << m_food.getTextureRect().height;
    // std::cout << "m_food width:" << m_food.getTextureRect().width;

    m_snake.Init(m_context->m_assets->GetTexture(SNAKEHEADRIGHT), m_context->m_assets->GetTexture(SNAKEBODYHORI), m_context->m_assets->GetTexture(SNAKETAILLEFT), m_context->m_assets->GetTexture(SNAKE));
}

void GamePlay::ProcessInput() {
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            sf::Vector2f newDirection = m_snakeDirection;
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    newDirection = {0.f, -16.f};
                    break;
                case sf::Keyboard::W:
                    newDirection = {0.f, -16.f};
                    break;
                case sf::Keyboard::Down:
                    newDirection = {0.f, 16.f};
                    break;
                case sf::Keyboard::S:
                    newDirection = {0.f, 16.f};
                    break;
                case sf::Keyboard::Left:
                    newDirection = {-16.f, 0.f};
                    break;
                case sf::Keyboard::A:
                    newDirection = {-16.f, 0.f};
                    break;
                case sf::Keyboard::Right:
                    newDirection = {16.f, 0.f};
                    break;
                case sf::Keyboard::D:
                    newDirection = {16.f, 0.f};
                    break;
                case sf::Keyboard::Escape:
                    m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
                    break;
                default:
                    break;
            }

            if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) || 
            std::abs(m_snakeDirection.y) != std::abs(newDirection.y)) {
                m_snakeDirection = newDirection;
            }

        }
    }
}

void GamePlay::Update(sf::Time deltaTime) {
    if (!m_isPaused) {
        m_elapsedTime += deltaTime;
        if(m_elapsedTime.asSeconds() > 0.1) {

            for(auto& wall : m_walls) {
                if (m_snake.IsOn(wall)) {
                    m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
                }
            }
            // can use random to move the food
            // todo: fix snake eating food when not directly on it (visual issue?, food respawn?)
            // possible solution, make sure x, y are divisible by 16
            if(m_snake.IsOn(m_food)) {
                        m_snake.Grow(m_snakeDirection);
                        int x = 0, y = 0;

                        // x = rand() % m_context->m_window->getSize().x;
                        // y = rand() % m_context->m_window->getSize().y;

                        do {
                            // use std::clamp() to make sure the food doesn't get spawned in the walls
                            // x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, rand() % m_context->m_window->getSize().x - 2*16);
                            // y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 16, rand() % m_context->m_window->getSize().y - 2*16);
                            x = rand() % m_context->m_window->getSize().x - 2*16;
                            y = rand() % m_context->m_window->getSize().y - 2*16;
                        } while ((x % 16 != 0 || y % 16 != 0) || (x < 16 || y < 16));

                        std::cout << "m_food x: " << x << std::endl;
                        std::cout << "m_food y: " << y << std::endl;
                        m_food.setPosition(x, y);

                        m_score += 1;
                        m_scoreText.setString("Score: " + std::to_string(m_score));
                    }
            else {
                    m_snake.Move(m_snakeDirection);
                }

            if(m_snake.IsSelfIntersecting()) m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
            m_elapsedTime = sf::Time::Zero;
        }
    }
}

void GamePlay::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);

    for(auto& wall : m_walls) {
        m_context->m_window->draw(wall);
    }
    m_context->m_window->draw(m_food);
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(m_scoreText);
    m_context->m_window->display();
}

void GamePlay::Pause() {
    m_isPaused = true;
}

void GamePlay::Start() {
    m_isPaused = false;
}