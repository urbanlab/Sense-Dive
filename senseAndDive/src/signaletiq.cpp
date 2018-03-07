//
//  pixels.cpp
//  urbanLab_v2
//
//  Created by Blindsp0t on 20/02/2018.
//
//

#include "signaletiq.h"


//--------------------------------------------------------------
void signaletiq::setup() {
    
    //general
    //ofSetVerticalSync(true);
    ofSetBackgroundColor(136,215,248);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofDisableAntiAliasing();
    ofEnableAlphaBlending();
    
    //load videos
    loadMedias(0);    

    //gui
    setupGui();
    drawGui = false;
    
}


//--------------------------------------------------------------
void signaletiq::loadMedias(int it)
{
    //scan directories
    ofDirectory dir;
    dir.allowExt("mov");
    dir.listDir("signaletiq");
    videoLoopElement.load(dir.getPath(0));
    videoLoopElement.update();
    videoLoopElement.play();
    
}

//--------------------------------------------------------------
void signaletiq::exit()
{
    gui.saveToFile("gui.xml");
}

//--------------------------------------------------------------
void signaletiq::setupGui()
{
    gui.setup();
    gui.add(videoSpeed.set("videoSpeed", 1.0, 0.0, 2.0));
        
    gui.loadFromFile("gui.xml");
    //gui.minimizeAll();
    
    gui.setPosition(ofGetWidth()-gui.getWidth(), 2);
}

//--------------------------------------------------------------
void signaletiq::update() {
    
    //display fps
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    videoLoopElement.setSpeed(videoSpeed);
    videoLoopElement.update();
}


//--------------------------------------------------------------
void signaletiq::draw() {
    
    videoLoopElement.draw(0,0,ofGetWidth(), ofGetHeight());
  
    if(drawGui)
        gui.draw();
    
}

//--------------------------------------------------------------
void signaletiq::keyPressed(int key) {
    
    if(key==' ')
        drawGui = !drawGui;
    
    
}


