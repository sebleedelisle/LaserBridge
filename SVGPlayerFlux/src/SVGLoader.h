//
//  SVGLoader.h
//
//  Created by Seb Lee-Delisle on 22/02/2018.
//

#pragma once
#include "ofMain.h"
#include "ofxSvg.h"

class SVGLoader {
    
    public :
    
    void load(string path);
    
    vector<ofxSVG> svgs;
    vector<string> fileNames;
    
    ofxSVG & getSvg(int index);
    
    static bool sortalgo(const ofFile& a, const ofFile& b) {
        string aname = a.getBaseName(), bname = b.getBaseName();
        return strcasecmp_withNumbers(aname.c_str(), bname.c_str()) < 0;
        
    }
    
    static int strcasecmp_withNumbers(const char *void_a, const char *void_b) {
        const char *a = void_a;
        const char *b = void_b;
        
        if (!a || !b) { // if one doesn't exist, other wins by default
            return a ? 1 : b ? -1 : 0;
        }
        if (isdigit(*a) && isdigit(*b)) { // if both start with numbers
            char *remainderA;
            char *remainderB;
            long valA = strtol(a, &remainderA, 10);
            long valB = strtol(b, &remainderB, 10);
            if (valA != valB)
                return valA - valB;
            // if you wish 7 == 007, comment out the next two lines
            else if (remainderB - b != remainderA - a) // equal with diff lengths
                return (remainderB - b) - (remainderA - a); // set 007 before 7
            else // if numerical parts equal, recurse
                return strcasecmp_withNumbers(remainderA, remainderB);
        }
        if (isdigit(*a) || isdigit(*b)) { // if just one is a number
            return isdigit(*a) ? -1 : 1; // numbers always come first
        }
        while (*a && *b) { // non-numeric characters
            if (isdigit(*a) || isdigit(*b))
                return strcasecmp_withNumbers(a, b); // recurse
            if (tolower(*a) != tolower(*b))
                return tolower(*a) - tolower(*b);
            a++;
            b++;
        }
        return *a ? 1 : *b ? -1 : 0;
    }
   
};
