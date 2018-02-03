//
//  TCPSVGReceiver.h
//  PocoTCPServerAddon
//
//  Created by Seb Lee-Delisle on 03/02/2018.
//

#pragma once

#include "ofxSvg.h"
#include "ofMain.h"
#include "ofxPocoNetwork.h"

class TCPSVGReceiver {
    
    public :
    
    //TCPSVGReceiver();
    
    void start(int port);
    bool update();
    
    ofxPocoNetwork::TCPServer server;

    vector<string> sentMessages;
    vector<string> receivedMessages;

    string message;
    string svgString;
    bool receivedMsg;
    bool newSVG;
    ofxSVG svg;
};
