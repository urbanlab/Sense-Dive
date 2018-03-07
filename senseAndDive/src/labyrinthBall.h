
#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxGui.h"
#include "ofxOsc.h"


#define NB_POTEAUX 4
#define OSC_PORT 1236


// ------------------------------------------------- App
class labyrinth : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
    void exit();
    void handleOSC();
    void loadSavedPhysicalWorld();
    void setupGui();
	
	void keyPressed(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
    
    //physical world
	vector <ofPolyline>                     lines;
	ofxBox2d                                box2d;
	vector <shared_ptr<ofxBox2dCircle> >	circles;
	vector <shared_ptr<ofxBox2dEdge> >      edges;
    
    //forces
    bool gravityL, gravityR, gravityU, gravityD;
    float timeGravityL, timeGravityR, timeGravityU, timeGravityD;
    
    //board inclination
    float angle0, angle1, angle2, angle3;
    
    //gameplay
    bool winner;
    float winnerTime;
    
    //gui
    ofxPanel gui;
    ofParameter<float> lineWidth;
    ofParameter<float> winnerBlinkTime;
    ofParameter<float> yWinnerCoords;
    ofParameter<float> timePoteauActive;

    ofParameter<float> xNewBallOrigin, yNewBallOrigin;
    bool drawGui;
    
    //background
    ofImage laby;
    
    //osc
    ofxOscReceiver OSC_IN;
    
    
    //poteaux
    typedef struct poteau
    {
        bool state;
        float timeOn;
        ofVec2f attractionPoint;
        ofPoint position;
    };
    vector<poteau> poteaux;
    

};
