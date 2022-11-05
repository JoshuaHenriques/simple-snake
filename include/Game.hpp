#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetMan.hpp"
#include "StateMan.hpp"

// uniquely identify every font and texture we have
enum AssetID {
    MAIN_FONT = 0,
    GRASS,
    FOOD,
    WALL,
    SNAKE,
    SNAKEHEADRIGHT,
    SNAKETAILLEFT,
    SNAKEBODYHORI,
};

// holds assetman, stateman, and window
// pass obj of this struct to each of the states so the state can access 
// the assets, load new states, and draw on the rendering window
struct Context {
    std::unique_ptr<Engine::AssetMan> m_assets;
    std::unique_ptr<Engine::StateMan> m_states;
    std::unique_ptr<sf::RenderWindow> m_window;

    Context() {
        m_assets = std::make_unique<Engine::AssetMan>();
        m_states = std::make_unique<Engine::StateMan>();
        m_window = std::make_unique<sf::RenderWindow>();
    }
};

class Game {
    private:
        // shared_ptr because context will be common for all the states
        std::shared_ptr<Context> m_context;
        const sf::Time TIME_PER_FRAME = sf::seconds(1.f/144.f);
    public:
        Game();
        ~Game();

        void Run();
};