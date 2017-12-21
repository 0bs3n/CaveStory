#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "rectangle.h"
#include "globals.h"
#include "tile.h"
#include "slope.h"

class Graphics;
class Tile;
struct Tileset;
struct SDL_Texture;
struct SDL_Rect;

class Level {
public:
    Level();
    Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
    ~Level();

    void update(float elapsedTime);
    void draw(Graphics &graphics);

    std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
    std::vector<Slope> checkSlopes(const Rectangle &other);

    Vector2 getPlayerSpawnPoint() const;

private:
    std::string _mapName;
    Vector2 _spawnPoint;
    Vector2 _size;
    Vector2 _tileSize;
    SDL_Texture *_backgroundTexture;

    std::vector<Tile> _tileList;
    std::vector<Tileset> _tilesets;
    std::vector<Rectangle> _collisionRects;
    std::vector<Slope> _slopes;
    

    /* void loadMap
     * loads a map
     */
    void loadMap(std::string mapName, Graphics &graphics);

};

struct Tileset {
    SDL_Texture *Texture;
    int FirstGid;
    Tileset() {
        FirstGid = -1;
    }
    Tileset (SDL_Texture *texture, int firstGid) {
        this->Texture = texture;
        this->FirstGid = firstGid;
    }

};

#endif
