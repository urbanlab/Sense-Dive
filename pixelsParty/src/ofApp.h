#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSyphon.h"
#include "ofxOsc.h"

#define NB_POTEAUX 4


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void handleOSC();
        void setupGui();
        void exit();
        void scanMediasDir(string path);
    
        void setupParticlesAndImgs(int imgID = 0);
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    //image loaded at startup
    ofImage myImage;
    vector<string> imgPaths;
    int currentImgID;
    
    //custom type
    typedef struct
    {
        ofColor color;
        ofPoint initPos;
        ofPoint destination;
        ofPoint currentPos;
        int poteauID;
        bool active;
        
    }customPixel;
    
    
    typedef struct poteau
    {
        bool state;
        float timeOn;
        ofVec2f attractionPoint;
        ofPoint position;
    };
    
    
    //iterator
    int alreadyMoved[4];
    
    //groups of pixels forming the entire image
    vector<customPixel> myPixelsPoteau0, myPixelsPoteau1, myPixelsPoteau2, myPixelsPoteau3;
    
    //for drawing
    ofMesh mesh;
    
    //osc
    ofxOscReceiver OSC_IN;
    
    //syphon output
    ofxSyphonServer syphon;
    
    //gui
    ofxPanel gui;
    bool drawGui;
    ofxVec2Slider centers[NB_POTEAUX];
    ofParameter<float> pixelQty;
    
};
