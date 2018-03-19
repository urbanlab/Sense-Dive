//
//  pixels.cpp
//  urbanLab_v2
//
//  Created by Blindsp0t on 20/02/2018.
//
//

#include "pixels.h"

void pixels::setup()
{
    setupGui();
    
    //load medias in data path
    currentImgID=0;
    scanMediasDir("images/");
    
    //setupParticleSystem
    setupParticlesAndImgs(currentImgID);
    
    //osc
    OSC_IN.setup(OSC_PORT);
    
    //SHUFFLE VECTORS
    std::random_shuffle(myPixelsPoteau0.begin(), myPixelsPoteau0.end());
    std::random_shuffle(myPixelsPoteau1.begin(), myPixelsPoteau1.end());
    std::random_shuffle(myPixelsPoteau2.begin(), myPixelsPoteau2.end());
    std::random_shuffle(myPixelsPoteau3.begin(), myPixelsPoteau3.end());
    
    alreadyMoved[0] = 0;
    alreadyMoved[1] = 0;
    alreadyMoved[2] = 0;
    alreadyMoved[3] = 0;
    
}

//--------------------------------------------------------------
void pixels::scanMediasDir(string path)
{
    ofDirectory dir;
    dir.listDir(path.c_str());
    dir.sort();
    for(int i = 0; i < (int)dir.size(); i++){
        cout << "new media element : " << dir.getPath(i) << endl;
        imgPaths.push_back(dir.getPath(i));
    }
}


//--------------------------------------------------------------
void pixels::setupGui()
{
    gui.setup();
    
    gui.add(pixelQty.set("pixelQty", 200, 200, 5000));
    
    ofParameterGroup positionsPoteaux;
    positionsPoteaux.setName("positionsPoteaux");
    gui.add(centers[0].setup("center0", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(centers[1].setup("center1", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(centers[2].setup("center2", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(centers[3].setup("center3", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    
    gui.loadFromFile("gui.xml");
    gui.minimizeAll();
    
    gui.setPosition(ofGetWidth()-gui.getWidth(), 2);
}

//--------------------------------------------------------------
void pixels::exit()
{
    gui.saveToFile("gui.xml");
}

//--------------------------------------------------------------
void pixels::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    ofSetBackgroundColor(0);
    
    handleOSC();
    
    mesh.clear();
    
    
    for(int i=0; i<myPixelsPoteau0.size();i++)
    {
        if(!myPixelsPoteau0[i].active && alreadyMoved[0] > i)
        {
            myPixelsPoteau0[i].active = true;
        }
        if(myPixelsPoteau0[i].active)
        {
            myPixelsPoteau0[i].currentPos += (myPixelsPoteau0[i].destination - myPixelsPoteau0[i].currentPos)/(10+ofRandom(5));
        }
        
        
        mesh.addColor(myPixelsPoteau0[i].color);
        mesh.addVertex(myPixelsPoteau0[i].currentPos);
    }
    
    for(int i=0; i<myPixelsPoteau1.size();i++)
    {
        if(!myPixelsPoteau1[i].active && alreadyMoved[1] > i)
        {
            myPixelsPoteau1[i].active = true;
        }
        if(myPixelsPoteau1[i].active)
        {
            myPixelsPoteau1[i].currentPos += (myPixelsPoteau1[i].destination - myPixelsPoteau1[i].currentPos)/(10+ofRandom(5));
        }
        
        
        mesh.addColor(myPixelsPoteau1[i].color);
        mesh.addVertex(myPixelsPoteau1[i].currentPos);
    }
    
    for(int i=0; i<myPixelsPoteau2.size();i++)
    {
        if(!myPixelsPoteau2[i].active && alreadyMoved[2] > i)
        {
            myPixelsPoteau2[i].active = true;
        }
        if(myPixelsPoteau2[i].active)
        {
            myPixelsPoteau2[i].currentPos += (myPixelsPoteau2[i].destination - myPixelsPoteau2[i].currentPos)/(10+ofRandom(5));
        }
        
        
        mesh.addColor(myPixelsPoteau2[i].color);
        mesh.addVertex(myPixelsPoteau2[i].currentPos);
    }
    
    for(int i=0; i<myPixelsPoteau3.size();i++)
    {
        if(!myPixelsPoteau3[i].active && alreadyMoved[3] > i)
        {
            myPixelsPoteau3[i].active = true;
        }
        if(myPixelsPoteau3[i].active)
        {
            myPixelsPoteau3[i].currentPos += (myPixelsPoteau3[i].destination - myPixelsPoteau3[i].currentPos)/(10+ofRandom(5));
        }
        
        
        mesh.addColor(myPixelsPoteau3[i].color);
        mesh.addVertex(myPixelsPoteau3[i].currentPos);
    }
    
    
}

//--------------------------------------------------------------
void pixels::draw(){
    
    ofSetColor(255);
    mesh.drawVertices();
    
    
    //gui and debug
    if(drawGui)
    {
        gui.draw();
        
        ofSetColor(255,0,0);
        for(int i=0; i<NB_POTEAUX; i++)
        {
            ofDrawCircle(ofVec2f(centers[i]->x, centers[i]->y) , 45);
        }
    }
    
    //syphon.publishScreen();
}


//--------------------------------------------------------------
void pixels::keyPressed(int key){
    
    if(key=='q')
    {
        alreadyMoved[0] +=pixelQty;
    }
    if(key=='s')
    {
        alreadyMoved[1] +=pixelQty;
    }
    if(key=='d')
    {
        alreadyMoved[2] +=pixelQty;
    }
    if(key=='f')
    {
        alreadyMoved[3] +=pixelQty;
    }
    if(key == ' ' )
    {
        drawGui = !drawGui;
    }
    
    if(key =='0')
    {
        if(currentImgID < imgPaths.size()-1)
            currentImgID++;
        else
            currentImgID = 0;
        
        setupParticlesAndImgs(currentImgID);
        
        
        //osc
        OSC_IN.setup(OSC_PORT);
        
        //SHUFFLE VECTORS
        std::random_shuffle(myPixelsPoteau0.begin(), myPixelsPoteau0.end());
        std::random_shuffle(myPixelsPoteau1.begin(), myPixelsPoteau1.end());
        std::random_shuffle(myPixelsPoteau2.begin(), myPixelsPoteau2.end());
        std::random_shuffle(myPixelsPoteau3.begin(), myPixelsPoteau3.end());
        
        alreadyMoved[0] = 0;
        alreadyMoved[1] = 0;
        alreadyMoved[2] = 0;
        alreadyMoved[3] = 0;
    }
    
}



//--------------------------------------------------------------
void pixels::handleOSC()
{
    while(OSC_IN.hasWaitingMessages()){
        
        ofxOscMessage m;
        OSC_IN.getNextMessage(m);
        
        if(m.getAddress() == "/arduino/poteau")
        {
            float poteauNb = m.getArgAsFloat(0);
            poteauNb -= 1;
            cout << "poteauNb : " << poteauNb << endl;
            
            alreadyMoved[int(poteauNb)] += pixelQty;
        }
    }
}


//--------------------------------------------------------------
void pixels::setupParticlesAndImgs(int imgID)
{
    
    
    myImage.load(imgPaths[imgID].c_str());
    myImage.resize(ofGetWidth(),ofGetHeight());
    
    
    myPixelsPoteau0.clear();
    myPixelsPoteau1.clear();
    myPixelsPoteau2.clear();
    myPixelsPoteau3.clear();
    
    
    ofPixels pix = myImage.getPixels();
    
    for(int i=0; i<ofGetWidth()*ofGetHeight();i++)
    {
        ofPoint pos;
        pos.x = i%(ofGetWidth());
        pos.y = i/(ofGetWidth());
        
        customPixel p;
        
        p.color = myImage.getColor(pos.x, pos.y) ;
        
        p.currentPos = p.initPos;
        p.destination = pos;
        p.active = false;
        
        if(i%4==0)
        {
            p.initPos = ofVec2f(centers[0]->x, centers[0]->y)/*ofPoint(0,0)*/-ofPoint(ofRandom(30), ofRandom(30));
            p.currentPos = p.initPos;
            
            myPixelsPoteau0.push_back(p);
        }
        else if(i%3==0)
        {
            p.initPos = ofVec2f(centers[1]->x, centers[1]->y)/*ofPoint(myImage.getWidth(),0)*/-ofPoint(ofRandom(30), ofRandom(30));
            p.currentPos = p.initPos;
            
            myPixelsPoteau1.push_back(p);
        }
        else if(i%2==0)
        {
            p.initPos = ofVec2f(centers[2]->x, centers[2]->y)/*ofPoint(0,myImage.getHeight())*/+ofPoint(ofRandom(30), ofRandom(30));
            p.currentPos = p.initPos;
            
            myPixelsPoteau2.push_back(p);
        }
        else if(i%1==0)
        {
            p.initPos = ofVec2f(centers[3]->x, centers[3]->y)/*ofPoint(myImage.getWidth(),myImage.getHeight())*/+ofPoint(ofRandom(30), ofRandom(30));
            p.currentPos = p.initPos;
            
            myPixelsPoteau3.push_back(p);
        }
    }
}

