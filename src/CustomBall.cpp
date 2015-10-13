//
//  CustomBall.cpp
//  example
//
//  Created by 岩城勇磨 on 2015/01/28.
//
//

#include "CustomBall.h"

CustomBall::CustomBall() {
    
    r = ofRandom(60, 110);
    g = ofRandom(160, 210);
    b = ofRandom(180, 230);
    
    radius = ofRandom(5, 10);
    lineWidth = ofRandom(4);
    expandRate = 10;
    
    dead = false;
    timer = 0;
    FRICTION = 0.999;
    
}

void CustomBall::update() {
    expandRate *= FRICTION;
    radius += expandRate/4;
    
    r += 1;
    g += 1;
    b += 1;
    
    //timer -= 1;
    
    if (expandRate < 0.5) {
        dead = true;
    }
    
}

void CustomBall::draw() {
    ofSetColor(r, g, b, 100);
    ofNoFill();
    ofSetLineWidth(lineWidth);
    ofCircle (x, y, radius);
}
