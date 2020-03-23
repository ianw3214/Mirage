#pragma once

namespace Mirage{
    class State {
    public:
        State() {}
        virtual ~State() {}

        virtual void Init() {}
        virtual void Shutdown() {}

        virtual void Update() {}
    };
}