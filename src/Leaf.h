//
//  Leaf.h
//  LeapKingyo07
//
//  Created by 岩城勇磨 on 2015/01/26.
//
//

#ifndef __LeapKingyo07__Leaf__
#define __LeapKingyo07__Leaf__

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"

class Leaf {
public:
    Leaf(float x, float y, float radius, int NUM);
    ~Leaf();
    void draw();
    void update();
    ofxBox2d                                box2d;			  //	the box2d world
    vector	 <ofPtr<ofxBox2dCircle> >	leaf_childs;
    vector		<ofPtr<ofxBox2dJoint> >		joints;
    float x, y;
    int radius;
    int NUM;
    
private:
};



#endif /* defined(__LeapKingyo07__Leaf__) */
