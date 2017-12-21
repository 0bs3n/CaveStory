#include "animated_sprite.h"
#include "gfx.h"
#include "sprite.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite( Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, 
        int posX, int posY, float timeToUpdate) :
            Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
            _frameIndex(0),
            _visible(true),
            _timeToUpdate(timeToUpdate),
            _currentAnimationOnce(false),
            _currentAnimation("")
{}

void AnimatedSprite::addAnimation( int frames, int x, int y, std::string name, int width, int height, Vector2 offset ) {
    std::vector< SDL_Rect > rectangles;

    for ( int i = 0; i < frames; i++ ) {
        SDL_Rect newRect = { (i + x) * width, y, width, height };
        rectangles.push_back( newRect );
    }

    this->_animations.insert( std::pair< std::string, std::vector<SDL_Rect> > (name, rectangles));
    this->_offsets.insert( std::pair<std::string, Vector2> (name, offset) );

}



/* fix for weird running frames from youtube: TODO: study this
 * void AnimatedSprite::addAnimation(std::vector<Vector2> & frames, std::string name, int width, int height, Vector2 offset) {
        std::vector<SDL_Rect> rectangles;
        for (int i = 0; (unsigned)i < frames.size(); i++) {
                SDL_Rect newRect = {frames[i].x * width, frames[i].y * height, width, height};
                rectangles.push_back(newRect);
        }
        this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));
        this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}
*/

void AnimatedSprite::resetAnimations() {
    this->_animations.clear();
    this->_offsets.clear();
}

void AnimatedSprite::playAnimation( std::string animation, bool once ) {
    this->_currentAnimationOnce = once;
    if ( this->_currentAnimation != animation ) {
        this->_currentAnimation = animation;
        this->_frameIndex = 0;
    }
}

void AnimatedSprite::setVisible( bool visible ) {
    this->_visible = visible;
}

void AnimatedSprite::stopAnimation() {
    this->_frameIndex = 0;
    this->animationDone( this->_currentAnimation );
}

void AnimatedSprite::update( int elapsedTime ) {
    Sprite::update();

    this->_timeElapsed += elapsedTime;

    if ( this->_timeElapsed > this->_timeToUpdate ) {
        this->_timeElapsed -= this->_timeToUpdate;

        if ( (unsigned)this->_frameIndex < this->_animations[_currentAnimation].size() - 1 ) {
                this->_frameIndex++;

            } else {

            if ( this->_currentAnimationOnce == true ) {
                this->setVisible( false );
            }

            this->_frameIndex = 0;
            this->animationDone( this->_currentAnimation );
        }
    }
}

void AnimatedSprite::draw( Graphics &graphics, int x, int y ) {
    if ( this->_visible ) {
        SDL_Rect destinationRectangle;
        destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
        destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
        destinationRectangle.w = this->_sourceRect.w * globals::SPRITE_SCALE;
        destinationRectangle.h = this->_sourceRect.h * globals::SPRITE_SCALE;

        SDL_Rect sourceRect= this->_animations[this->_currentAnimation][this->_frameIndex];
        graphics.blitSurface( this->_spriteSheet, &sourceRect, &destinationRectangle);

    }
}

//void AnimatedSprite::setupAnimations() {
//}

/*
void AnimatedSprite::setupAnimations() {
        std::vector<Vector2> RunLeftFrames;
        RunLeftFrames.insert(RunLeftFrames.end(), {Vector2(0, 0), Vector2(1, 0), Vector2(0, 0), Vector2(2, 0)});
        this->addAnimation(RunLeftFrames, "RunLeft", 32, 32, Vector2(0, 0));
 
        std::vector<Vector2> RunRightFrames;
        RunRightFrames.insert(RunRightFrames.end(), {Vector2(0, 1), Vector2(1, 1), Vector2(0, 1), Vector2(2, 1)});
        this->addAnimation(RunRightFrames, "RunRight", 32, 32, Vector2(0, 0));
}
*/
