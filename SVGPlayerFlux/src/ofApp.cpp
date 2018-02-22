#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	
    //receiver.start(4445);
    
    initLaser();
    initGui();
    

    guideImage.load("MASTER_ELEVATION_BOTH.jpg");
    svgLoader.load("svgs/");
    music.load("Flux part 1 Maquette V1.wav");
    music.play();
    music.setPosition(0.5f);
    musicDurationMS = 2 * music.getPositionMS();
    musicPositionMS = 0;
    music.stop(); 
    
  
	 
}

void ofApp::initLaser() {
    
    laserWidth = 1200;
    laserHeight = 700;
    laser.setup(laserWidth, laserHeight);
    
    laser.addProjector(dac1);
    laser.addProjector(dac2);
    
    ofBuffer buffer = ofBufferFromFile("dac1IP.txt");
    string dac1Ip = buffer.getText();
    if(dac1Ip=="") dac1Ip ="169.254.70.201";
    dac1.setup(dac1Ip);
    
    buffer = ofBufferFromFile("dac21IP.txt");
    string dac2Ip = buffer.getText();
    if(dac2Ip=="") dac2Ip ="169.254.70.201";
    dac2.setup(dac2Ip);
    
    int numzones = 6;
    
    // more complex, create zones first
    for(int i = 0; i<numzones; i++) {
        laser.addZone(laser.width-((20-i)*30),0,30,100);
    }
    for(int i = 0; i<numzones; i++) {
        laser.addZoneToProjector(i,0);
        laser.addZoneToProjector(i,1);
    }
}
void ofApp:: initGui() {
 
    laser.initGui();
    laser.gui.loadFont("Verdana.ttf", 8, false);
    
    ofParameterGroup params;
    params.add(scale.set("SVG scale", 2, 0.1,3));
    params.add(showGuide.set("Show guide image", true));
    params.add(guideBrightness.set("Guide Brightness", 150,0,255));
    
    laser.gui.add(params);
    currentSVG = 0;
    
    ofxPanel *projgui = (laser.getProjector(0).gui);
    
    projgui->minimizeAll();
    ofxGuiGroup* g;
    //    g = dynamic_cast <ofxGuiGroup *>(gui->getControl(projectorlabel));
    //    if(g) g->maximize();
    g = dynamic_cast <ofxGuiGroup *>(projgui->getControl("Projector settings"));
    if(g) g->maximize();
    
    g = dynamic_cast <ofxGuiGroup *>(g->getControl("Output position offset"));
    if(g) g->minimize();
    
    ofxGuiGroup* profiles = dynamic_cast <ofxGuiGroup *>(projgui->getControl("Render profiles"));
    if(profiles){
        profiles->maximize();
        g = dynamic_cast <ofxGuiGroup *>(profiles->getControl("High quality"));
        if(g) g->minimize();
        g = dynamic_cast <ofxGuiGroup *>(profiles->getControl("Fast"));
        if(g) g->minimize();
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
	float deltaTime = ofClamp(ofGetLastFrameTime(), 0, 0.2);
	elapsedTime+=deltaTime;
    laser.update();
    if(music.isPlaying()) {
        musicPositionMS = music.getPositionMS();
    }
    //receiver.update();
}


void ofApp::draw() {
	
    ofBackground(0);
    
	 
    if(laser.currentProjector<0) {
        if(showGuide){
            ofPushStyle();
            
            ofNoFill();
            ofSetLineWidth(1);
            ofDrawRectangle(0,0,laserWidth, laserHeight);
            
            ofSetColor(guideBrightness);
            
            guideImage.setAnchorPercent(0.5, 0.5);
            ofPushMatrix();
            //ofTranslate(10,10);
            ofTranslate(laser.width/2, laser.height/2);
            ofScale(laser.height/guideImage.getHeight(), laser.height/guideImage.getHeight());
            guideImage.draw(0,0);
            
            
            ofPopMatrix();
            ofPopStyle();
        }
    }
    
    
    
    
    //guide.draw(0,0,laserWidth, laserHeight);
	int ypos = laserHeight+10;
    int xpos = 660;
	
   ofDrawBitmapString("'F' to toggle fullscreen", xpos, ypos+=20);
    ofDrawBitmapString("'TAB' to toggle laser preview mode", xpos, ypos+=20);
    ofDrawBitmapString("Adjust Render Profiles -> Default to affect laser speed", xpos, ypos+=20);
    
    int laserframerate1 = laser.getProjectorFrameRate(0);
    int laserframerate2 = laser.getProjectorFrameRate(1);
    
    ofDrawBitmapString(ofToString(laserframerate1), 20, 20);
    ofDrawBitmapString(ofToString(laserframerate2), 30, 20);
  //  ofDrawBitmapString(ofToString(musicPositionMS), 20, 40);
    ofNoFill();
    ofDrawRectangle(0,ofGetHeight()-10, ofGetWidth(), 10);
    ofFill();
    float musicbarwidth =ofMap(musicPositionMS,0,musicDurationMS, 0, ofGetWidth());
    ofDrawRectangle(0,ofGetHeight()-10, musicbarwidth, 10);
    
    
    ofPushMatrix();

    ofVec2f pos(400,400);

    int frame = (float)musicPositionMS/1000.0f*30.0f;
    ofxSVG& svg = svgLoader.getSvg(frame);
 
   ofVec3f centrePoint = ofVec3f(svg.getWidth()/2, svg.getHeight()/2);

    for(int i=0; i<svg.getNumPath(); i++ ) {
        ofPath& path = svg.getPathAt(i);

        const vector<ofPolyline>& lines = path.getOutline();

        ofColor col = path.getStrokeColor();

        if(col.getBrightness()<30) col = ofColor::white;

        for(int j=0; j<lines.size(); j++) {
            ofPolyline line = lines[j];

            vector<ofVec3f>& vertices = line.getVertices();
            for(int i = 0; i<vertices.size(); i++) {
                ofVec3f& v = vertices[i];
                v-=centrePoint;
                //v.rotate(rotation.x, ofPoint(1,0,0));
                //v.rotate(rotation.y, ofPoint(0,1,0));
                //v.rotate(rotation.z, ofPoint(0,0,1));
                v*=scale;
                v+=pos;
            }

            //line.simplify(0.1);
            //cout << "brightness : " << brightness << endl;
           // ofLog(line.isClosed());
            laser.drawPoly(line,col);
        }
    }
    


    ofPopMatrix();
    laser.send();
    laser.drawUI();

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
   
    if(key =='c') {
        polyLines.clear();
    }if(key =='f') {
        ofToggleFullscreen();
	}
    if(key == 'p') {
        if(music.isPlaying()) {
            
            music.stop();
            
        } else {
            music.play();
            music.setPositionMS(musicPositionMS);
        }
        
    }
    if(key == OF_KEY_DOWN) {
        
        music.setPositionMS(0);
        music.play();
        
    }
    
    if(key == OF_KEY_LEFT) {
        musicPositionMS -=5000;
        music.setPositionMS(musicPositionMS);
        
    } else if(key == OF_KEY_RIGHT) {
        musicPositionMS +=5000;
         music.setPositionMS(musicPositionMS);
        
    }
    
    if(key==OF_KEY_TAB) laser.nextProjector();

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if(!drawingShape) return;
	
	ofPolyline &poly = polyLines.back();
	//if(poly.getofVec3f end =poly.getVertices().back();
	//if(ofDist(x, y, end.x, end.y) > 5) {
		//poly.simplify();
	poly.addVertex(x, y);
	
	//}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	polyLines.push_back(ofPolyline());
	drawingShape = true;
}

void ofApp::mouseReleased(int x, int y, int button) {
	if(drawingShape) {
		ofPolyline &poly = polyLines.back();
		poly = poly.getSmoothed(2);
		drawingShape = false;
	}
	// TODO add dot if the line is super short
	
}

void ofApp::windowResized(int x, int y) {
    laser.updateScreenSize();
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    laser.saveSettings();
    dac1.close();
}
