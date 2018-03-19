#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxGui.h" 
#include "ofxSyphon.h"
#include "ofxOsc.h"
#include "ofxHapPlayer.h"


#define NB_BGND_ELEMENTS 10
#define NB_FORGND_ELEMENTS 25

#define ELEMENT_WIDTH 60
#define ELEMENT_HEIGHT 60

#define OSC_PORT 1234

#define NB_POTEAUX 4
#define timePoteauOn 1


// -------------------------------------------------

class ofApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
    void exit();
    void setupGui();
    void scanMediasDir(string path);
    void scanVideosDir(string path);
    void loadMedias(int it);
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
	
	
	ofxBox2d                                box2d;			  //	the box2d world
	vector		<shared_ptr<ofxBox2dCircle> >	circles;		  //	default box2d circles
    vector<float>                               birthDate;
    
	vector		<shared_ptr<ofxBox2dRect> >		boxes;			  //	defalut box2d rects
    
    
    
    //ELEMENTS
    ofImage backgroundElements[4];
    //ofVideoPlayer foregroundElement;
    ofxHapPlayer foregroundElement;
    void createNewParticule(float x = ofGetWidth()/2, float y=ofGetHeight()/2);
    
    
    //GUI
    ofxPanel gui;
    bool drawGui;
    ofParameter<float> force;
    ofParameter<float> tempsDeVie;
    ofParameter<float> maxDistTelemetre;
    ofParameter<bool>  emulateWithMouse;
    ofParameter<ofColor> colorBg;
    ofParameter<ofColor> colorAttractionPts;
    ofxVec2Slider centers[NB_POTEAUX];
    ofParameter<float> xMin, xMax, yMin, yMax;
    ofParameter<float> circlesRadius;
    
    
    
    //OSC
    ofxOscReceiver OSC_IN;
    void handleOSC();
    float telemeterValue;
    
    
    //SYPHON OUTPUT
    ofxSyphonServer syphon;
    
    
    typedef struct poteau
    {
        bool state;
        float timeOn;
        ofVec2f attractionPoint;
        ofPoint position;
    };
    vector<poteau> poteaux;
    ofColor drawingColorGlobal;
    ofColor color[NB_POTEAUX];
    
    
    
    //VIDEO BACKGROUND
    ofVideoPlayer videoBG;
    ofxHapPlayer foreground;
    
    
    //TABLEAUX
    string basePath, fullPath;
    int    iterator;
    bool hasForegroundVideo;
};

