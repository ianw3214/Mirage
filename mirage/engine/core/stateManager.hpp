#pragma once

#include "state.hpp"
#include "util/util.hpp"

// NOTE: (Ian) The state manager *may* not need to be exposed at all
namespace Mirage{
    class StateManager {
    public:
        StateManager();
        ~StateManager();

        void PushState(State * state);
        void PushOverlay(State * state);
        void PopState();
        void PopState(State * state);
        void PopOverlay(State * state);

        void ChangeState(State * state);

        void Update();
    private:
        struct Impl;
        Owned<Impl> impl;
    };
}