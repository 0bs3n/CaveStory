#include <SDL2/SDL.h>
#include "game.h"
#include "gfx.h"
#include "input.h"
#include "sprite.h"
#include <stdio.h>


/* Game class Implementation
 * Holds all information for main game loop.
 */ 

namespace {
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}


Game::Game() {
    SDL_Init( SDL_INIT_EVERYTHING );
    this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {

    Graphics graphics;
    Input input;
    SDL_Event event;
    bool running = true;

    this->_player = Sprite( graphics, "./data/sprites/MyChar.png", 0, 0, 16, 16, 100, 100 );

    int LAST_UPDATE_TIME = SDL_GetTicks();

    //Start game loop
    while ( running ) {
        input.beginNewFrame();

        if (SDL_PollEvent( &event )) {

            if ( event.type == SDL_KEYDOWN ) {
                if ( event.key.repeat == 0 ) {
                    input.keyDownEvent( event );
                }
            }

            else if ( event.type == SDL_KEYUP ) {
                input.keyUpEvent( event );
            }

            else if ( event.type == SDL_QUIT ) {
                return;
            }
        }

        if ( input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true )
            return;

        const int CURRENT_TIME_MS = SDL_GetTicks();
        
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

        this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));

        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        this->draw( graphics );
    }
}

void Game::draw( Graphics &graphics ) {

    graphics.clear();
    this->_player.draw( graphics, 100, 100 );
    graphics.flip();
}

void Game::update( float elapsedTime ) {
    // Section by ethan, limit FPS to be at MOST 50 fps, to prevent my CPU from freaking out during dev
    const float MIN_FRAME_TIME = ( 1000 / (float)50 );
    if ( elapsedTime < MIN_FRAME_TIME )
        SDL_Delay( MIN_FRAME_TIME - elapsedTime );
    // End ethan's section
    
    

}

