#ifndef GFX_H
#define GFX_H

/*
 * Holds all information to do with the graphics and rendering of the game.
 */

#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Rect;


class Graphics {
public:
    Graphics();
    ~Graphics();

    /* SDL_Surface* loadImage
     * Loads an image into the _spriteSheets map if it doesn't already exist.
     * as a result, each image will only be loaded once.
     * return the image from the map regardless of whether or not it was just loaded.
     */
    SDL_Surface* loadImage( const std::string &filePath);

    /* void blitSurface
     * Draws a texture <sourceRectangle> from a source texture <source>
     * to a certain part of the screen <destinationRectangle>
     */
    void blitSurface( SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle );

    /* void flip
     * renders everything to the screen
     */
    void flip();

    /* void clear
     * clears the screen
     */
    void clear();

    /* SDL_Renderer* getRenderer
     * returns the renderer 
     */
    SDL_Renderer* getRenderer() const;

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::map<std::string, SDL_Surface*> _spriteSheets;
        
};




#endif
