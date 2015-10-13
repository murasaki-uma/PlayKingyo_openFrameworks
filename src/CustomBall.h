//
//  CustomBall.h
//  example
//
//  Created by 岩城勇磨 on 2015/01/28.
//
//

#ifndef __example__CustomBall__
#define __example__CustomBall__

#include <stdio.h>
#include "ofMain.h"

class CustomBall {
    
public:
    CustomBall();
    
    int r;
    int g;
    int b;
    
    int x;
    int y;
    
    
    int radius;
    int lineWidth;
    int expandRate;
    int timer;
    float FRICTION;
    
    bool dead;
    
    
    void update();
    void draw();
    
};


#endif /* defined(__example__CustomBall__) */
