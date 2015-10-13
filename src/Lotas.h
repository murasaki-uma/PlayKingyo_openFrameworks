//
//  Lotas.h
//  LeapKingyo07
//
//  Created by 岩城勇磨 on 2015/01/26.
//
//

#ifndef __LeapKingyo07__Lotas__
#define __LeapKingyo07__Lotas__

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"

class L_Data {
public:
    ofColor color;
    string  name;
    int		id;
    int r;
    int g;
    int b;
};


// A Lotas Particle extedning the box2d circle
class LotasParticle : public ofxBox2dCircle {
    
    
    
public:
    
    
    
    int r = ofRandom(32, 77);
    int g = ofRandom(130, 145);
    int b = ofRandom(90, 116);
    int a = 255;
    
    
    void setupTheLotasData() {
        
        static int colors[] = {0xcae72b, 0xe63b8f, 0x2bb0e7};
        static string abc   = "abcdefghijklmnopqrstuvwxyz";
        
        // we are using a Data pointer because
        // box2d needs to have a pointer not
        // a referance
        setData(new L_Data());
        L_Data * theData = (L_Data*)getData();
        
        theData->id = ofRandom(0, 100);
        theData->name += abc[(int)ofRandom(0, abc.size())];
        theData->color.setHex(colors[(int)ofRandom(0, 3)]);
        
        printf("setting the Lotas data!\n");
        
    }
    
    void draw() {
        L_Data* theData = (L_Data*)getData();
        if(theData) {
            
            
            float radius = getRadius();
            ofPushMatrix();
            ofTranslate(getPosition());
            ofRotateZ(getRotation());
            ofFill();
            ofSetColor(r, g, b, a);
            ofCircle(0, 0, radius);
            ofCircle(0, 0, radius/4);
            ofSetColor(150, 230, 150);
            ofLine(0, 0, radius, 0);
            
            ofPopMatrix();
        }
    }
    
    //
    
    
};




#endif /* defined(__LeapKingyo07__Lotas__) */
