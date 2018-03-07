#pragma once

#include "ofMain.h"
#include "ofxQuadWarp.h"


#include "pixels.h"
#include "openSky.h"
#include "signaletiq.h"
#include "labyrinthBall.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    int globalState;
    
    pixels pixelsMode;
    openSky skyMode;
    signaletiq signaletiqMode;
	labyrinth labyrinthMode;
    
    //in-app mapping tool
    ofxQuadWarp warper;
    ofFbo fbo;
    ofPoint points[10];

	bool bFullscreen;
		
};
