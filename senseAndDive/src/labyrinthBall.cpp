#include "labyrinthBall.h"

//--------------------------------------------------------------
void labyrinth::setup() {
	
	ofBackgroundHex(0xfdefc2);
	ofSetVerticalSync(true);
	
    //load labyrinth image
    laby.load("labyrinth/laby.png");
    
    //interactions - inputs
    poteaux.resize(NB_POTEAUX);
    
	// Box2d
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.createGround();
	box2d.setFPS(60.0);
	
	//lignes enregistrees
    loadSavedPhysicalWorld();
    
    //first ball
    shared_ptr<ofxBox2dCircle> c = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
    c.get()->setPhysics(1, 0.5, 0.5);
    c.get()->setup(box2d.getWorld(), xNewBallOrigin, yNewBallOrigin, 30);
    circles.push_back(c);
    
    //gameplay
    winner = false;
    
    //gui
    setupGui();
    
    //init
    angle0 = angle1 = angle2 = angle3;
	
    //osc
    OSC_IN.setup(OSC_PORT);
}

//--------------------------------------------------------------
void labyrinth::setupGui()
{
    drawGui=false;
    
    gui.setup();
    gui.add(lineWidth.set("lineWidth", 2, 1, 10));
    gui.add(winnerBlinkTime.set("winnerBlinkTime", 2, 1, 5));
    gui.add(yWinnerCoords.set("yLimit", ofGetHeight()-100, 0, ofGetHeight()));
    gui.add(timePoteauActive.set("timePoteauActive", 1, 0.1, 3));
    
    gui.add(xNewBallOrigin.set("xNewBallOrigin", ofGetWidth()/2, 0, ofGetWidth()));
    gui.add(yNewBallOrigin.set("yNewBallOrigin", ofGetHeight()/2, 0, ofGetHeight()));

    gui.loadFromFile("gui.xml");
}




//--------------------------------------------------------------
void labyrinth::exit()
{
    gui.saveToFile("gui.xml");
}

//--------------------------------------------------------------
void labyrinth::update() {

    //OSC messages
    handleOSC();

    //reset forces each frame
    box2d.setGravity(0, 0);
    
    float gravityX, gravityY;
    
    for(int i=0; i<NB_POTEAUX; i++)
    {
        //if we want to add a little "timing" on poteaux behaviour
        if(ofGetElapsedTimef() - poteaux[i].timeOn > timePoteauActive)
        {
            poteaux[i].state = false;
            
            if(i == 0 ) gravityX += 20;
            if(i == 1 ) gravityX -= 20;
            if(i == 2 ) gravityY -= 20;
            if(i == 3 ) gravityY += 20;
        }
        
        if(poteaux[i].state == true)
        {
            cout << "poteau " << i << " active" << endl;
            if(i == 0 ) gravityX -= 20;
            if(i == 1 ) gravityX += 20;
            if(i == 2 ) gravityY+=20;
            if(i == 3 ) gravityY-=20;
        }
    }
    
    //update model
    box2d.setGravity(gravityX, gravityY);
	box2d.update();
}

//--------------------------------------------------------------
void labyrinth::draw() {
	
    ofSetColor(253, 239, 194);
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());

    
    ofPushMatrix();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(180,1.0,0.0,0.0);
    
    // 0 - gauche
    if(poteaux[0].state == true)
    {
        angle0+=0.1;
        ofRotate(-angle0, 0.0, 1.0, 0.0);
    }
    else if(angle0 > 0)
    {
            angle0 -= 0.1;
            ofRotate(-angle0, 0.0, 1.0, 0.0);
    }
    
    // 1 - droite
    if(poteaux[1].state == true)
    {
        angle1+=0.1;
        ofRotate(angle1, 0.0, 1.0, 0.0);
    }
    else if(angle1 > 0)
    {
        angle1 -= 0.1;
        ofRotate(angle1, 0.0, 1.0, 0.0);
    }
    
    // 2 - haut
    if(poteaux[2].state == true)
    {
        angle2+=0.1;
        ofRotate(-angle2, 1.0, 0.0, 0.0);
    }
    else if(angle2 > 0)
    {
        angle2 -= 0.1;
        ofRotate(-angle2, 1.0, 0.0, 0.0);
    }
    
    // 3 - bas
    if(poteaux[3].state == true)
    {
        angle3+=0.1;
        ofRotate(angle3, 1.0, 0.0, 0.0);
    }
    else if(angle3 > 0)
    {
        angle3 -= 0.1;
        ofRotate(angle3, 1.0, 0.0, 0.0);
    }

    
    laby.draw(-ofGetWidth()/2,-ofGetHeight()/2, ofGetWidth(), ofGetHeight());
    
    
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
	
    //particules
	for (int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0xc0dd3b);
		circles[i].get()->draw();
        
        //winner !
        if(circles[i].get()->getPosition().y < yWinnerCoords)
        {
            //cout << " winner because of ball : " << i << " position : " << circles[i].get()->getPosition().y << endl;
            winner = true;
            winnerTime = ofGetElapsedTimef();
            circles[i].get()->setPosition(0, 150000);
            //circles[i].get()->destroy();
        }
	}
	
    
    if(winner)
    {
        
        
        if(ofGetElapsedTimef() - winnerTime < winnerBlinkTime)
        {
            //ofSetBackgroundColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
            ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
            ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
            //cout << ofGetElapsedTimef() - winnerTime << " <  " << winnerBlinkTime << endl;
        }
        else
        {
            cout << "winner mode ends now " << endl;
            winner = false;
            //drop a new ball ;)
            //first ball
            shared_ptr<ofxBox2dCircle> c = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
            c.get()->setPhysics(1, 0.5, 0.5);
            c.get()->setup(box2d.getWorld(), xNewBallOrigin, yNewBallOrigin, 30);
            circles.push_back(c);
            
            //circles[0].get()->destroy();
        }
    }
    
    
    ofPopMatrix();
    
    
    if(drawGui)
    {
        
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotate(180,1.0,0.0,0.0);
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);


        //labyrinthe
        ofSetHexColor(0x444342);
        ofNoFill();
        ofSetLineWidth(lineWidth);
        for (int i=0; i<lines.size(); i++) {
            lines[i].draw();
        }
        for (int i=0; i<edges.size(); i++) {
            edges[i].get()->draw();
        }
        
        //origin new balls
        ofNoFill();
        ofSetColor(0,255,0);
        ofDrawCircle(xNewBallOrigin, yNewBallOrigin, 30);
        ofFill();
        
            ofPopMatrix();
        
        ofSetColor(ofColor::red);
        ofDrawLine(0, yWinnerCoords, ofGetWidth(), yWinnerCoords);
        ofSetColor(255);
        gui.draw();
    }
}


//--------------------------------------------------------------
void labyrinth::keyPressed(int key) {
	
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
  
    
    //clear labyrinth
	if(key == 'c') {
		lines.clear();
		edges.clear();
        
        ofstream f;
        f.clear();
        f.open(ofToDataPath("labyrinth/lines.txt").c_str());
        f<<"\n";
        f.close();
	}
    
    //save labyrinth
	if(key == 'S') {
		ofstream f;
		f.clear();
		f.open(ofToDataPath("labyrinth/lines.txt").c_str(), ios_base::app);
		for (int i=0; i<lines.size(); i++) {
			for (int j=0; j<lines[i].size(); j++) {
				float x = lines[i][j].x;
				float y = lines[i][j].y;
				f << x << "," << y << ",";
			}
			f << "\n";
		}
		f.close();lines.clear();
	}
    
    if(key == 'N') {
        shared_ptr<ofxBox2dCircle> c = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
        c.get()->setPhysics(1, 0.5, 0.5);
        c.get()->setup(box2d.getWorld(), mouseX, mouseY, 30);
        circles.push_back(c);
        cout << "mouseX : " << mouseX << " - mouseY : " << mouseY << endl;
    }
    
    if(key==' ')
        drawGui = !drawGui;
}

//--------------------------------------------------------------
void labyrinth::handleOSC()
{
    while(OSC_IN.hasWaitingMessages()){
        
        cout << "message OSC recu " << endl;
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
void labyrinth::loadSavedPhysicalWorld()
{
    ifstream f;
    f.open(ofToDataPath("labyrinth/lines.txt").c_str());
    vector <string> strLines;
    while (!f.eof()) {
        string ptStr;
        getline(f, ptStr);
        strLines.push_back(ptStr);
    }
    f.close();
    
    for (int i=0; i<strLines.size(); i++) {
        vector <string> pts = ofSplitString(strLines[i], ",");
        if(pts.size() > 0) {
            shared_ptr <ofxBox2dEdge> edge = shared_ptr<ofxBox2dEdge>(new ofxBox2dEdge);
            for (int j=0; j<pts.size(); j+=2) {
                if(pts[j].size() > 0) {
                    float x = ofToFloat(pts[j]);
                    float y = ofToFloat(pts[j+1]);
                    edge.get()->addVertex(x, y);
                }
            }
            edge.get()->create(box2d.getWorld());
            edges.push_back(edge);
        }
    }
}


//--------------------------------------------------------------
void labyrinth::mouseMoved(int x, int y ) {
}

//--------------------------------------------------------------
void labyrinth::mouseDragged(int x, int y, int button) {
	lines.back().addVertex(x, y);
}

//--------------------------------------------------------------
void labyrinth::mousePressed(int x, int y, int button) {
	lines.push_back(ofPolyline());
	lines.back().addVertex(x, y);
}

//--------------------------------------------------------------
void labyrinth::mouseReleased(int x, int y, int button) {
	
    shared_ptr <ofxBox2dEdge> edge = shared_ptr<ofxBox2dEdge>(new ofxBox2dEdge);
	lines.back().simplify();
	
	for (int i=0; i<lines.back().size(); i++) {
		edge.get()->addVertex(lines.back()[i]);
	}
	
	//poly.setPhysics(1, .2, 1);  // uncomment this to see it fall!
	edge.get()->create(box2d.getWorld());
	edges.push_back(edge);
	
	//lines.clear();
}

//--------------------------------------------------------------
void labyrinth::windowResized(int w, int h) {
}

