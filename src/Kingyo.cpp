//
//  Kingyo.cpp
//  LeapKingyo06
//
//  Created by 岩城勇磨 on 2015/01/24.
//
//

#include "Kingyo.h"
#include "ofApp.h"


#include "Quad.h"
#include "Quart.h"
#include "Quint.h"
#include "Sine.h"
#include "Linear.h"
#include "Expo.h"
#include "Elastic.h"
#include "Cubic.h"
#include "Circ.h"
#include "Bounce.h"
#include "Back.h"

#include <math.h>

Kingyo::Kingyo(float x_,float y_, float w_, float h_, float sp_, float rad_)
{
    pos.x = x_;
    pos.y = y_;
    w = w_;
    h = h_;
    rad = rad_;
    tx = 0;
    ty = 0;
    speed = sp_;
    acceleration = 0.9;
    isRadAdd = ( rad < 0 ) ? true : false;
    AniCount = 0.0;
    
    changeTime = 90;
    KingyoForceX = ofRandom(ofGetWidth());
    KingyoForceY = ofRandom(ofGetHeight());
    
    body.loadImage("body.png");
    left.loadImage("left.png");
    right.loadImage("right.png");
    LeftTail.loadImage("LeftTail.png");
    RightTail.loadImage("RightTail.png");
    CenterTail.loadImage("Tail.png");
    
    g_body.loadImage("g_body.png");
    g_left.loadImage("g_left.png");
    g_right.loadImage("g_right.png");
    g_LeftTail.loadImage("g_LeftTail.png");
    g_RightTail.loadImage("g_RightTail.png");
    g_CenterTail.loadImage("g_Tail.png");
    
    TailSpeed = ofRandom(0.2, 0.5);
    
    float golden = ofRandom(100);
    
    if(golden < 5) {
        isGolden = true;
    } else {
        isGolden = false;
    }
    
    movePoint = ofVec2f( ofRandom(ofGetWidth()),  ofRandom(ofGetHeight()) );
    
    ParticleFrag = false;
    
    start();
    end();
    Next();
    changePoint = false;
    
    CP = 2;
    
    r = ofRandom(180, 240);
    g = ofRandom(60, 160);
    b = ofRandom(60, 164);
    
    
}

Kingyo::~Kingyo()
{
    
}

bool Kingyo::Flag() {
    return ParticleFrag;
}




void Kingyo::start(){
    
    time 		= 0.0;
    beginning	= 30;
    change 		= -61;
    duration 	= 20;
    
}


void Kingyo::end(){
    
    time2       = 0.0;
    beginning2	= -30;
    change2 	= 61;
    
}

void Kingyo::Next()
{
    Next_timeX = 999;
    Next_beginningX = movePoint.x;
    Next_changeX = 0;
    Next_durationX = 500;
    
    Next_timeY = 999;
    Next_beginningY = movePoint.y;
    Next_changeY = 0;
    Next_durationY = 500;
}

void Kingyo::move(ofVec2f f) {
    
    
    countTime++;
    
    if(rad > 30){
        isRadAdd = true;
        time2 = 0;
        duration+=2;
        
    } else if(rad < -30){
        isRadAdd = false;
        time = 0;
        duration+=2;
        
    }
    
    if(duration > 34) {
        duration = 20;
    }
    
    if(time2 == 0 && rad > -30) {
        rad = -31;
    }
    
    if(time == 0 && rad < 30) {
        rad = 31;
    }
    
    
    
    
    /*cout << "rad : " << rad << endl;
    cout << "time : " << time << endl;
    cout << "time2 : " << time2 << endl;*/
    
    
    // 中心尾びれの回転
    if(isRadAdd) {
        
        if (time < duration) time++;
        rad = Quart::easeInOut (time, beginning, change, duration);
        LeftRad = rad;
        RightRad = rad;
        
    } else {
        
        if (time2 < duration) time2++;
        rad = Quart::easeInOut (time2, beginning2, change2, duration);
        LeftRad = rad;
        RightRad = rad;
    }
    
    
    
    movePoint = f;
    
    
    
    Move = (movePoint - pos) * speed;
    pos += Move * acceleration;
    
    
}

ofVec2f Kingyo::returnVec() {
    
    if(countTime > changeTime) {
        KingyoForceX = ofRandom(ofGetWidth());
        KingyoForceY = ofRandom(ofGetHeight());
        countTime = 0;
        
    }
    return ofVec2f(KingyoForceX, KingyoForceY);
}

float Kingyo::returnRad() {
    return atan2(movePoint.y - pos.y, movePoint.x - pos.x) * 180.0 / PI + 95;
}

ofVec2f Kingyo::returnForce() {
    return Move * acceleration;
}




void Kingyo::moveNomal() {
    
    
    

    
    
    
}

void Kingyo::moveLeap(ofVec2f leap_pos) {
    

}

void Kingyo::changeColor() {
    /*r = 227;
    g = 176;
    b = 177;
    
    235 190 50
    */
    r = ofMap(pos.x, ofGetWidth()/2-190, ofGetWidth()/2+190, 100, 200);
    g = ofMap(pos.x, ofGetWidth()/2-190, ofGetWidth()/2+190, 80, 120);
    b = ofMap(pos.x, ofGetWidth()/2-190, ofGetWidth()/2+190, 140, 190);
    
}



void Kingyo::display()
{
    
    ofSetColor(r, g, b);
    if (isGolden) ofSetColor(254, 247, 200);
    ofPushMatrix();
    
    
    // 移動先のポイント /////////////////////////////////////////////////////////////////////
    if(esa){
        ofCircle(movePoint.x, movePoint.y, 5);
    }
    
    // 金魚の表示//// /////////////////////////////////////////////////////////////////////
    ofTranslate(pos.x, pos.y);
    ofRotate(atan2(movePoint.y - pos.y, movePoint.x - pos.x) * 180.0 / PI + 95);
    
        
    ofPushMatrix();
    // bodyの回転軸を移動
    ofTranslate(0/CP, 40/CP);
    // 回転軸の表示
    if(kingyo_Bones){
        ofEllipse(0/CP, 0/CP, 5/CP, 5/CP);
    }
    
    // 画像の表示
    if (isGolden) g_body.draw(-21/CP, -83/CP, 43/CP, 83/CP);
    if (!isGolden) body.draw(-21/CP, -83/CP, 43/CP, 83/CP);
    
    ofPopMatrix();
    
    ///////////////////////// 左ヒレ
    ofPushMatrix();
    // ヒレの回転軸を移動
    ofTranslate(-20/CP, -10/CP);
    
    // 骨組みの表示
    if(kingyo_Bones){ ofEllipse(0/CP, 0/CP, 5/CP, 5/CP); }
    //rotate(radians(0));
    // image(名前, bodyの回転軸＋ヒレの回転軸の差分, bodyの回転軸＋ヒレの回転軸の差分, 位置, 位置);
    if (isGolden) g_left.draw(-15/CP, 0/CP, 13/CP, 18/CP);
    if (!isGolden) left.draw(-15/CP, 0/CP, 13/CP, 18/CP);
    ofPopMatrix();
    
    
    
    ///////////////////////// 右ヒレ
    ofPushMatrix();
    ofTranslate(20/CP, -10/CP);
    
    // 骨組みの表示
    if(kingyo_Bones){ ofEllipse(0/CP, 0/CP, 5/CP, 5/CP); }
    //rotate(radians(0));
    if (isGolden) g_right.draw(3/CP, 0/CP, 13/CP, 18/CP);
    if (!isGolden) right.draw(3/CP, 0/CP, 13/CP, 18/CP);
    ofPopMatrix();
    
    
    // bodyのpopMatrix
    
    
    
    
    ///////////////////////// 尾びれ
    // 左
    ofPushMatrix();
    ofTranslate(0/CP, 45/CP);
    if(kingyo_Bones){ ofEllipse(0/CP, 0/CP, 5/CP, 5/CP); }
    ofRotate(LeftRad);
    ofEnableAlphaBlending();
    if (isGolden) g_LeftTail.draw(-40/CP, 0/CP, 33/CP, 29/CP);
    if (!isGolden) LeftTail.draw(-40/CP, 0/CP, 33/CP, 29/CP);
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(0/CP, 45/CP);
    if(kingyo_Bones){ ofEllipse(0, 0, 5, 5); }
    ofRotate(RightRad);
    ofEnableAlphaBlending();
    if (isGolden) g_RightTail.draw(5/CP, 0/CP, 33/CP, 29/CP);
    if (!isGolden) RightTail.draw(5/CP, 0/CP, 33/CP, 29/CP);
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(0/CP, 45/CP);
    if(kingyo_Bones){ ofEllipse(0/CP, 0/CP, 5/CP, 5/CP); }
    ofRotate(rad);
    if (isGolden) g_CenterTail.draw(-12/CP, 0/CP, 24/CP, 69/CP);
    if (!isGolden) CenterTail.draw(-12/CP, 0/CP, 24/CP, 69/CP);
    ofPopMatrix();
    
    ofPopMatrix();
    
}





