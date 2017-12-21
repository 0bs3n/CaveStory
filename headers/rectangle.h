#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "globals.h"

class Rectangle {
public:
    Rectangle() {}
    Rectangle( int x, int y, int width, int height ) :
        _x(x),
        _y(y),
        _width(width),
        _height(height)
    {}
    
    int getCenterX() const { return this->_x + this->_width / 2; }
    int getCenterY() const { return this->_y + this->_height / 2; }

    int getLeft() const { return this->_x; }
    int getRight() const { return this->_x + this->_width; }

    int getTop() const { return this->_y; }
    int getBottom() const { return this->_y + this->_height; }

    int getWidth() const { return this->_width; }
    int getHeight() const { return this->_height; }

    int getSide( const sides::Side side ) const {

        return 
            side == sides::LEFT ? this->getLeft() :
            side == sides::RIGHT ? this->getRight() :
            side == sides::TOP ? this->getTop() :
            side == sides::BOTTOM ? this->getBottom() :
            sides::NONE;
    }

    bool colidesWith( const Rectangle &other ) const {
        return
            this->getRight() >= other.getLeft() &&
            this->getLeft() <= other.getRight() &&
            this->getTop() <= other.getBottom() &&
            this->getBottom() >= other.getTop();
    }

    // TODO If something fails please add paranthesis to this to see if it fixes it
    bool isValidRectangle() const {
        return 
            this->_x >= 0 && 
            this->_y >= 0 && 
            this->_width >= 0 && 
            this->_height >= 0;
    }

private:
    int _x, _y, _width, _height;

};



#endif
