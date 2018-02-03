//
//  TCPSVGReceiver.cpp
//  PocoTCPServerAddon
//
//  Created by Seb Lee-Delisle on 03/02/2018.
//

#include "TCPSVGReceiver.h"


void TCPSVGReceiver::start(int port) {
   
    server.start(4445, ofxPocoNetwork::FRAME_NONE);
    
}

bool TCPSVGReceiver::update() {
    
    receivedMsg = false;
    newSVG = false;
    // check server for incoming messages from all clients
    for(int i = 0; i < server.getNumClients(); i++) {
        
        while(server.hasWaitingMessages(i)) {
            
            string tmp;
            receivedMsg = server.getNextMessage(i, tmp);
            if(receivedMsg) {
                //receivedMessages.push_back(message);
                message.append(tmp);
                string delimiter = "</svg>";
                
                size_t pos = message.find(delimiter);
                while( pos!=string::npos) {
                    
                    // ofLog(OF_LOG_NOTICE, "FOUND at "+ofToString(pos));
                    
                    svgString = message.substr(0,pos+6);
                    message = message.substr(pos+6);
                    pos = message.find(delimiter);
                    newSVG = true;
                }
            }
        }
    }
    
    if(newSVG) {
        string url = "url";
        svg.loadFromData(svgString.c_str(), svgString.size(), url.c_str());
    }

    return newSVG; 
}
