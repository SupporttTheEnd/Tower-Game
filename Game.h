#include <iostream>
#include <cmath>
#include "inc/SDL.h"
#include "inc/SDL_image.h"
#include <vector>

using namespace std;
#undef main

#ifndef GAME_H
#define GAME_H

enum AnimationState {
    IDLE,
    WALKING_UP, 
    WALKING_DOWN, 
    WALKING_RIGHT, 
    WALKING_LEFT,
    WALKING_UP_ATK, 
    WALKING_DOWN_ATK, 
    WALKING_RIGHT_ATK, 
    WALKING_LEFT_ATK
};

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {return SDL_HasIntersection(&a, &b);}
    bool running() {return isRunning;}

private:
    AnimationState currentState; 
    int currentFrame;
    Uint32 frameStart; 
    int count; 
    bool isRunning; 
    SDL_Window *window; 
    SDL_Renderer *renderer; 
};

#endif