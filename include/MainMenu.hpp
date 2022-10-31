#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include <State.hpp>
#include <Game.hpp>

class MainMenu : public Engine::State
{
    private:
        std::shared_ptr<Context> m_context;
        sf::Text m_gameTitle;
        sf::Text m_startButton;
        sf::Text m_exitButton;

        bool m_startBtnSel, m_startBtnPres;
        bool m_exitBtnSel, m_exitBtnPres;

    public:
        MainMenu(std::shared_ptr<Context> &context);
        ~MainMenu();

        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
};