#include "ofApp.h"

string msg;
int circleNum = 300;

static bool shouldRemove(ofPtr<ofxBox2dBaseShape>shape) {
    return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape.get()->getPosition());
}

int KingyoNUM = 10;
int ParticleTime = 0;
int LEAF_NUM = 10;
int BRANCH_NUM = 1;
int OKE_RAD = 340;
int BUBBLE_RAD = 10;

int Drawcount;
int Lotascount;

float phase;

bool detectionGesture;

ofVec2f leap_pos;
bool drawEsa = false;

float swipPower = 0.05;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0);
    ofSetCircleResolution(150);
    ofEnableSmoothing();
    //ofEnableAlphaBlending();
    ofDisableAntiAliasing();
    
    
    
    leap.open();
    leap.setupGestures();   // we enable our gesture detection here
    
    bMouseForce = false;
    isEsa = false;
    
    box2d.init();
    box2d.enableEvents();   // <-- turn on the event listener
    box2d.setGravity(0, 0);
    box2d.createBounds();
    box2d.setFPS(30.0);
    box2d.registerGrabbing();
    
    // Kingyo ////////////////////////////////////////////////////////////////
    
    for (int i = 0; i < KingyoNUM; i++) {
        //Kingyo(float x_,float y_, float w_, float h_, float sp_, float rad_)
        kingyos.push_back(new Kingyo(ofRandom(ofGetWidth()/2-100, ofGetWidth()/2+100), ofRandom(ofGetHeight()/2-100, ofGetHeight()/2+100), 0, 0, 0.01, ofRandom(-29, 29)));
    }
    
    for (int i = 0; i < KingyoNUM; i++) {
        ofPtr <ofxBox2dCircle> c = ofPtr <ofxBox2dCircle>(new ofxBox2dCircle);
        c.get()->setPhysics(1.0, 0.5, 0.3);
        //ofVec2f Kvec = kingyos[i]->returnVec();
        c.get()->setup(box2d.getWorld(), ofRandom(ofGetWidth()/2-100, ofGetWidth()/2+100), ofRandom(ofGetHeight()/2-150, ofGetHeight()/2+150),5);
        esaBalls.push_back(c);
    }
    
    // BigLotus ////////////////////////////////////////////////////////////////
    // register the listener so that we get the events
    ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
    ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);
    
    // load the 8 sfx soundfile
    //for (int i=0; i<N_SOUNDS; i++) {
    bell.loadSound("bell.mp3");
    bell.setMultiPlay(true);
    bell.setLoop(false);
    //}
    
    // bubble_souds
    bubble01.loadSound("bubble01.mp3");
    bubble02.loadSound("bubble02.mp3");
    bubble03.loadSound("bubble03.mp3");
    
    for (int i = 0; i < 2; i++) {
        ofPtr <ofxBox2dCircle> b = ofPtr <ofxBox2dCircle>(new ofxBox2dCircle);
        b.get()->setPhysics(10, 0.5, 0.3);
        b.get()->setup(box2d.getWorld(), ofRandom(ofGetWidth()/2-100, ofGetWidth()/2+100), ofRandom(ofGetHeight()/2-150, ofGetHeight()/2+150), 120-20*i);
        b.get()->name = "BigLotus";
        
        b.get()->setData(new SoundData());
        SoundData * sd = (SoundData*)b.get()->getData();
        sd->soundID = ofRandom(0, N_SOUNDS);
        sd->bHit	= false;
        
        BigLotus.push_back(b);
    }
    
    BigLotus01.loadImage("BigLotus.png");
    BigLotus02.loadImage("BigLotus.png");
    
    // Branch ////////////////////////////////////////////////////////////////
    for (int i = 0; i < 8; i++) {
        branches.push_back(new Branch);
    }
    
    for (int i = 0; i < 5; i++) {
        branchesLeft.push_back(new Branch);
    }
    
    for (int i = 0; i < 7; i++) {
        branchesTop.push_back(new Branch);
    }
    
    for (int i = 0; i < 3; i++) {
        branchesRight.push_back(new Branch);
    }
    
    
    // bacground ////////////////////////////////////////////////////////////////
    
    ofPtr <ofxBox2dEdge> bedge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    
    for(int i=0; i<100; i++) {
        float t = ofMap(i, 0, 99, 0.0, TWO_PI);
        ofVec3f v(ofGetWidth()/2, ofGetHeight()/2);
        //groundMesh.addVertex(v);
        v.x += cos(t)*OKE_RAD;
        v.y += sin(t)*OKE_RAD;
        bedge.get()->addVertex(v);
        //bedge.get()->setPhysics(3, 0.1, 0.1);
        //bedge.get()->setPhysics(0, 0.001, 10);
    }
    
    
    
    
    bedge.get()->create(box2d.getWorld());
    background_edges.push_back(bedge);

    
    
    
    // Leaf ////////////////////////////////////////////////////////////////
    
    for (int i = 0; i < 5; i++) {
        Drawcount++;
        
        
        //leafs.push_back(new Leaf(mouseX, mouseY, 5, 10));
        float x = ofGetWidth()/2 + ofRandom(-200, 200);
        float y = ofGetHeight()/2 + ofRandom(-200, 200);
        
        for (int i=0; i < LEAF_NUM; i++) {
            if(i == 0) {
                ofPtr<CustomParticle> p = ofPtr<CustomParticle>(new CustomParticle);
                p.get()->setPhysics(10, 0.5, 0.3);
                p.get()->setup(box2d.getWorld(), x, y, ofRandom(4, 9));
                //p.get()->setVelocity(ofRandom(-1, 1), ofRandom(1,-1));
                p.get()->setupTheCustomData();
                particles.push_back(p);
            } else {
                ofPtr<CustomParticle> p = ofPtr<CustomParticle>(new CustomParticle);
                p.get()->setPhysics(10, 0.5, 0.3);
                p.get()->setup(box2d.getWorld(), x+ofRandom(-30, 30), y+ofRandom(-30, 30), ofRandom(6, 10));
                //p.get()->setVelocity(ofRandom(-1, 1), ofRandom(1,-1));
                p.get()->setupTheCustomData();
                particles.push_back(p);
            }
        }
        
        
        
        for (int i=LEAF_NUM*Drawcount; i>particles.size()-LEAF_NUM; i-=LEAF_NUM) {
            //cout << i << endl;
            
            if(i != 0) {
                for (int j = 1; j < LEAF_NUM; j++) {
                    //cout << j << endl;
                    ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
                    
                    // if this is the first point connect to the top anchor.
                    
                    int size = particles.size();
                    joint.get()->setup(box2d.getWorld(), particles[i-1-j].get()->body, particles[i-1].get()->body);
                    joint.get()->setDamping(1.0);
                    joint.get()->setFrequency(10.0);
                    
                    joint.get()->setLength(25);
                    leafs_joints.push_back(joint);
                    
                }
            }
            
        }
    }
    
    
    
    init();
    
    
    nCurveVertices = 7;
    
    curveVertices[0].x = 326;
    curveVertices[0].y = 209;
    curveVertices[1].x = 306;
    curveVertices[1].y = 279;
    curveVertices[2].x = 265;
    curveVertices[2].y = 331;
    curveVertices[3].x = 304;
    curveVertices[3].y = 383;
    curveVertices[4].x = 374;
    curveVertices[4].y = 383;
    curveVertices[5].x = 418;
    curveVertices[5].y = 309;
    curveVertices[6].x = 345;
    curveVertices[6].y = 279;
    
    for (int i = 0; i < nCurveVertices; i++){
        curveVertices[i].bOver 			= false;
        curveVertices[i].bBeingDragged 	= false;
        curveVertices[i].radius = 4;
    }
    
    

}


//--------------------------------------------------------------
void ofApp::init(){
    time 		= 0;
    beginning	= 200;
    change 		= -100;
    duration 	= 1000;
}

//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {
    
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
    
}


//--------------------------------------------------------------
vector <ofPoint> ofApp::loadPoints(string file) {
    vector <ofPoint> pts;
    vector <string>  ptsStr = ofSplitString(ofBufferFromFile(file).getText(), ",");
    for (int i=0; i<ptsStr.size(); i+=2) {
        float x = ofToFloat(ptsStr[i]);
        float y = ofToFloat(ptsStr[i+1]);
        pts.push_back(ofPoint(x, y));
    }
    return pts;
}


//--------------------------------------------------------------
void ofApp::update()
{
    leap.updateGestures();  // check for gesture updates
    
    
    isEsa = false;
    //cout << isEsa << endl;
    
    // 衝突判定
    ofVec2f constPos01 = BigLotus[0]->getPosition();
    ofVec2f constPos02 = BigLotus[1]->getPosition();
    
    if ( (constPos01.x-constPos02.x)*(constPos01.x-constPos02.x) + (constPos01.y-constPos02.y)*(constPos01.y-constPos02.y) <= (BigLotus[0]->getRadius()+BigLotus[1]->getRadius())*(BigLotus[0]->getRadius()+BigLotus[1]->getRadius()) ) {
        if(!bell.getIsPlaying()) {
            bell.play();
        }
        
    }
    
    // CustomBall
    for (int i = 0; i < leap_circles.size(); i++ ) {
        leap_circles[i].update();
        if(leap_circles[i].dead) {
            leap_circles.erase( leap_circles.begin()+i );
        }
    }
    leap_time++; // CustomBall timeUpdate
    
    
    simpleHands = leap.getSimpleHands();
    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        
        if(leap_time%3 == 0) {
            
            
            sampleCircle.x = leap_pos.x;
            sampleCircle.y = leap_pos.y;
            isEsa = true;
            
        }
        
        
        if( (ofGetWidth()/2 - leap_pos.x)*(ofGetWidth()/2 - leap_pos.x) + (ofGetHeight()/2 - leap_pos.y)*(ofGetHeight()/2 -     leap_pos.y) <= (OKE_RAD-15)*(OKE_RAD-15) ) {
            leap_circles.push_back(sampleCircle);
            detectionGesture = true;
            cout << detectionGesture << endl;
        } else {
            detectionGesture = false;
        }
        
        
        
        
        
        
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
        
        for(int i = 0; i < simpleHands.size(); i++){
            for (int f=0; f<5; f++) {
                int id = simpleHands[i].fingers[ fingerTypes[f] ].id;
                ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp; // metacarpal
                ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip; // proximal
                ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip; // distal
                ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip; // fingertip
                fingersFound.push_back(id);
                leap_pos = simpleHands[i].handPos;
                leap_pos.x = ofMap(leap_pos.x, -500, 500, 0, ofGetWidth());
                leap_pos.y = ofMap(leap_pos.y, -400, 300, ofGetHeight(), 0);
                
            }
        }
    }
    
    box2d.update();
    ParticleTime ++;
    
    
    
    for (int i = 0; i < kingyos.size(); i++) {
        ofVec2f f = esaBalls[i]->getPosition();
        kingyos[i]->move(f);
        //kingyos[i]->changeColor();
    }
    
    
    
    for (int j = 0; j < particles.size(); j++) {
        if( particles[j]->a == 0) {
            particles.erase(particles.begin()+j);
        }
    }
    
    if(leap.iGestures == 2 && detectionGesture) {
        kingyos.push_back(new Kingyo(leap_pos.x, leap_pos.y, 0, 0, 0.01, ofRandom(-29, 29)));
        //kingyos.pop_back();
        //delete [] kingyos[0];
        esaBalls.erase(esaBalls.begin() + 0);
        kingyos.erase(kingyos.begin() + 0);
        
        ofPtr <ofxBox2dCircle> c = ofPtr <ofxBox2dCircle>(new ofxBox2dCircle);
        c.get()->setPhysics(1.0, 0.5, 0.3);
        //ofVec2f Kvec = kingyos[i]->returnVec();
        c.get()->setup(box2d.getWorld(), ofRandom(ofGetWidth()/2-100, ofGetWidth()/2+100), ofRandom(ofGetHeight()/2-150, ofGetHeight()/2+150),5);
        esaBalls.push_back(c);
        
        for(int i=0; i<9; i++) {
            float t = ofMap(i, 0, 9, 0.0, TWO_PI);
            
            ofVec2f v(leap_pos);
            v.x += cos(t)*BUBBLE_RAD;
            v.y += sin(t)*BUBBLE_RAD;
            int direction = -1;
            
            bubbles.push_back(new Bubble( leap_pos.x+cos(t)*BUBBLE_RAD, leap_pos.y+sin(t)*BUBBLE_RAD, ofRandom(15, 20), cos(t), sin(t), direction ));
            
            cout << "bubble_x :" << leap_pos.x+cos(t)*BUBBLE_RAD << endl;
        }
        
        // 水の音
        int b = ofRandom(1, 4);
        cout << "b :" << b << endl;
        
        switch (b) {
            case 1:
                bubble01.play();
                break;
                
            case 2:
                bubble02.play();
                break;
                
            case 3:
                bubble03.play();
                break;
        }
        leap.iGestures = 0;
        
    }
    
    if(leap.iGestures == 3){
        
        for (int i = 0; i < BigLotus.size(); i++) {
            BigLotus[i]->addForce(ofVec2f(ofMap(leap_pos.x, 0, ofGetWeekday(), 400, 600), 0), swipPower);
            BigLotus[i]->addRepulsionForce(leap_pos, 5);
            //cout << "Right" << endl;
            
        }
        //leap.iGestures = 0;
    }
    
    
    if(leap.iGestures == 4){
        
        for (int i = 0; i < BigLotus.size(); i++) {
            BigLotus[i]->addForce(ofVec2f(ofMap(leap_pos.x, 0, ofGetWeekday(), -400, -600), 0), swipPower);
            BigLotus[i]->addRepulsionForce(leap_pos, 5);
            //cout << "Right" << endl;
            
        }
        //leap.iGestures = 0;
    }
    
    
    if(leap.iGestures == 5){
        
        for (int i = 0; i < BigLotus.size(); i++) {
            BigLotus[i]->addForce(ofVec2f(0, ofMap(leap_pos.y, 0, ofGetHeight(), 400, 500)), 10);
            BigLotus[i]->addRepulsionForce(leap_pos, 5);
            //cout << "Right" << endl;
            
        }
        //leap.iGestures = 0;
    }
    
    if(leap.iGestures == 6){
        
        for (
             int i = 0; i < BigLotus.size(); i++) {
            BigLotus[i]->addForce(ofVec2f(0, ofMap(leap_pos.y, 0, ofGetHeight(), -400, -500)), 10);
            BigLotus[i]->addRepulsionForce(leap_pos, 5);
            //cout << "Right" << endl;
            
        }
        //leap.iGestures = 0;
    }


    
    
    
    switch (leap.iGestures) {
        case 1:
            msg = "Screen Tap";
            //msg += "\nPosition: "+ofToString(leap.screenTapPosition);
            break;
            
        case 2:
            msg = "Key Tap";
            //msg += "\nPosition: " + ofToString(leap.keyTapPosition);
            break;
            
        case 3:
            msg = "Swipe Right";
            
            break;
            
        case 4:
            msg = "Swipe Left";
            
            leap.iGestures = 0;
            break;
            
        case 5:
            msg = "Swipe Down";
            //msg += "\nSwipe Speed mm/s: " + ofToString(leap.swipeSpeed) + "\nDuration sec's: "+ofToString(leap.swipeDurationSeconds);
            break;
            
        case 6:
            msg = "Swipe Up";
            //msg += "\nSwipe Speed mm/s: " + ofToString(leap.swipeSpeed) + "\nDuration sec's: "+ofToString(leap.swipeDurationSeconds);
            break;
            
        case 7:
            msg = "Swipe Forward";
            //msg += "\nSwipe Speed mm/s: " + ofToString(leap.swipeSpeed) + "\nDuration sec's: "+ofToString(leap.swipeDurationSeconds);
            break;
            
        case 8:
            msg = "Swipe Backwards";
            //msg += "\nSwipe Speed mm/s: " + ofToString(leap.swipeSpeed) + "\nDuration sec's: "+ofToString(leap.swipeDurationSeconds);
            break;
            
        case 9:
            msg = "Circle Left";
            //msg += "\nCircle Radius: " + ofToString(leap.circleRadius) + "\nCircle Center: "+ofToString(leap.circleCenter);
            break;
            
        case 10:
            msg = "Circle Right";
            //msg += "\nCircle Radius: " + ofToString(leap.circleRadius) + "\nCircle Center: "+ofToString(leap.circleCenter);
            break;
            
        default:
            msg = "Waiting for hand movement...";
            break;
    }
    
    for (int i = 0; i < kingyos.size(); i++) {
        ofSetColor(255, 200, 200);
        //esaBalls[i].get()->update();
        
        ofVec2f a = kingyos[i]->returnVec();
        if (isEsa) {
            
            if (detectionGesture) {
                //esaBalls[i]->addAttractionPoint(leap_pos, 0.08);
                //esaBalls[i]->addRepulsionForce(leap_pos, 0.03);
                //esaBalls[i]->addForce(ofVec2f(leap_pos.x) - kingyos[i]->pos.x, ofVec2f(leap_pos.y) - kingyos[i]->pos.y);
                esaBalls[i]->addAttractionPoint(leap_pos, 0.05);
            }
            
            
        } else {
            esaBalls[i].get()->addAttractionPoint(a, 0.001);
        }
    }
    
    
    
    for (int i = 0; i < rocks.size(); i++) {
        rocks[i].get()->update();
    }
    
    
    BigLotusPos01 = BigLotus[0].get()->getPosition();
    BigLotusPos02 = BigLotus[1].get()->getPosition();
    
    
    for (int i = 0; i < bubbles.size(); i++) {
        //bubbles[i]->display();
        bubbles[i]->move();
        
        if(bubbles[i]->rad < 0) {
            bubbles.erase(bubbles.begin() + i);
            //delete [] bubbles[i];
        }
    }
    
    leap.markFrameAsOld();	//IMPORTANT! - tell ofxLeapMotion that the frame is no longer new.

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /* Leap iGesture Key
     --------------------------------
     1 = Screen Tap
     2 = Key Tap
     3 = Swipe Right
     4 = Swipe Left
     5 = Swipe Down
     6 = Swipe Up
     7 = Swipe Forward
     8 = Swipe Backward (towards yourself)
     9 = Circle Left (counter-clockwise)
     10 = Circle Right (clockwise)
     --------------------------------
     */
    
    bg.draw(0, 0, ofGetWidth(), ofGetHeight());
    for (int i = 0; i < leap_circles.size(); i++ ) {
        
        leap_circles[i].draw();
    }
    
    
    // Kingyo ////////////////////////////////////////////////////////////////
    //ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    
    
    
    // Custam Particle ///////////////////////////////////////////////////////
    
    for (int i = 0; i < kingyos.size(); i++) {
        
        kingyos[i]->display();
        if(drawEsa) {
            esaBalls[i].get()->draw();
        }
    }
    
    /*for(int i=0; i<rockJoints.size(); i++) {
     rockJoints[i].get()->draw();
     }*/
    
    for (int i=0; i<edges.size(); i++) {
        ofSetCircleResolution(255);
        edges[i].get()->draw();
    }
    
    for (int i = 0; i < rocks.size(); i++) {
        rocks[i].get()->draw();
    }
    
    
    /*for(int i=0; i<lotas.size(); i++) {
     lotas[i].get()->draw();
     }*/
    
    for(int i=0; i<particles.size(); i++) {
        particles[i].get()->draw();
    }
    
    
    // Bubble /////////////////////////////////////////////////////////
    /*
     for (int i = 0; i < bubbles.size(); i++) {
     //bubbles[i]->display();
     bubbles[i]->move();
     
     if(bubbles[i]->rad < 0) {
     delete bubbles[i];
     }
     }*/
    
    
    for (int i = 0; i < bubbles.size(); i++) {
        bubbles[i]->display();
    }
    
    
    
    
    // branches ///////////////////////////////////////////////////////
    
    for (int i = 0; i < branches.size(); i++) {
        
        float t = ofMap(i, 0, branches.size(), 0.0, TWO_PI/4);
        ofVec3f v(ofGetWidth()/2, ofGetHeight()/2);
        //groundMesh.addVertex(v);
        v.x += cos(t)*OKE_RAD;
        v.y += sin(t)*OKE_RAD;
        
        float rad = ofMap(t, 0, TWO_PI/4, 0, 90);
        
        cfm = ofVec2f(-10-i, -i);
        
        
        ofPushMatrix();
        ofTranslate(v.x+cfm.x, v.y+cfm.y);
        ofRotate(branches[i]->startAngle*PI/180 + rad);
        branches[i]->branch(branches[i]->segments);
        ofPopMatrix();
    }
    
    for (int i = 0; i < branchesLeft.size(); i++) {
        
        float t = ofMap(i, 0, branchesLeft.size(), TWO_PI/4, TWO_PI/2);
        ofVec3f v(ofGetWidth()/2, ofGetHeight()/2);
        //groundMesh.addVertex(v);
        v.x += cos(t)*OKE_RAD;
        v.y += sin(t)*OKE_RAD;
        
        float rad = ofMap(t, TWO_PI/4, TWO_PI/2, 90, 180);
        
        cfm = ofVec2f(0, -15-i);
        
        ofPushMatrix();
        ofTranslate(v.x+cfm.x, v.y+cfm.y);
        ofRotate(branchesLeft[i]->startAngle*PI/180 +rad);
        branchesLeft[i]->branch(branchesLeft[i]->segments);
        ofPopMatrix();
    }
    
    for (int i = 0; i < branchesRight.size(); i++) {
        float t = ofMap(i, 0, branchesRight.size(), TWO_PI/2, TWO_PI/4*3);
        ofVec3f v(ofGetWidth()/2, ofGetHeight()/2);
        //groundMesh.addVertex(v);
        v.x += cos(t)*OKE_RAD;
        v.y += sin(t)*OKE_RAD;
        
        float rad = ofMap(t, TWO_PI/2, TWO_PI/4*3, 180, 270);
        
        cfm = ofVec2f(10, 0);
        
        ofPushMatrix();
        ofTranslate(v.x+cfm.x, v.y+cfm.y);
        ofRotate(branchesRight[i]->startAngle*PI/180 +rad);
        branchesRight[i]->branch(branchesRight[i]->segments);
        ofPopMatrix();
    }
    
    for (int i = 0; i < branchesTop.size(); i++) {
        float t = ofMap(i, 0, branchesTop.size(), TWO_PI/4*3, TWO_PI);
        ofVec3f v(ofGetWidth()/2, ofGetHeight()/2);
        //groundMesh.addVertex(v);
        v.x += cos(t)*OKE_RAD;
        v.y += sin(t)*OKE_RAD;
        
        float rad = ofMap(t, TWO_PI/4*3, TWO_PI, 270, 360);
        
        cfm = ofVec2f(0, 20);
        
        ofPushMatrix();
        ofTranslate(v.x+cfm.x, v.y+cfm.y);
        ofRotate(branchesTop[i]->startAngle*PI/180 + rad);
        branchesTop[i]->branch(branchesTop[i]->segments);
        ofPopMatrix();
    }
    
    
    
    
    
    
    for (int i = 0; i < BigLotus.size(); i++) {
        //BigLotus[i].get()->draw();
    }
    
    //ofSetColor(30);
    ofEnableAlphaBlending();
    ofPushMatrix();
    
    ofTranslate(BigLotusPos01.x, BigLotusPos01.y);
    ofRotate(BigLotus[0].get()->getRotation());
    BigLotus01.draw(-120, -120, 240, 240);
    ofPopMatrix();
    
    ofPushMatrix();
    
    ofTranslate(BigLotusPos02.x, BigLotusPos02.y);
    ofRotate(BigLotus[1].get()->getRotation());
    BigLotus02.draw(-100, -100, 200 ,200);
    ofPopMatrix();
    
    
    for (int i=0; i<background_edges.size(); i++) {
        ofSetHexColor(0x444342);
        ofNoFill();
        //background_edges[i].get()->draw();
    }

    
    
    
    
    ofDrawBitmapString(msg, 20, 20);  // let's draw our message to the screen
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::DrawLine(ofVec2f P1, ofVec2f P2, int r, int g, int b) {
    ofSetColor(r, g, b);
    ofLine(P1, P2);
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}

//--------------------------------------------------------------
void ofApp::exit(){
    leap.close();  // let's close down Leap and kill the controller
}
