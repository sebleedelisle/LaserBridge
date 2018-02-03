#pragma once

#include "ofMain.h"
#include "ofxLaserManager.h"
#include "ofxLaserDacEtherdream.h"
#include "ofxGui.h"
#include "ofxSvg.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed  (int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
    void windowResized(int x, int y);
	
	void showLaserEffect(int effectnum);
	
    ofParameter<int> currentSVG;
    ofParameter<float> scale;
    
    vector<ofxSVG> svgs;
    vector<string> fileNames; 
	
	ofxLaser::Manager laser;
    ofxLaser::DacEtherdream dac;
	
	int laserWidth;
	int laserHeight;
    
	bool drawingShape = false;
	vector<ofPolyline> polyLines;
		
	float elapsedTime; 

};

