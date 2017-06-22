#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"
#include <map>
#include "globals.h"
#include <vector>

class Graphics;

class AnimatedSprite : public Sprite {
public:

    AnimatedSprite();
    AnimatedSprite( Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, 
            int posX, int posY, float timeToUpdate);

    /* void playAnimation
     * Plays the animation if it isn't already playing 
     */

    void playAnimation( std::string animation, bool once = false );

    /* void update
     * Updates the animated sprite (timer)
     */
    void update( int elapsedTime );

    /* void draw
     * Draws the sprite to the screen
     */
    void draw( Graphics &graphics, int x, int y );

    /* void setupAnimations
     * A required function that sets up all animations for a sprite
     */
    virtual void setupAnimations();

private:
    
    std::map< std::string, std::vector<SDL_Rect> > _animations;
    std::map< std::string, Vector2> _offsets;

    int _frameIndex;
    double _timeElapsed;
    bool _visible;

protected:

    double _timeToUpdate;
    bool _currentAnimationOnce;
    std::string _currentAnimation;

    /* void addAnimation
     * Adds an animation to the map of animations for the sprite
     */
    void addAnimation( int frames, int x, int y, std::string name, int width, int height, Vector2 offset );

    /* void resetAnimations
     * resets the map containing animations for the sorite
     * resets all animations associated with the sprite
     */
    void resetAnimations();

    /* void stopAnimation
     * stop current animation
     */
    void stopAnimation();

    /* void setVisible
     * changes the visibility of the animated sprite
     */
    void setVisible( bool visible );

    /* void animationDone
     * logic that occurs what an animation ends. REQUIRED. 
     */
    virtual void animationDone( std::string currentAnimation);

};

#endif

