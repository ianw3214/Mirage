#include "stateManager.hpp"

// The impl purely holds data needed for the implementation
#include <vector>
struct Mirage::StateManager::Impl {
    std::vector<State*> states;
    std::vector<State*>::iterator state_insert;
};

Mirage::StateManager::StateManager() {
    impl = new Impl();
    impl->state_insert = impl->states.begin();
}
Mirage::StateManager::~StateManager() {
    for (State * state : impl->states) {
        delete state;
    }
    delete impl;
}

void Mirage::StateManager::PushState(State * state) {
    state->Init();
    impl->state_insert = impl->states.emplace(impl->state_insert, state);
}

void Mirage::StateManager::PushOverlay(State * state) {
    state->Init();
    impl->states.emplace_back(state);
}

void Mirage::StateManager::PopState() {
    if (impl->state_insert != impl->states.begin()) {
        // Call SHUTDOWN of state here as well
        delete *(impl->state_insert);
        impl->states.erase(impl->state_insert);
        impl->state_insert--;
    }
}

void Mirage::StateManager::PopState(State * state) {
    auto it = std::find(impl->states.begin(), impl->states.end(), state);
    if (it != impl->states.end()) {
        delete *it;
        impl->states.erase(it);
        impl->state_insert--;
    }
}

void Mirage::StateManager::PopOverlay(State * state) {
    auto it = std::find(impl->states.begin(), impl->states.end(), state);
    if (it != impl->states.end()) {
        delete *it;
        impl->states.erase(it);
    }
}


void Mirage::StateManager::ChangeState(State * state) {
    for (State * state : impl->states) {
        delete state;
    }
    impl->states.clear();
    impl->states.push_back(state);
}

void Mirage::StateManager::Update() {
    for (State * state : impl->states) {
        state->Update();
    }
}