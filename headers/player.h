#ifndef PLAYER_H
#define PLAYER_H

#include "animated_sprite.h"
#include "globals.h"

class Graphics;

class Player : public AnimatedSprite {
public:
    Player();
    Player( Graphics &graphics, Vector2 spawnPoint);
    void draw( Graphics &graphics );
    void update( float elapsedTime );

    /* void moveLeft
     * moves the palyer left by positive _dx
     */
    void moveLeft();

    /* void moveRight
     * moves the palyer right by negative _dx
     */
    void moveRight();

    /* void stopMoving
     * stops player from moving and maintains direction, then plays idle animation for that direction
     */
    void stopMoving();

    void crouch();

    virtual void animationDone( std::string currentAnimation );
    virtual void setupAnimations();

    void handleTileCollisions( std::vector<Rectangle> &others );
    float getX() const;
    float getY() const;


private:
    float _dx, _dy; //change in x postion/ change of y postion during a given frame ( d for delta or change )
    Direction _facing;
    bool _grounded;
    
};





#endif
