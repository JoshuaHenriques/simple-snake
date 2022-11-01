#pragma once

#include <memory>

#include <Game.hpp>
#include <State.hpp>

class GamePlay : public Engine::State {
    private:
        std::shared_ptr<Context> m_context;
        
    public:
        GamePlay();
        ~GamePlay();
};