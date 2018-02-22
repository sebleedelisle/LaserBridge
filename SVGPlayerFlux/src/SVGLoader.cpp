//
//  SVGLoader.cpp
//  SVGPlayerFlux
//
//  Created by Seb Lee-Delisle on 22/02/2018.
//

#include "SVGLoader.h"


void SVGLoader:: load(string path) {
    
    ofDirectory dir(path);
    
    //only show svg files
    dir.allowExt("svg");
    //populate the directory object
    dir.listDir();
    dir.sort();
    
//
    
    const vector<ofFile>& origfiles = dir.getFiles();
    vector<ofFile> files(origfiles);
    ofSort(files, sortalgo);
    
    svgs.resize(files.size());
    fileNames.resize(files.size());
    
    
    for(int i = 0; i<files.size();i++) {
        const ofFile & file = files.at(i);
        svgs[i].load(file.getAbsolutePath());
        ofLog(OF_LOG_NOTICE,file.getFileName());
        fileNames[i] = file.getFileName();
        
    }

}

ofxSVG&  SVGLoader::getSvg(int index) {
    index = index %svgs.size();
    return svgs.at(index); 
    
}
