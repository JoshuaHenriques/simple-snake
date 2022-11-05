#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include <State.hpp>
#include <Game.hpp>

class GameOver : public Engine::State {
    private:
        std::shared_ptr<Context> m_context;
        sf::Text m_gameOverTitle;
        sf::Text m_retryButton;
        sf::Text m_exitButton;

        bool m_retryBtnSel, m_retryBtnPres;
        bool m_exitBtnSel, m_exitBtnPres;

    public:
        GameOver(std::shared_ptr<Context> &context);
        ~GameOver();

        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
};