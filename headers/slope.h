#ifndef SLOPE_H
#define SLOPE_H

#include "globals.h"
#include "rectangle.h"

class Slope {

public:

    Slope( Vector2 p1, Vector2 p2 ) : _p1(p1), _p2(p2) {

        if ( this->_p2.x - this->_p1.x != 0 ) {
        this->_slope = ( (float)this->_p2.y - (float)this->_p1.y) / ( (float)this->_p2.x - (float)this->_p1.x);
        }

    }

    inline float getSlope() const {
        return this->_slope;
    }

    bool collidesWith( const Rectangle &other ) const {
        return
            ( other.getRight() >= this->_p2.x &&
              other.getLeft() <= this->_p1.x &&
              other.getTop() <= this->_p2.y &&
              other.getBottom() >= this->_p1.y ) ||

            ( other.getRight() >= this->_p1.x &&
              other.getLeft() <= this->_p2.x &&
              other.getTop() <= this->_p1.y &&
              other.getBottom() >= this->_p2.y ) ||

            ( other.getLeft() <= this->_p1.x &&
              other.getRight() >= this->_p2.x &&
              other.getTop() <= this->_p1.y &&
              other.getBottom() >= this->_p2.y ) ||

            ( other.getLeft() <= this->_p2.x &&
              other.getRight() >= this->_p1.x &&
              other.getTop() <= this->_p2.y &&
              other.getBottom() >= this->_p1.y );

    }

    inline Vector2 getP1() const { return this->_p1; }
    inline Vector2 getP2() const { return this->_p2; }


private:
    Vector2 _p1, _p2;
    float _slope;
};



#endif
