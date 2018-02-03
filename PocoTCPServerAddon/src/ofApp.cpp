#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    //ofSetFrameRate(60);
    receiver.start(4445);

}

//--------------------------------------------------------------
void ofApp::update(){
    receiver.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
//    if(newSVG) {
//        ofPushStyle();
//        ofSetColor(255,0,0);
//        ofDrawCircle(20,20,20);
//        ofPopStyle();
//    }
//
//    // display received messages/requests
//    stringstream receiveOutput;
//    receiveOutput << "RECEIVED MESSAGES..." << endl;
//    receiveOutput << svgString << endl;
////    for(int i = receivedMessages.size()-1; i >= 0; i--) {
////        receiveOutput << receivedMessages[i] << endl;
////    }
//    ofSetColor(0);
//    ofDrawBitmapString(receiveOutput.str(), 20, 80);
//
    
    
    ofxSVG& svg = receiver.svg;
    
    for(int i=0; i<svg.getNumPath(); i++ ) {
        ofPath& path = svg.getPathAt(i);
        
        const vector<ofPolyline>& lines = path.getOutline();
        
        ofColor col = path.getStrokeColor();
        ofSetColor(col);
        
        for(int j=0; j<lines.size(); j++) {
            ofPolyline line = lines[j];
            line.draw();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
   
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
//
//    if(server.getNumClients()) {
//        string message = "Hello from server " + ofToString(sentMessages.size());
//        server.sendMessageToAll(message);
//        sentMessages.push_back(message);
//    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
