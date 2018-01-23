#include "ofApp.h"

#define behaviour_pop_poteau 1


//--------------------------------------------------------------
void ofApp::setup() {
    
    //general
    ofSetVerticalSync(true);
    ofSetBackgroundColor(136,215,248);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofDisableAntiAliasing();
    ofEnableAlphaBlending();
    
    //interactions - inputs
    poteaux.resize(NB_POTEAUX);
    
    loadMedias(0);
    
    //gui
    setupGui();
    drawGui=false;
    
    //box2D
    box2d.init();
    box2d.setGravity(0, 0);
    box2d.setFPS(60.0);
    box2d.createBounds(xMin, yMin, xMax-xMin, yMax-yMin);
    
    //background elements
    for (int i=0; i<NB_BGND_ELEMENTS; i++) {
        float w = ELEMENT_WIDTH;
        float h = ELEMENT_HEIGHT;
        shared_ptr<ofxBox2dRect> rect = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
        rect.get()->setPhysics(3.0, 0.53, 0.9);
        rect.get()->setup(box2d.getWorld(), ofRandom(xMin, xMax), ofRandom(yMin, yMax), w, h);
        boxes.push_back(rect);
    }
    
    //particules (no more created by a poteau action)
    for (int i=0; i<NB_BGND_ELEMENTS; i++) {
        createNewParticule(ofGetWidth()/2, ofGetHeight()/2);
    }
    
    
    //osc
    OSC_IN.setup(OSC_PORT);
    
    
    //syphon
    syphon.setName("urbanLab");
    
    //colors
    color[0] = ofColor(120, 0,0);
    color[1] = ofColor(0,120,0);
    color[2] = ofColor(0,0,120);
    color[3] = ofColor(50,70,90);
    
}


//--------------------------------------------------------------
void ofApp::scanMediasDir(string path)
{
    ofDirectory dir;
    dir.allowExt("png");
    dir.listDir(path.c_str());
    for(int i = 0; i < (int)dir.size(); i++){
        cout << "new media element : " << dir.getPath(i) << endl;
        //imgPaths.push_back(dir.getPath(i));
        backgroundElements[i].load(dir.getPath(i));
    }
}


//--------------------------------------------------------------
void ofApp::loadMedias(int it)
{
    //scan directories
    basePath = "medias";
    iterator = it;
    fullPath = basePath + ofToString(iterator);
    
    //Background elements
    scanMediasDir(fullPath + "/PNG");
    
    //Particles animated elements
    ofDirectory dir;
    dir.allowExt("mov");
    dir.listDir(fullPath);
    foregroundElement.load(dir.getPath(0));
    foregroundElement.update();
    foregroundElement.play();
    
    hasForegroundVideo = false;
    if(dir.size()>1)
    {
        foreground.load(dir.getPath(1));
        foreground.update();
        foreground.play();
        hasForegroundVideo = true;
    }
    
    //video background
    ofDirectory dir2;
    dir2.allowExt("mp4");
    dir2.listDir(fullPath);
    cout << "loading mp4 video " << dir2.getPath(0) << endl;
    videoBG.load(dir2.getPath(0));
    videoBG.update();
    videoBG.play();

}

//--------------------------------------------------------------
void ofApp::exit()
{
    gui.saveToFile("gui.xml");
}

//--------------------------------------------------------------
void ofApp::setupGui()
{
    gui.setup();
    
    gui.add(force.set("force", 0.5, 0, 20));
    gui.add(tempsDeVie.set("tempsDeVie", 10, 1, 360));
    gui.add(circlesRadius.set("circlesRadius", 25, 0, 50));
    gui.add(emulateWithMouse.set("emulateWithMouse", false));
    
    ofParameterGroup colors;
    colors.setName("colors");
    colors.add(colorBg.set("colorBG",ofColor(136,215,248),ofColor(0,0),ofColor(255,255)));
    colors.add(colorAttractionPts.set("colorAttractionPts",ofColor(50,240,50, 100),ofColor(0,0),ofColor(255,255)));
    gui.add(colors);
    
    ofParameterGroup positionsPoteaux;
    positionsPoteaux.setName("positionsPoteaux");
    gui.add(centers[0].setup("center0", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(centers[1].setup("center1", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(centers[2].setup("center2", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(centers[3].setup("center3", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    
    ofParameterGroup box2dWorldLimit;
    box2dWorldLimit.setName("box2dWorldLimit");
    box2dWorldLimit.add(xMin.set("xMin", 0, 0, ofGetWidth()));
    box2dWorldLimit.add(xMax.set("xMax", 0, 0, ofGetWidth()));
    box2dWorldLimit.add(yMin.set("yMin", 0, 0, ofGetHeight()));
    box2dWorldLimit.add(yMax.set("yMax", 0, 0, ofGetHeight()));
    gui.add(box2dWorldLimit);
    
    
    gui.loadFromFile("gui.xml");
    gui.minimizeAll();
    
    gui.setPosition(ofGetWidth()-gui.getWidth(), 2);
}

//--------------------------------------------------------------
void ofApp::update() {
    
    //display fps
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    //reset color
    drawingColorGlobal = ofColor(255);
    
    for(int i=0; i<NB_POTEAUX; i++)
    {
        //update positions according to gui
        poteaux[i].position = ofVec2f(centers[i]->x, centers[i]->y) ;
        
        //if we want to add a little "timing" on poteaux behaviour
        if(ofGetElapsedTimef() - poteaux[i].timeOn > timePoteauOn)
        {
            poteaux[i].state = false;
        }
        
        if(poteaux[i].state == true)
        {
            cout << "poteau " << i << " active" << endl;
            drawingColorGlobal -= color[i];
        }
    }
    
    
    //videos
    foregroundElement.update();
    videoBG.update();
    foreground.update();
    
    //osc
    handleOSC();
    
    //box2D
    box2d.update();
    
    ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
    
    for(int i=0; i<circles.size(); i++) {
        for(int p=0; p<NB_POTEAUX; p++)
        {
            if(poteaux[p].state == true)
                circles[i].get()->addAttractionPoint(poteaux[p].position, force);
        }
    }
}


//--------------------------------------------------------------
void ofApp::draw() {

    
    //build a color according to the number of active poteaux
    ofSetColor(drawingColorGlobal);
    
    
    //draw background first
    videoBG.draw(xMin, yMin, xMax - xMin, yMax-yMin);

    ofSetColor(255);
    
    //draw Particles
    for(int i=0; i<circles.size(); i++) {
        ofFill();
        foregroundElement.draw(circles[i].get()->getPosition().x, circles[i].get()->getPosition().y, circles[i].get()->getRadius(), circles[i].get()->getRadius());
        
    }
    
    //draw background elements
    for(int i=0; i<boxes.size(); i++) {
        ofFill();
        backgroundElements[int(i%4)].draw(boxes[i].get()->getPosition().x, boxes[i].get()->getPosition().y, boxes[i].get()->getWidth(), boxes[i].get()->getHeight());
    }
    
    //draw foreground
    ofSetColor(255, 255, 255, 255);
    if(hasForegroundVideo)
        foreground.draw(xMin, yMin, xMax - xMin, yMax-yMin);
    
    
    for(int p=0; p<NB_POTEAUX; p++)
    {
        if(poteaux[p].state == true)
        {
            ofNoFill();
            ofDrawCircle(poteaux[p].position, circlesRadius*cos(ofGetFrameNum()));
            ofFill();
            
        }
    }
    
    //gui and debug
    if(drawGui)
    {
        gui.draw();
        
        ofSetColor(255,0,0);
        for(int i=0; i<NB_POTEAUX; i++)
        {
            ofDrawCircle(poteaux[i].position, 45);
        }
        
        //draw attraction points
        ofSetColor(colorAttractionPts);
        for(int i=0; i<NB_POTEAUX; i++)
        {
            if(poteaux[i].state)
                ofDrawCircle(poteaux[i].position, 55);
        }
        
        //draw box2d world limits
        ofDrawLine(0, yMin, ofGetWidth(), yMin);
        ofDrawLine(0, yMax, ofGetWidth(), yMax);
        ofDrawLine(xMin, 0, xMin, ofGetHeight());
        ofDrawLine(xMax, 0, xMax, ofGetHeight());
        
        
        ofSetColor(255);
    }
    
    //syphon
    syphon.publishScreen();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    if(key == 'c') {
        createNewParticule();
    }
    
    if(key == 'b') {
        float w = ofRandom(14, 20);
        float h = ofRandom(14, 20);
        shared_ptr<ofxBox2dRect> rect = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
        rect.get()->setPhysics(3.0, 0.53, 0.9);
        rect.get()->setup(box2d.getWorld(), mouseX, mouseY, w, h);
        boxes.push_back(rect);
    }
    
    if(key == 't') ofToggleFullscreen();
    
    if(key==' ' )
        drawGui = !drawGui;
    
    if(key== 'q')
    {
        poteaux[0].state = true;
        poteaux[0].timeOn = ofGetElapsedTimef();
    }
    if(key=='s')
    {
        poteaux[1].state = true;
        poteaux[1].timeOn = ofGetElapsedTimef();
    }
    if(key=='d')
    {
        poteaux[2].state = true;
        poteaux[2].timeOn = ofGetElapsedTimef();
    }
    if(key=='f')
    {
        poteaux[3].state = true;
        poteaux[3].timeOn = ofGetElapsedTimef();
    }
    if(key=='R')
    {
        if(iterator < 2)
            iterator ++;
        else
            iterator = 0;
                
        loadMedias(iterator);
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::handleOSC()
{
    while(OSC_IN.hasWaitingMessages()){
        
        ofxOscMessage m;
        OSC_IN.getNextMessage(m);
        
        if(m.getAddress() == "/arduino/telemetre"){
            /*
            telemeterValue = m.getArgAsFloat(0);
            
            if(telemeterValue < maxDistTelemetre)
            {
                createNewParticule();
            }
             */
        }
        
        if(m.getAddress() == "/arduino/poteau")
        {
            float poteauNb = m.getArgAsFloat(0);
            poteauNb -= 1;
            cout << "poteauNb : " << poteauNb << endl;
            poteaux[poteauNb].state = true;
            poteaux[poteauNb].timeOn = ofGetElapsedTimef();
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::createNewParticule(float x, float y)
{
    float r = ofRandom(10, 20);
    shared_ptr<ofxBox2dCircle> circle = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
    circle.get()->setPhysics(3.0, 0.53, 0.9);
    circle.get()->setup(box2d.getWorld(), x, y, r);
    circles.push_back(circle);
    birthDate.push_back(ofGetElapsedTimef());
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::resized(int w, int h){
}

