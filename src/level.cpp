#include <SDL2/SDL.h>
#include <tinyxml2.h>

#include "level.h"
#include "gfx.h"
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace tinyxml2;

Level::Level() {}

Level::Level( std::string mapName, Vector2 spawnPoint, Graphics &graphics ) :
    _mapName(mapName),
    _spawnPoint(spawnPoint),
    _size( Vector2( 0,0 ) ) // _size( Vector2( 0,0 ))
{ 
   this->loadMap( mapName, graphics );
}

Level::~Level() {}

void Level::loadMap( std::string mapName, Graphics &graphics ) {
    // Parse the .tmx file
    XMLDocument doc;
    std::stringstream ss;
    ss << "data/maps/" << mapName << ".tmx"; // if (mapName == "Map_1") -> "data/maps/Map_1.tmx"
    doc.LoadFile( ss.str().c_str() );
    XMLElement *mapNode = doc.FirstChildElement( "map" );

    // Get the width and the height of the whole map and store it in _size
    int width, height;
    mapNode->QueryIntAttribute( "width", &width );
    mapNode->QueryIntAttribute( "height", &height );
    this->_size = Vector2( width, height );

    // Get the width and the height of the tile and store it in _tileSize
    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute( "tilewidth", &tileWidth );
    mapNode->QueryIntAttribute( "tileheight", &tileHeight );
    this->_tileSize = Vector2( tileWidth, tileHeight );

    // Load the tilesets
    XMLElement *pTileset = mapNode->FirstChildElement( "tileset" );
    if ( pTileset != NULL ) {
        while( pTileset ) {
            int firstGid;
            const char* source = pTileset->FirstChildElement( "image" )->Attribute( "source" );
            std::stringstream ss;
            ss << "data/tilesets/" << source;
            pTileset->QueryIntAttribute( "firstgid", &firstGid );
            SDL_Texture* tex = SDL_CreateTextureFromSurface( graphics.getRenderer(), graphics.loadImage( ss.str() ) );
            this->_tilesets.push_back( Tileset( tex, firstGid ));

            pTileset = pTileset->NextSiblingElement( "tileset" );
        }
    }

    // Load Layers
    XMLElement *pLayer = mapNode->FirstChildElement( "layer" );
    if ( pLayer != NULL ) {
        while ( pLayer ) {
            // Loading the data element
            XMLElement *pData = pLayer->FirstChildElement( "data" );
            if ( pData != NULL ) {
                while ( pData ) {
                    // Loading Tile element
                    XMLElement *pTile = pData->FirstChildElement( "tile" );
                    if ( pTile != NULL ) {
                        int tileCounter = 0;
                        while ( pTile ) {
                            
                            // Build each individual tile here
                            // If gid is 0, no tile should be drawn, continue loop.
                            if ( pTile->Attribute( "gid" ) == 0 ) { 
                                tileCounter++;
                                if ( pTile->NextSiblingElement( "tile" )) {
                                    pTile = pTile->NextSiblingElement( "tile" );
                                    continue;
                                } 

                                else {
                                    break;
                                }
                            }


                            // Get the tileset for this specific gid
                            int gid = pTile->IntAttribute( "gid" );
                            Tileset tls;
                            for ( int i = 0; i < this->_tilesets.size(); i++ ) {
                                if ( this->_tilesets[i].FirstGid <= gid ) {
                                    // This is the tileset we want
                                    tls = this->_tilesets[i];
                                }
                            }

                            if ( tls.FirstGid == -1 ) {
                                // No tileset was found for this gid
                                tileCounter++;
                                if ( pTile->NextSiblingElement( "tile" )) {
                                    pTile = pTile->NextSiblingElement( "tile" );
                                    continue;
                                }
                                else {
                                    break;
                                }
                            }
                            
                            // Get the postition of the tile in the level
                            int xx = 0;
                            int yy = 0;

                            xx = tileCounter % width;
                            xx *= tileWidth;
                            yy += tileHeight * ( tileCounter / width );
                            Vector2 finalTilePostition = Vector2( xx, yy );

                            // Calculate the postition of the tile in the tileset
                            int tilesetWidth, tilesetHeight;
                            SDL_QueryTexture( tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight );
                            int tsxx = gid % ( tilesetWidth / tileWidth ) - 1;
                            tsxx *= tileWidth;
                            int tsyy = 0;
                            int amt = gid / ( tilesetWidth /tileWidth );
                            tsyy = tileHeight * amt;
                            Vector2 finalTilesetPostition = Vector2( tsxx, tsyy );

                            // Build the actual tile and add it to the levels _tileList.
                            Tile tile(tls.Texture, Vector2( tileWidth, tileHeight ),
                                    finalTilesetPostition, finalTilePostition );
                            this->_tileList.push_back( tile );
                            tileCounter++;

                            
                            pTile = pTile->NextSiblingElement( "tile" );
                        }
                    }
                    pData = pData->NextSiblingElement( "data" );
                }
            }
            pLayer = pLayer->NextSiblingElement( "layer" );
        }
    }
    // Parse out collisions
    XMLElement *pObjectGroup = mapNode->FirstChildElement( "objectgroup" );
    if ( pObjectGroup != NULL ) {
        while (pObjectGroup ) {
            const char* name = pObjectGroup->Attribute( "name" );
            std::stringstream ss;
            ss << name;
            if (ss.str() == "collisions" ) {
                XMLElement *pObject = pObjectGroup->FirstChildElement( "object" );
                if ( pObject != NULL ) {
                    while ( pObject ) {
                        float x, y, width, height;
                        x = pObject->FloatAttribute( "x" );
                        y = pObject->FloatAttribute( "y" );
                        width = pObject->FloatAttribute( "width" );
                        height = pObject->FloatAttribute( "height" );
                        this->_collisionRects.push_back( Rectangle( 
                                    std::ceil( x ) * globals::SPRITE_SCALE,
                                    std::ceil( y ) * globals::SPRITE_SCALE,
                                    std::ceil( width ) * globals::SPRITE_SCALE,
                                    std::ceil( height ) * globals::SPRITE_SCALE 
                                    ));


                        pObject = pObject->NextSiblingElement( "object" );
                    }
                }
                
            }
            // Other object groups go here with to catch all possible object groups
            // with and else if ( ss.str() == "<group name>" ) {...}
             
            
            else if ( ss.str() == "spawn points" ) {
                XMLElement *pObject = pObjectGroup->FirstChildElement( "object" );
                if ( pObject != NULL ) {
                    while ( pObject ) {
                        float x = pObject->FloatAttribute( "x" );
                        float y = pObject->FloatAttribute( "y" );
                        const char* name = pObject->Attribute( "name" );
                        std::stringstream ss;
                        ss << name;
                        if ( ss.str() == "player" ) {
                            this->_spawnPoint = Vector2( std::ceil( x ) * globals::SPRITE_SCALE, 
                                                    std::ceil( y ) * globals::SPRITE_SCALE );
                        }

                        pObject = pObject->NextSiblingElement( "object" );
                    }
                }
            }

            // START SLOPES
            else if ( ss.str() == "slopes" ) {
                XMLElement *pObject = pObjectGroup->FirstChildElement( "object" );
                if ( pObject != NULL ) {
                    while ( pObject ) {
                        std::vector<Vector2> points;
                        Vector2 p1;

                        p1 = Vector2( ceil( pObject->FloatAttribute( "x" )), ceil( pObject->FloatAttribute( "y" )));

                        pObject = pObject->NextSiblingElement( "object" );
                    }
                }
            }
            //END SLOPES

            pObjectGroup = pObjectGroup->NextSiblingElement( "objectgroup" );
        }
    }

}

void Level::update( float elapsedTime ) {}

std::vector<Rectangle> Level::checkTileCollisions( const Rectangle &other ) {
    std::vector<Rectangle> others;
    for ( int i = 0; i < this->_collisionRects.size(); i++ ) {
        if ( this->_collisionRects.at(i).colidesWith( other )) {
            others.push_back( this->_collisionRects.at(i) );
        }
    }
    return others;
}

void Level::draw( Graphics &graphics ) {
    for ( int i = 0; i < this->_tileList.size(); i++ ) {
        this->_tileList.at( i ).draw( graphics );
    }
}

Vector2 Level::getPlayerSpawnPoint() const {
    return this->_spawnPoint;
}
