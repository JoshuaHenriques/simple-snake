#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>

#include "Game.hpp"

Game::Game() : m_context(std::make_shared<Context>())
{
    // sf::Style::Close prevents maximizing the window
    m_context->m_window->create(sf::VideoMode(200, 200), "SFML works!", sf::Style::Close);
    // Todo:
    // add first state to m_states
}

Game::~Game() {

}

void Game::Run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // limit to 60fps
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        // clock.restart() returns the time elapsed from zero
        timeSinceLastFrame += clock.restart();

        // consisten update cycle
        while(timeSinceLastFrame > TIME_PER_FRAME) {
            timeSinceLastFrame -= TIME_PER_FRAME;

            // Todo:
            // state change happens before the update cycle begins
            // m_context->m_states->ProcessStateChange();
            // // this will allow the state to process input
            // m_context->m_states->GetCurrent()->ProcessInput();
            // // the state will do all required calculations and updates
            // m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
            // // the sprites and text are all drawn on the render window
            // m_context->m_states->GetCurrent()->Draw();

            sf::Event event;
            while (m_context->m_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_context->m_window->close();
            }

            m_context->m_window->clear();
            m_context->m_window->draw(shape);
            m_context->m_window->display();
        }
    }
}