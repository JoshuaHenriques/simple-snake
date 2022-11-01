// included once in any source file
#pragma once

#include <SFML/System/Time.hpp>

namespace Engine {
    class State {
        public:
            // constructor
            State(){};
            // always make destructors virtual or else destruction won't happen properly
            virtual ~State(){};

            // all initial setup of state, setup sprite, text, and positions
            virtual void Init() = 0;

            // handle events like key presses and mouse clicks
            virtual void ProcessInput() = 0;

            // react and process inputs and make changes to states like recalculating 
            // positions of sprites and texts
            // deltaTime = elapsed time since the last call this is required for making sure
            // our game runs at the same fps on every machine
            virtual void Update(sf::Time deltaTime) = 0;

            // will draw all the sprites and text of the state in the window
            virtual void Draw() = 0;

            virtual void Pause(){};
            virtual void Start(){};
    };
}