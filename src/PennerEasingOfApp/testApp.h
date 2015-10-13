#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

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

class testApp : public ofSimpleApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
	
		void init();
		
		float time, beginning, change, duration;
		
		
};

#endif	
