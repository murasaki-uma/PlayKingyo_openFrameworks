//
//  Bubble.h
//  LeapKingyo
//
//  Created by 岩城勇磨 on 2015/02/20.
//
//

#ifndef __LeapKingyo28__Bubble__
#define __LeapKingyo28__Bubble__

#include <stdio.h>
#include "ofMain.h"

class Bubble {
public:
    float x,y;
    float rad;
    float spX, spY;
    float friction;
    int direction;
    Bubble(float x_, float y_, float rad_, float spX_, float spY_, int direction_);
    ~Bubble();
    void display();
    void move();
    void BubbleAdd(float bubble_x, float bubble_y);

private:
};

#endif /* defined(__LeapKingyo28__Bubble__) */
