#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    
    const float SPRITE_SCALE = 2.0f;

}

namespace sides {
    enum Side {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE
    };

    inline Side getOppositeSide( Side side ) {
        return
            side == TOP ? BOTTOM :
            side == BOTTOM ? TOP :
            side == RIGHT ? LEFT :
            side == LEFT ? RIGHT :
            NONE;
    }
}

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Vector2 {
    int x, y;
     
    // Default initializer for Vector2
    Vector2() : 
        x(0), y(0) 
    {} // Initialize and do nothing

    // Full initializer for Vector2
    Vector2( int x, int y ) : 
        x(x), y(y) 
    {} // Initialize and do nothing

    // Create and empty Vector2 object
    Vector2 zero() {
        return Vector2( 0, 0 );
    }

};



#endif
