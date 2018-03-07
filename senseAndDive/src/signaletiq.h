//
//  pixels.hpp
//  urbanLab_v2
//
//  Created by Blindsp0t on 20/02/2018.
//
//


#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxHapPlayer.h"


class signaletiq
{
public:
    void setup();
    void update();
    void draw();
    void handleOSC();
    void setupGui();
    void exit();
    void loadMedias(int it);
    void keyPressed(int key);
   
    ofxHapPlayer videoLoopElement;

    //GUI
    ofxPanel gui;
    bool drawGui;
    ofParameter<float> videoSpeed;

};

