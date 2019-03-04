#pragma once

struct Input {
    // Window events
    bool windowClosed;

    // Mouse events
    int mouseX;
    int mouseY;
    bool leftMouseClicked;

    // Clearing inputs
    Input() : windowClosed(false), mouseX(0), mouseY(0), leftMouseClicked(false) {}
    void clear() {
        windowClosed = false;
        mouseX = 0;
        mouseY = 0;
        leftMouseClicked = false;
    }
};