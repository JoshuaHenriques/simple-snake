#include "GameOver.hpp"
#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context> &context) 
    : m_context(context), m_retryBtnSel(true), 
    m_retryBtnPres(false), m_exitBtnSel(false), 
    m_exitBtnPres(false) {}

GameOver::~GameOver() {

}

void GameOver::Init() {
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString("Game Over");
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, m_gameOverTitle.getLocalBounds().height / 2);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 145.f);

    // retry button
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_retryButton.setString("Retry");
    m_retryButton.setCharacterSize(20);
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2, m_retryButton.getLocalBounds().height / 2);
    m_retryButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.f);

    // exit button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(20);
    m_exitButton.setOrigin((m_exitButton.getLocalBounds().width / 2), m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition((m_context->m_window->getSize().x / 2), m_context->m_window->getSize().y / 2 + 25.f);
}

void GameOver::ProcessInput() {
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                
                case sf::Keyboard::Up: {
                    if(!m_retryBtnSel) {
                        m_retryBtnSel = true;
                        m_exitBtnSel = false;
                    }
                    break;
                }
                case sf::Keyboard::W: {
                    if(!m_retryBtnSel) {
                        m_retryBtnSel = true;
                        m_exitBtnSel = false;
                    }
                    break;
                }
                case sf::Keyboard::Down: {
                    if(!m_exitBtnSel) {
                        m_retryBtnSel = false;
                        m_exitBtnSel = true;
                    }
                    break;
                }
                case sf::Keyboard::S: {
                    if(!m_exitBtnSel) {
                        m_retryBtnSel = false;
                        m_exitBtnSel = true;
                    }
                    break;
                }
                case sf::Keyboard::Return: {
                    m_retryBtnPres = false;
                    m_exitBtnPres = false;

                    if(m_retryBtnSel)
                    {
                        m_retryBtnPres = true;
                    } else {
                        m_exitBtnPres = true;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
}

void GameOver::Update(sf::Time deltaTime) {
    if(m_retryBtnSel) {
        m_retryButton.setFillColor(sf::Color::Yellow);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else {
        m_retryButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::Yellow);
    }

    if(m_retryBtnPres) {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if(m_exitBtnPres) {
        m_context->m_window->close();
    }
}

void GameOver::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_gameOverTitle);
    m_context->m_window->draw(m_retryButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}