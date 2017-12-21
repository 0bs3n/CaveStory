#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "level.h"

class Graphics;

class Game {

public:
    Game();
    ~Game();
private:
    void gameLoop();
    void draw( Graphics &graphics );
    void update( float elapsedTime );
    void limitFPS( float elapsedTime, int FPS );

    Player _player;
    Level _level;

};

#endif
