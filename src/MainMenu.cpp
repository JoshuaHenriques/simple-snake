#include <iostream>

#include <SFML/Window/Event.hpp>

#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<Context> &context) 
    : m_context(context), m_startBtnSel(true), 
    m_startBtnPres(false), m_exitBtnSel(false), 
    m_exitBtnPres(false) {

}

MainMenu::~MainMenu() {

}

void MainMenu::Init() {
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Roboto-Regular.ttf");
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString("Snake");
    // sets the origin of the text rectangle from top left to the center
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
    // to center the text
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 125.f);

    // start button
    m_startButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_startButton.setString("Start");
    m_startButton.setOrigin(m_startButton.getLocalBounds().width / 2, m_startButton.getLocalBounds().height / 2);
    m_startButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.f);
    m_startButton.setCharacterSize(20);

    // exit button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin((m_exitButton.getLocalBounds().width / 2), m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition((m_context->m_window->getSize().x / 2), m_context->m_window->getSize().y / 2 + 25.f);
    m_exitButton.setCharacterSize(20);
}

void MainMenu::ProcessInput() {
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up: {
                    if(!m_startBtnSel) {
                        m_startBtnSel = true;
                        m_exitBtnSel = false;
                    }
                    break;
                }
                case sf::Keyboard::Down: {
                    if(!m_exitBtnSel) {
                        m_startBtnSel = false;
                        m_exitBtnSel = true;
                    }
                    break;
                }
                case sf::Keyboard::Return: {
                    m_startBtnPres = false;
                    m_exitBtnPres = false;

                    if(m_startBtnSel)
                    {
                        m_startBtnPres = true;
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

void MainMenu::Update(sf::Time deltaTime) {
    if(m_startBtnSel) {
        m_startButton.setFillColor(sf::Color::Yellow);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else {
        m_startButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::Yellow);
    }

    if(m_startBtnPres) {
        // todo:
        // go to play state
    }
    else if(m_exitBtnPres) {
        m_context->m_window->close();
    }
}

void MainMenu::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_startButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}