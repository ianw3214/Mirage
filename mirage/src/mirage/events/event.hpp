#pragma once

#include <vector>

struct Input {
    // Window events
    bool windowClosed;

    // Mouse events
    int mouseX;
    int mouseY;
    bool leftMouseClicked;
    bool leftMouseReleased;

    // Key events
    std::vector<int> pressedKeys;
    std::vector<int> releasedKeys;

    // Clearing inputs
    Input() : 
        windowClosed(false), 
        mouseX(0), 
        mouseY(0), 
        leftMouseClicked(false),
        leftMouseReleased(false) 
    {
        pressedKeys.reserve(10);
        releasedKeys.reserve(10);
    }
    void clear() {
        windowClosed = false;
        mouseX = 0;
        mouseY = 0;
        leftMouseClicked = false;
        leftMouseReleased = false;
        pressedKeys.clear();
        releasedKeys.clear();
    }

    // Utility functions - to be implemented by platform
    bool KeyPressed(int key) const;
};