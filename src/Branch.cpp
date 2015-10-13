//
//  branch.cpp
//  LeapKingyo28
//
//  Created by 岩城勇磨 on 2015/02/01.
//
//

#include "branch.h"

Branch::Branch() {
    segments = ofRandom(40, 0);
    startAngle = ofRandom(-30, 30);
    t_x = ofRandom(ofGetWidth());
    t_y = ofRandom(ofGetHeight());
}

void Branch::branch(float len) {
    
    float t = ofMap(len, 1, 160, 1, 8);
    theta = sin(len+num) * 3;
    ofSetLineWidth(t);
    
    ofSetColor(32,145,97);
    ofLine(0, 0, 0, -len);
    ofLine(0, 0, 20, -30);
    ofLine(0, 0, -20, -30);
    //ofSetColor(200, 200, 200);
    ofEllipse(0, 0, 3, 3);
    
    ofTranslate(0, -len);
    len *= 0.80;
    if(len > 2){
        ofPushMatrix();
        ofRotate(-10+theta);
        branch(len);
        ofPopMatrix();
        
        //ofPushMatrix();
        //ofRotate(20-theta);
        //branch(len);
        //ofPopMatrix();
    }else{
        ofEllipse(0, 0, 3, 3);
    }
    num += 0.001;
}
