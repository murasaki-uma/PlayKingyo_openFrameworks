//
//  Kingyo.h
//  LeapKingyo06
//
//  Created by 岩城勇磨 on 2015/01/24.
//
//

#ifndef __LeapKingyo06__Kingyo__
#define __LeapKingyo06__Kingyo__


#include <stdio.h>
#include "ofMain.h"



class Kingyo {
public:
    Kingyo(float x_,float y_, float w_, float h_, float sp_, float rad_);
    ~Kingyo();
    
    float x;
    float y;
    ofVec2f pos;
    float w;
    float h;
    ofVec2f movePoint;
    float NextPointX, NextPointY;
    ofVec2f Move;
    float AniCount;
    float tx, ty; // ノイズ値
    
    // Kingyoの行き先の制御
    int countTime, changeTime;
    float KingyoForceX, KingyoForceY;
    
    float rad; // 金魚の尾ひれの中心
    float LeftRad, RightRad;
    float TailSpeed;
    float speed;
    float acceleration; // 加速度
    
    bool isRadAdd;
    bool kingyo_Bones = false;
    bool esa = false;
    bool isMove = false;
    bool isMoving = false;
    bool isGolden;
    
    void display();
    void display(ofVec2f leap_pos);
    //void change();
    void move(ofVec2f f);
    void moveNomal();
    void moveLeap(ofVec2f leap_pos);
    void esaUpdate(float t, float b, float c, float d);
    void changeColor();
    int r, g, b;
    float CP; // 倍率
    
    
    ofVec2f returnVec();
    float returnRad();
    ofVec2f returnForce();
    
    bool ParticleFrag;
    bool Flag();
    bool changePoint;
    
    
        
    
    void start();
    float time, beginning, change, duration;
    
    void end();
    float time2, beginning2, change2, duration2;
    
    void Next();
    float Next_timeX, Next_beginningX, Next_changeX, Next_durationX;
    float Next_timeY, Next_beginningY, Next_changeY, Next_durationY;
    
    
private:
    
    
    ofImage body, left, right, LeftTail, CenterTail, RightTail;
    ofImage g_body, g_left, g_right, g_LeftTail, g_CenterTail, g_RightTail;
    float radius;
};


#endif /* defined(__LeapKingyo06__Kingyo__) */
