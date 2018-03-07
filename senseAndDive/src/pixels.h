//
//  pixels.hpp
//  urbanLab_v2
//
//  Created by Blindsp0t on 20/02/2018.
//
//

#ifndef pixels_hpp
#define pixels_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"


#define NB_POTEAUX 4
#define OSC_PORT 1235



class pixels
{
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
    //ofxSyphonServer syphon;
    
    //gui
    ofxPanel gui;
    bool drawGui;
    ofxVec2Slider centers[NB_POTEAUX];
    ofParameter<float> pixelQty;

};

#endif /* pixels_hpp */
