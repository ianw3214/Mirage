# MIRAGE GAME ENGINE

## ENGINE TASKS

- [x] Setup renderer
- [ ] Misc. utilities
  - [x] Common structs
  - [ ] Math utilities
  - [ ] Debugging utilities (logging)
  - [x] Smart pointer utilities
    - [x] Investigate not using smart pointers for engine stuff since it's usually simpler
  - [ ] Profiling/Performance
  - [x] Traps
- [ ] Re-organize folder structure in engine
- [x] Implement renderer
  - [x] Make renderer more accessible from game
- [x] Model loading
  - [x] Separate model class
  - [x] Model textures
- [x] Proper rendering w/ transforms
  - [x] Move transform setting code into model code
  - [x] Camera class  
- [x] Specify initial state (Reference Oasis game engine?)
  - [x] Remove polymorphism from Application class?
- [x] Remove two project setup (too many headaches)
- [ ] Quaternions (yay!)
- [x] Lighting
- [x] Setup ImGui
  - [ ] ImGui text input not working
  - [x] Basic core engine info ImGui window
- [ ] Resource system
  - [ ] Texture resource
- [ ] Remove unnecessary namespaces
- [x] Terrain setup
  - [x] Properly orient terrain + allow multiple terrain pieces
  - [x] Heightmap
    - [ ] Heightmap optimizations
    - [ ] Don't use png for file storage
  - [ ] Terrain manager
  - [ ] Move to better folder location - graphicsUtils/graphicsToolbox
  - [ ] [Get height of terrain](https://www.youtube.com/watch?v=6E2zjfzMs7c)
  - [ ] Raycast onto terrain
- [ ] Fog system
- [ ] Skybox
- [ ] Integrate console system
  - [ ] Command system

## GAME TASKS

- [ ] Character in game
  - [x] Character controller (movement)
  - [x] Character controller (camera rotation)
  - [x] Camera rotation in up/down axis as well
  - [ ] Character moves with terrain (not necessarily physics based)
- [ ] Entity system
- [x] Day night system
  - [ ] Update shader lights as well

## EDITOR TASKS

- [ ] Terrain editor
  - [ ] Ray cast from mouse to terrain
  - [ ] Draw circle around mouse position on terrain

## MISC PROGRAMMING TASKS

- [ ] Clean up namespace clutter
- [ ] Expose window from engine (width/height, etc...)
- [ ] Get rid of smart pointer ( I HATE SMART POINTERS )

## ART TASKS

- [ ] Concept explorations
- [ ] Digital painted splash art
- [ ] Learn 3d modelling
  - [ ] Character model
  - [ ] Tree model

## GENERAL TASKS

- [ ] General game design
- [ ] Re-organize TODOs to be more categorized
