#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"
#include "CustomBall.h"
#include "ofxBox2d.h"
#include "Kingyo.h"
#include "Leaf.h"
#include "CustomParticle.h"
#include "Lotas.h"
#include "Branch.h"
#include "Bubble.h"

typedef struct {
    
    float 	x;
    float 	y;
    bool 	bBeingDragged;
    bool 	bOver;
    float 	radius;
    
}draggableVertex;


#define N_SOUNDS 1

class SoundData {
public:
    int	 soundID;
    bool bHit;
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void exit();
    void leapGesture();
    
    ofxLeapMotion leap;
    vector <ofxLeapMotionSimpleHand> simpleHands;
    
    vector <int> fingersFound;
    ofEasyCam cam;
    
    vector <CustomBall> leap_circles;
    int leap_time;
    
    
    
    
    // Poly ////////////////////////////////////////////////////////
    float                                   px, py;
    bool                                    bDrawLines;
    bool                                    bMouseForce;
    ofPolyline                              drawing;		  //	we draw with this first
    ofxBox2dEdge                            edgeLine;		  //	the box2d edge/line shape (min 2 points)
    
    
    // when the ball hits we play this sound
    ofSoundPlayer  sound[N_SOUNDS];
    ofxBox2d                                box2d;			  //	the box2d world
    vector		<ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
    
    
    vector <ofPtr<ofxBox2dEdge> >       background_edges;
    ofVec2f cfm;
    
    
    // Kingyo ////////////////////////////////////////////////////////
    vector <ofPoint> loadPoints(string file);
    bool                                breakupIntoTriangles;
    ofPolyline                          shape;
    vector <ofPtr<ofxBox2dPolygon> >	polyShapes;
    bool isEsa;
    vector		<ofPtr<ofxBox2dCircle>  >		esaBalls;
    vector <ofPtr<CustomParticle> >		CustomEsaBalls;
    
    
    
    // Kingyo ////////////////////////////////////////////////////////
    vector<Kingyo *> kingyos;
    
    void init();
    float time, beginning, change, duration;
    

    
    // Rock /////////////////////////////////////////////////
    vector		<ofPtr<ofxBox2dCircle> >	rocks;
    vector		<ofPtr<ofxBox2dJoint> >		rockJoints;
    vector <ofPtr<ofxBox2dEdge> >           edges;
    
    // Ripple ////////////////////////////////////////////////////////
    vector <Branch *> branches;            // branch
    vector <Branch *> branchesLeft;            // Left
    vector <Branch *> branchesRight;           // Right
    vector <Branch *> branchesTop;             // Top
    
    // Ripple ////////////////////////////////////////////////////////
    //vector<Ripple *> ripples;
    
    // CustomParticle ////////////////////////////////////////////////
    vector <ofPtr<CustomParticle> >		particles;
    vector		<ofPtr<ofxBox2dCircle>  >		cps;
    void DrawLine(ofVec2f P1, ofVec2f P2, int r, int g, int b);
    
    // 音がでるやつ
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
    ofSoundPlayer  bell;
    
    ofImage BigLotus01, BigLotus02;
    vector <ofPtr<ofxBox2dCircle>  >		BigLotus;
    ofVec2f BigLotusPos01, BigLotusPos02;
    
    // Leafe /////////////////////////////////////////////////
    vector<Leaf *>                          leafs;
    vector		<ofPtr<ofxBox2dJoint> >		leafs_joints;			  //	joints\
    
    vector      <ofPtr<LotasParticle> >		lotas;
    vector		<ofPtr<ofxBox2dJoint> >		lotas_joints;			  //	joints\
    
    int nCurveVertices;
    draggableVertex curveVertices[7];
    draggableVertex bezierVertices[4];
    
    
    // Leafe /////////////////////////////////////////////////
    vector<Bubble *>                        bubbles;
    //vector<Bubble *>                        bubbles;
    ofSoundPlayer                           bubble01, bubble02, bubble03;
    
    CustomBall sampleCircle;
    
    ofImage bg;
    
    		
};
