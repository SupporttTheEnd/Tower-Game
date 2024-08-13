#include "Game.h"
#include "TextureManager.h"

using namespace std;

const int playerHeight = 192; 
const int heartCount = 5; 

SDL_Rect playerRect = {360, 260, 128, 128};
SDL_Rect hitboxRect; // New hitbox for the player
SDL_Rect srcRect; 
SDL_Texture* playerTex; 

vector<SDL_Rect> hearts; 
SDL_Texture* heartTex; 

SDL_Rect castleRect = {-50, -250, 400, 300}; 
SDL_Texture* castleTex;

SDL_Rect backgroundRect = {0, 0, 800, 600};
SDL_Texture* backgroundTex;

// Base velocities
float baseVelocityX = -3.0f; // Base horizontal velocity
float baseVelocityY = -3.0f; // Base vertical velocity

// Dynamic velocity modifiers
float velocityModifierX = 0.0f;
float velocityModifierY = 0.0f;

Game::Game() {
    count = 0; 
    currentState = IDLE; 
    currentFrame = 0; 
    frameStart = SDL_GetTicks();

    for (int i = 0; i < heartCount; i++) {
        SDL_Rect heart = {10 + i * 50, 10, 40, 40}; 
        hearts.push_back(heart);
    }

    hitboxRect.w = 32;
    hitboxRect.h = 32;
}

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0; 
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "Subsystems Initialized" << endl; 
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            cout << "Window created!" << endl; 
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            cout << "Renderer created!" << endl; 
        }
        isRunning = true; 
    } else {
        isRunning = false; 
    }

    playerTex = TextureManager::LoadTexture("assets/player_sheet.png", renderer);
    heartTex = TextureManager::LoadTexture("assets/heart.png", renderer);
    backgroundTex = TextureManager::LoadTexture("assets/background.png", renderer);
    castleTex = TextureManager::LoadTexture("assets/Castle_Blue.png", renderer);
}

void Game::handleEvents() {
    SDL_Event event; 
    SDL_PollEvent(&event);
    
    if (event.type == SDL_QUIT) {
        isRunning = false;
    } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_UP) {
            currentState = WALKING_UP;
            velocityModifierY = -baseVelocityY;
        } else if (event.key.keysym.sym == SDLK_DOWN) {
            currentState = WALKING_DOWN;
            velocityModifierY = baseVelocityY;
        } else if (event.key.keysym.sym == SDLK_LEFT) {
            currentState = WALKING_LEFT;
            velocityModifierX = -baseVelocityX;
        } else if (event.key.keysym.sym == SDLK_RIGHT) {
            currentState = WALKING_RIGHT;
            velocityModifierX = baseVelocityX;
        } else if (event.key.keysym.sym == SDLK_SPACE) {
            if (currentState == WALKING_UP) {
                currentState = WALKING_UP_ATK;
            } else if (currentState == WALKING_DOWN) {
                currentState = WALKING_DOWN_ATK;
            } else if (currentState == WALKING_LEFT) {
                currentState = WALKING_LEFT_ATK;
            } else if (currentState == WALKING_RIGHT) {
                currentState = WALKING_RIGHT_ATK;
            }
        }
    } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_SPACE) {
            if (currentState == WALKING_UP_ATK) {
                currentState = WALKING_UP;
            } else if (currentState == WALKING_DOWN_ATK) {
                currentState = WALKING_DOWN;
            } else if (currentState == WALKING_LEFT_ATK) {
                currentState = WALKING_LEFT;
            } else if (currentState == WALKING_RIGHT_ATK) {
                currentState = WALKING_RIGHT;
            }
        } else {
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
                event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
                velocityModifierX = 0;
                velocityModifierY = 0;
            }
        }
    }
}

void Game::update() {
    // Store previous positions for collision resolution
    SDL_Rect prevBackgroundRect = backgroundRect;
    SDL_Rect prevCastleRect = castleRect;

    // Update positions based on current velocities
    backgroundRect.x += static_cast<int>(velocityModifierX);
    backgroundRect.y += static_cast<int>(velocityModifierY);
    
    castleRect.x += static_cast<int>(velocityModifierX);
    castleRect.y += static_cast<int>(velocityModifierY);

    // Update hitbox position
    hitboxRect.x = playerRect.x + (playerRect.w / 3); // Center the hitbox
    hitboxRect.y = playerRect.y + (playerRect.h / 3); // Center the hitbox

    // Check for collision with castle
    if (SDL_HasIntersection(&hitboxRect, &castleRect)) {
        // Revert to previous positions if a collision is detected
        backgroundRect = prevBackgroundRect;
        castleRect = prevCastleRect;

        if (hearts.size() > 0){
            hearts.pop_back();
        }
        // Stop movement on collision
        velocityModifierX = 0; 
        velocityModifierY = 0; 
    }

    // Handle sprite frame updates
    if (SDL_GetTicks() - frameStart > 100) {
        currentFrame++;
        
        if (currentState == WALKING_LEFT_ATK || currentState == WALKING_RIGHT_ATK || 
            currentState == WALKING_UP_ATK || currentState == WALKING_DOWN_ATK) {
            if (currentFrame >= 6) {
                currentFrame = 0;
            }
        } else {
            if (currentFrame >= 3) {
                currentFrame = 0;
            }
        }
        
        frameStart = SDL_GetTicks();
    }
    
    // Set source rectangle based on current state
    if (currentState == WALKING_UP_ATK || currentState == WALKING_UP) {
        srcRect.y = playerHeight * 7;
    } else if (currentState == WALKING_DOWN_ATK || currentState == WALKING_DOWN) {
        srcRect.y = playerHeight * 4;
    } else if (currentState == WALKING_LEFT_ATK || currentState == WALKING_RIGHT_ATK || 
               currentState == WALKING_LEFT || currentState == WALKING_RIGHT) {
        srcRect.y = playerHeight * 2;
    } else {
        srcRect.y = 0; 
    }
    
    srcRect.x = currentFrame * playerHeight;
    srcRect.w = playerHeight;
    srcRect.h = playerHeight;
}

void Game::render() {
    SDL_RenderClear(renderer); 

    SDL_RenderCopy(renderer, backgroundTex, NULL, &backgroundRect);
    SDL_RenderCopy(renderer, castleTex, NULL, &castleRect);

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (currentState == WALKING_LEFT_ATK || currentState == WALKING_LEFT) {
        flip = SDL_FLIP_HORIZONTAL;
    }
    SDL_RenderCopyEx(renderer, playerTex, &srcRect, &playerRect, 0, NULL, flip);

    for (const auto& heart : hearts) {
        SDL_RenderCopy(renderer, heartTex, NULL, &heart);
    }

    SDL_RenderPresent(renderer); 
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(playerTex);
    SDL_DestroyTexture(heartTex);
    SDL_DestroyTexture(backgroundTex);
    SDL_DestroyTexture(castleTex); 
    SDL_Quit();
    cout << "Game Cleaned" << endl;
}
