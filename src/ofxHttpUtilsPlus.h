//
//  ofxHttpUtilsPlus.h
//
//  Created by hiroshi yamato on 4/15/15.
//
//

#ifndef __ofxHttpUtilsPlus__
#define __ofxHttpUtilsPlus__

#include <stdio.h>
#include "ofxHttpUtils.h"

class ofxHttpUtilsPlus : public ofxHttpUtils {

public:
    
    ofxHttpUtilsPlus();
    ~ofxHttpUtilsPlus();
    
    ofxHttpResponse putData(string url, const ofBuffer & data, string contentType="");
    
};


#endif /* defined(__ofxHttpUtilsPlus__) */
