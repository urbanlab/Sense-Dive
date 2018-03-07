#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(25);	
	ofBackground(255);
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	int baud = 9600;
	serial.setup(0, baud);
    
    //open the first device
	//serial.setup("COM4", baud); // windows example
	//serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
	
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 80);


	OSC1.setup("localhost", 1235); //pixels party
	OSC2.setup("localhost", 1234); //openSky
	OSC3.setup("localhost", 1236); //labyrinth
}

//--------------------------------------------------------------
void ofApp::update(){
			
		// (2) read
		// now we try to read 3 bytes
		// since we might not get them all the time 3 - but sometimes 0, 6, or something else,
		// we will try to read three bytes, as much as we can
		// otherwise, we may have a "lag" if we don't read fast enough
		// or just read three every time. now, we will be sure to 
		// read as much as we can in groups of three...
    
    
    //////////////////////////////////////////////////////////////////////
    //juste changer le 3 en nbDeBytes pour encoder "/arduino/poteau/X"
		
		nBytesRead = 0;
		int nRead  = 0;  // a temp variable to keep count per read
		
		unsigned char bytesReturned[80];
		
		memset(bytesReadString, 0, 80);
		memset(bytesReturned, 0, 80);
	/*	
		while( (nRead = serial.readBytes( bytesReturned, 80)) > 0){
			nBytesRead = nRead;
		};*/
		nRead = serial.readBytes( bytesReturned, 80); 
		memcpy(bytesReadString, bytesReturned, 80);
    

     //cout << " message recu : " << ofToInt(string(bytesReadString)) << endl;
    
    if(ofToInt(string(bytesReadString)) == 1)
    {
	cout << " message recu !!!!!!!!!!!!!!!!!!!!!!!! " << string(bytesReadString) << endl;
        ofxOscMessage m;
        m.setAddress("/arduino/poteau");
        m.addFloatArg(1);
	OSC1.sendMessage(m);
	OSC2.sendMessage(m);
	OSC3.sendMessage(m);
    }
    if(ofToInt(string(bytesReadString)) == 2)
    {
	 cout << " message recu : " << string(bytesReadString) << endl;
        ofxOscMessage m;
        m.setAddress("/arduino/poteau");
        m.addFloatArg(2);
 	OSC1.sendMessage(m);       
 	OSC2.sendMessage(m);       
 	OSC3.sendMessage(m);       
    }
    if(ofToInt(string(bytesReadString)) == 3)
    {
	 cout << " message recu : " << string(bytesReadString) << endl;
        ofxOscMessage m;
        m.setAddress("/arduino/poteau");
        m.addFloatArg(3);
        OSC1.sendMessage(m);
 	OSC2.sendMessage(m);       
 	OSC3.sendMessage(m);       
    }
    if(ofToInt(string(bytesReadString)) == 4)
    {
	 cout << " message recu : " << string(bytesReadString) << endl;
        ofxOscMessage m;
        m.setAddress("/arduino/poteau");
        m.addFloatArg(4);
        OSC1.sendMessage(m);
	OSC2.sendMessage(m);
	OSC3.sendMessage(m);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(0);
	ofDrawBitmapString("OSC PROXY APP", 50,100);
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	 if(key == '1')
    {
        ofxOscMessage m;
        m.setAddress("/arduino/poteau");
        m.addFloatArg(1);

		OSC1.sendMessage(m);
		OSC2.sendMessage(m);
		OSC3.sendMessage(m);
    }
    if(key == '2')
    {
        ofxOscMessage m;
        m.setAddress("/arduino/poteau");
        m.addFloatArg(2);

 		OSC1.sendMessage(m);       
 		OSC2.sendMessage(m);       
 		OSC3.sendMessage(m);       
    }
    if(key == '3')
    {
        ofxOscMessage m;
        m.setAddress("/arduino/poteau");
        m.addFloatArg(3);

        OSC1.sendMessage(m);
 		OSC2.sendMessage(m);       
 		OSC3.sendMessage(m);       
    }
    if(key == '4')
    {
        ofxOscMessage m;
        m.setAddress("/arduino/poteau");
        m.addFloatArg(4);

        OSC1.sendMessage(m);
		OSC2.sendMessage(m);
		OSC3.sendMessage(m);
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
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

