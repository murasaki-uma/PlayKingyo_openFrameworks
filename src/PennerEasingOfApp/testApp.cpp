#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	 
	init();
}

//--------------------------------------------------------------
void testApp::init(){
	
	time 		= 0;
	beginning	= 0;
	change 		= 500;
	duration 	= 1000;
	
}


//--------------------------------------------------------------
void testApp::update(){

	if (time < duration) time++;

}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0,0,0);	
	
	ofSetColor(0xa0f0a0);
	ofRect(	Quad::easeIn    (time, beginning, change, duration),0 ,10,10);
	ofRect(	Quad::easeOut   (time, beginning, change, duration),10,10,10);
	ofRect(	Quad::easeInOut (time, beginning, change, duration),20,10,10);
	
	ofSetColor(0xf00000);
	ofRect(	Quart::easeIn    (time, beginning, change, duration),30,10,10);
	ofRect(	Quart::easeOut   (time, beginning, change, duration),40,10,10);
	ofRect(	Quart::easeInOut (time, beginning, change, duration),50,10,10);
	
	ofSetColor(0x00f000);
	ofRect(	Quint::easeIn    (time, beginning, change, duration),60,10,10);
	ofRect(	Quint::easeOut   (time, beginning, change, duration),70,10,10);
	ofRect(	Quint::easeInOut (time, beginning, change, duration),80,10,10);

	ofSetColor(0x0000f0);
	ofRect(	Sine::easeIn    (time, beginning, change, duration),90,10,10);
	ofRect(	Sine::easeOut   (time, beginning, change, duration),100,10,10);
	ofRect(	Sine::easeInOut (time, beginning, change, duration),110,10,10);
	
	ofSetColor(0xf0f000);
	ofRect(	Linear::easeIn    (time, beginning, change, duration),120,10,10);
	ofRect(	Linear::easeOut   (time, beginning, change, duration),130,10,10);
	ofRect(	Linear::easeInOut (time, beginning, change, duration),140,10,10);
	
	ofSetColor(0x00f0f0);
	ofRect(	Expo::easeIn    (time, beginning, change, duration),150,10,10);
	ofRect(	Expo::easeOut   (time, beginning, change, duration),160,10,10);
	ofRect(	Expo::easeInOut (time, beginning, change, duration),170,10,10);
	
	ofSetColor(0xf000f0);
	ofRect(	Elastic::easeIn    (time, beginning, change, duration),180,10,10);
	ofRect(	Elastic::easeOut   (time, beginning, change, duration),190,10,10);
	ofRect(	Elastic::easeInOut (time, beginning, change, duration),200,10,10);
	
	ofSetColor(0xf0f0f0);
	ofRect(	Cubic::easeIn    (time, beginning, change, duration),210,10,10);
	ofRect(	Cubic::easeOut   (time, beginning, change, duration),220,10,10);
	ofRect(	Cubic::easeInOut (time, beginning, change, duration),230,10,10);
	
	ofSetColor(0xa0a0a0);
	ofRect(	Circ::easeIn    (time, beginning, change, duration),240,10,10);
	ofRect(	Circ::easeOut   (time, beginning, change, duration),250,10,10);
	ofRect(	Circ::easeInOut (time, beginning, change, duration),260,10,10);
	
	ofSetColor(0xa00000);
	ofRect(	Bounce::easeIn    (time, beginning, change, duration),270,10,10);
	ofRect(	Bounce::easeOut   (time, beginning, change, duration),280,10,10);
	ofRect(	Bounce::easeInOut (time, beginning, change, duration),290,10,10);
	
	ofSetColor(0x00a000);
	ofRect(	Back::easeIn    (time, beginning, change, duration),300,10,10);
	ofRect(	Back::easeOut   (time, beginning, change, duration),310,10,10);
	ofRect(	Back::easeInOut (time, beginning, change, duration),320,10,10);
	
	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){		
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	init();	
}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}
