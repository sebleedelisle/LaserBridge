#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	
    receiver.start(4445);
    
	laserWidth = 800;
	laserHeight = 800;
	laser.setup(laserWidth, laserHeight);

    laser.addProjector(dac);
    
    ofBuffer buffer = ofBufferFromFile("dacIP.txt");
    string dacIp = buffer.getText();
    if(dacIp=="") dacIp ="169.254.70.201";
    dac.setup(dacIp);
	
    laser.initGui();
    laser.gui.loadFont("Verdana.ttf", 8, false);
    
    ofParameterGroup params;
    params.add(scale.set("SVG scale", 1, 0.1,3));
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
    receiver.update();
}


void ofApp::draw() {
	

	ofBackground(0);
    
   
	ofNoFill();
	ofSetLineWidth(1);
	ofDrawRectangle(0,0,laserWidth, laserHeight);
    
	int ypos = laserHeight+10;
    int xpos = 360;
	
   ofDrawBitmapString("'F' to toggle fullscreen", xpos, ypos+=20);
    ofDrawBitmapString("'TAB' to toggle laser preview mode", xpos, ypos+=20);
    ofDrawBitmapString("Adjust Render Profiles -> Default to affect laser speed", xpos, ypos+=20);
    
   
    int laserframerate = laser.getProjectorFrameRate(0); 
    ofDrawBitmapString("Laser framerate : " + ofToString(laserframerate), 20, 20);
    
    ofPushMatrix();
    //ofTranslate(-300,-100);
    //ofScale(2,2);
    //float scale = 2;
    ofVec2f pos(400,400);

    ofxSVGFromString& svg = receiver.svg;

    //laserManager.addLaserSVG(birdSVGs[currentBirdSVG], ofPoint(xpos, ypos), ofPoint(1,1), ofPoint(0,0,rotation));
    
   ofVec3f centrePoint = ofVec3f(svg.getWidth()/2, svg.getHeight()/2);
    //ofRectangle svgRect;
    //bool firstpoint = true;
    
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
    
//    ofNoFill();
//    svg.draw();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
   
    if(key =='c') {
        polyLines.clear();
    }if(key =='f') {
        ofToggleFullscreen();
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
    dac.close();
}
