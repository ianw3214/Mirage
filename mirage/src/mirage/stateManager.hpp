#pragma once

#include "core.hpp"
#include "state.hpp"

// NOTE: (Ian) The state manager *may* not need to be exposed at all
namespace Mirage{
    class MIRAGE_API StateManager {
    public:
        StateManager();
        ~StateManager();

        void PushState(State * state);
        void PushOverlay(State * state);
        void PopState(State * state);
        void PopOverlay(State * state);

        void ChangeState(State * state);
    private:
        // TODO: (Ian) Use smart pointer here
        struct Impl;
        Impl * impl;
    };
}