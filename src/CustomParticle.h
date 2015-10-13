//
//  CustomParticle.h
//  LeapKingyo07
//
//  Created by 岩城勇磨 on 2015/01/26.
//
//

#ifndef __LeapKingyo07__CustomParticle__
#define __LeapKingyo07__CustomParticle__

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"

class Data {
public:
    ofColor color;
    string  name;
    int		id;
    int r;
    int g;
    int b;
};


// A Custom Particle extedning the box2d circle
class CustomParticle : public ofxBox2dCircle {
    
    
    
public:
    
        
    
    int r = ofRandom(70, 100);
    int g = ofRandom(110, 170);
    int b = ofRandom(90, 130);
    int a = 255;
    
    
    void setupTheCustomData() {
        
        static int colors[] = {0xcae72b, 0xe63b8f, 0x2bb0e7};
        static string abc   = "abcdefghijklmnopqrstuvwxyz";
        
        // we are using a Data pointer because
        // box2d needs to have a pointer not
        // a referance
        setData(new Data());
        Data * theData = (Data*)getData();
        
        theData->id = ofRandom(0, 100);
        theData->name += abc[(int)ofRandom(0, abc.size())];
        theData->color.setHex(colors[(int)ofRandom(0, 3)]);
        
        printf("setting the custom data!\n");
        
    }
    
    void draw() {
        Data* theData = (Data*)getData();
        if(theData) {
            
            /*
            if(r < 200) {
                r++;
            }
            if(g < 100) {
                g++;
            }
            if(b < 200) {
                b++;
            }
            
            if( r == 200 && g == 100 && b == 200) {
                a-=2;
            }
            */

            
            // Evan though we know the data object lets just
            // see how we can get the data out from box2d
            // you would use this when using a contact listener
            // or tapping into box2d's solver.
            
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


class Cp {
public:
    Cp();
    ~Cp();
    int r = ofRandom(20, 80);
    int g = ofRandom(0, 10);
    int b = ofRandom(20, 60);
    int a = 255;
private:
};

#endif /* defined(__LeapKingyo07__CustomParticle__) */
