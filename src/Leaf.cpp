//
//  Leaf.cpp
//  LeapKingyo07
//
//  Created by 岩城勇磨 on 2015/01/26.
//
//

#include "Leaf.h"
//#include "ofApp.h"

Leaf::Leaf(float x, float y, float radius, int NUM) {
    
    
    box2d.init();
    box2d.enableEvents();   // <-- turn on the event listener
    box2d.setGravity(0, 0);
    box2d.createBounds();
    box2d.setFPS(30.0);
    box2d.registerGrabbing();
    
    
    
    for (int i = 0; i < NUM; i++) {
        if(i == 1) {
            ofPtr <ofxBox2dCircle> c = ofPtr <ofxBox2dCircle>(new ofxBox2dCircle);
            c.get()->setPhysics(0.8, 0.5, 0.9);
            c.get()->setup(box2d.getWorld(), x, y, ofRandom(4, 5));
            
            /*c.get()->setData(new SoundData());
            SoundData * sd = (SoundData*)c.get()->getData();
            sd->soundID = ofRandom(0, N_SOUNDS);
            sd->bHit	= false;*/
        
            leaf_childs.push_back(c);
        } else {
            ofPtr <ofxBox2dCircle> c = ofPtr <ofxBox2dCircle>(new ofxBox2dCircle);
            c.get()->setPhysics(0.8, 0.5, 0.9);
            
            c.get()->setup(box2d.getWorld(), x+ofRandom(-30, 30), y+ofRandom(-30, 30), ofRandom(4, 10));
            
            /*c.get()->setData(new SoundData());
             SoundData * sd = (SoundData*)c.get()->getData();
             sd->soundID = ofRandom(0, N_SOUNDS);
             sd->bHit	= false;*/
            
            leaf_childs.push_back(c);
        }
    }
    
    for (int i=1; i<leaf_childs.size(); i++) {
        
        ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
        
        // if this is the first point connect to the top anchor.
        
        joint.get()->setup(box2d.getWorld(), leaf_childs[0].get()->body, leaf_childs[i].get()->body);
        joint.get()->setDamping(1.0);
        joint.get()->setFrequency(10.0);
        
        joint.get()->setLength(20);
        joints.push_back(joint);
    }
}

void Leaf::update() {
    box2d.update();
}

void Leaf::draw() {
    
    for(int i=0; i<leaf_childs.size(); i++) {
        ofFill();
        ofSetColor(30, 200, 100);
        
        leaf_childs[i].get()->draw();
    }
    
}