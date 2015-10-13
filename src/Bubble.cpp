//
//  Bubble.cpp
//  LeapKingyo28
//
//  Created by 岩城勇磨 on 2015/02/20.
//
//

#include "Bubble.h"

Bubble::Bubble(float x_, float y_, float rad_, float spX_, float spY_, int direction_) {
    x = x_;
    y = y_;
    rad = rad_;
    spX = spX_;
    spY = spY_;
    friction = 0.9;
    direction = direction_;
}

Bubble::~Bubble() {
    
}

void Bubble::display() {
    ofFill();
    ofSetColor(ofRandom(70, 90), ofRandom(170, 190), ofRandom(180, 220), 100*(rad-1)/3);
    ofEllipse(x, y, rad, rad);
}

void Bubble::move() {
    //spX *= friction;
    //spX *= direction;
    x += spX*friction;
    //cout << "x :" << spX << endl;
    
    //spY *= friction;
    y += spY*friction;
    
    
    //friction += 0.1;
    //println(direction);
    
    if(rad>0) {
        rad -= 0.7;
    }
}