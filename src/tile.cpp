#include "tile.h"
#include "gfx.h"

#include <SDL2/SDL.h>

Tile::Tile() {}
Tile::Tile( SDL_Texture *tileset, Vector2 size, Vector2 tilesetPostition, Vector2 position ) :
        _tileset(tileset),
        _size(size),
        _tilesetPostition(tilesetPostition),
        _position( Vector2( position.x * globals::SPRITE_SCALE, position.y * globals::SPRITE_SCALE)) 
{}

void Tile::update( float elapsedTime ) {}

void Tile::draw( Graphics &graphics ) {

    SDL_Rect destRect = { 
        this->_position.x, 
        this->_position.y, 
        this->_size.x * (int)globals::SPRITE_SCALE, 
        this->_size.y * (int)globals::SPRITE_SCALE 
    };

    SDL_Rect sourceRect = {
        this->_tilesetPostition.x, 
        this->_tilesetPostition.y,
        this->_size.x, 
        this->_size.y
    };

    graphics.blitSurface( this->_tileset, &sourceRect, &destRect );
}
 
