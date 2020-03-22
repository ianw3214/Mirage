#pragma once

#include "core.hpp"
#include "state.hpp"
#include "mirage/util/util.hpp"

// NOTE: (Ian) The state manager *may* not need to be exposed at all
namespace Mirage{
    class MIRAGE_API StateManager {
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