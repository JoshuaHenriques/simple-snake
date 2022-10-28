#pragma once

#include <stack>
#include <memory>
#include <State.hpp>

namespace Engine
{
    class StateMan {
        private:
            // state stack should only be modified at the start of the next update cycle
            std::stack<std::unique_ptr<State>> m_stateStack;
            // we don't want to push new state on the stack while the state is executing its update method
            std::unique_ptr<State> m_newState;
            bool m_add;
            bool m_replace;
            bool m_remove;
        public:
            StateMan(){};
            ~StateMan(){};

            // add to stack or replace current stack
            void Add(std::unique_ptr<State> toAdd, bool replace = false);
            // remove current state from state stack
            void PopCurrent();
            // state stack will be modified
            void ProcessStateChange();
            // to return a unique_ptr to current state object by reference 
            std::unique_ptr<State>& GetCurrent();
    };
}