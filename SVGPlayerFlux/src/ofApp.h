#pragma once

#include "ofMain.h"
#include "ofxLaserManager.h"
#include "ofxLaserDacEtherdream.h"
#include "ofxGui.h"
#include "ofxSvgFromString.h"
#include "TCPSVGReceiver.h"
#include "SVGLoader.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
    
    void initLaser(); 
    void initGui();
    
	void exit();
    
	
	void keyPressed  (int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
    void windowResized(int x, int y);
	
	void showLaserEffect(int effectnum);
	
    ofParameter<int> currentSVG;
    ofParameter<float> scale;

    ofParameter<bool>showGuide;
    ofParameter<int>guideBrightness;

    SVGLoader svgLoader;
    ofSoundPlayer music;
    float musicPositionMS;
    float musicDurationMS;
    
    ofImage guideImage;
   
	ofxLaser::Manager laser;
    ofxLaser::DacEtherdream dac1;
    ofxLaser::DacEtherdream dac2;
    
	int laserWidth;
	int laserHeight;
    
	bool drawingShape = false;
	vector<ofPolyline> polyLines;
		
	float elapsedTime;
    
    //TCPSVGReceiver receiver;
    

};

