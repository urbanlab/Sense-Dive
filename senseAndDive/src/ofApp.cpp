#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    int x = 0;//(ofGetWidth() - ofGetWidth()) * 0.5;
    int y = 0;//(ofGetHeight() - ofGetHeight()) * 0.5;
    int w = 1920;//ofGetWidth();
    int h = 1080;//ofGetHeight();
    
    cout << "allocate FrameBuffer Object : " << w << "  "  << h << endl;
    fbo.allocate(w, h);
    
    warper.setSourceRect(ofRectangle(0, 0, w, h));
    warper.setTopLeftCornerPosition(ofPoint(x, y));
    warper.setTopRightCornerPosition(ofPoint(x + w, y));
    warper.setBottomLeftCornerPosition(ofPoint(x, y + h));
    warper.setBottomRightCornerPosition(ofPoint(x + w, y + h));
    warper.setup();
    warper.load();
    warper.disableMouseControls();
    warper.disableKeyboardShortcuts();
    
    pixelsMode.setup();
    skyMode.setup();
    signaletiqMode.setup();
    labyrinthMode.setup();
    
    globalState = 0;

    drawGui = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){

    switch(globalState)
    {
        case 0:
        {
            pixelsMode.update();
            break;
        };
            
        case 1 :
        {
            skyMode.update();
            break;
        };

        case 2:
        {
            signaletiqMode.update();
            break;
        }

        case 3:
        {
            labyrinthMode.update();
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    ofSetColor(255);
    
    //======================== draw image into fbo.
    
    fbo.begin();
    ofClear(0);
    switch(globalState)
    {
        case 0:
        {
            pixelsMode.draw();
            break;
        }
        case 1:
        {
            skyMode.draw();
            break;
        }
        case 2:
        {
            signaletiqMode.draw();
            break;
        }

        case 3:
        {
            labyrinthMode.draw();
            break;
        }

            
    }    fbo.end();
    
    //======================== get our quad warp matrix.
    
    ofMatrix4x4 mat = warper.getMatrix();
    
    //======================== use the matrix to transform our fbo.
    
    ofPushMatrix();
    ofMultMatrix(mat);
    fbo.draw(0, 0);
    ofPopMatrix();
    

    if(drawGui)
    {
        switch(globalState)
        {
            case 0:
            {
                pixelsMode.gui.draw();
                break;
            }
            case 1:
            {
                skyMode.gui.draw();
                break;
            }
            case 2:
            {
                signaletiqMode.gui.draw();
                break;
            }

            case 3:
            {
                labyrinthMode.gui.draw();
                break;
            }   
        }
    }
 
    //======================== draw quad warp ui.
    
    ofSetColor(ofColor::magenta);
    warper.drawQuadOutline();
    
    ofSetColor(ofColor::yellow);
    warper.drawCorners();
    
    ofSetColor(ofColor::magenta);
    warper.drawHighlightedCorner();
    
    ofSetColor(ofColor::red);
    warper.drawSelectedCorner();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='0')
        globalState = 0;
    if(key=='1')
        globalState = 1;
    if(key=='2')
        globalState = 2;
    if(key=='3')
        globalState = 3;        

    if(key=='w')
    {
        warper.enableMouseControls();
        warper.enableKeyboardShortcuts();
    }
    if(key=='W')
    {
        warper.reset();
    }

    if(key == ' ')
    {
        drawGui = !drawGui;
    }

    switch(globalState)
    {
        case 0:
        {
            pixelsMode.keyPressed(key);
            break;
        }
        case 1:
        {
            skyMode.keyPressed(key);
            break;
        }
        case 2:
        {
            signaletiqMode.keyPressed(key);
            break;
        }
        case 3:
        {
            labyrinthMode.keyPressed(key);
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::exit()
{
    warper.save();
    pixelsMode.exit();
    skyMode.exit();
    signaletiqMode.exit();
    labyrinthMode.exit();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if(key=='w')
    {
        warper.disableMouseControls();
        warper.disableKeyboardShortcuts();
    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(globalState==3)
        labyrinthMode.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(globalState==3)
        labyrinthMode.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(globalState==3)
        labyrinthMode.mouseReleased(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
