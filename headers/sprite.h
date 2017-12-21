#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h> 
#include "rectangle.h"
#include "globals.h"

class Graphics;

class Sprite {
public:
	Sprite();

    Sprite( Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);

    virtual ~Sprite();
    // virtual void update( int elapsedTime );
    virtual void update();
    void draw(Graphics &graphics, int x, int y);

    Rectangle getBoundingBox() const;
    sides::Side getCollisionSide( Rectangle &other ) const;

protected:
    Rectangle _boundingBox;
    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;
    float _x, _y;

private:

};






#endif
