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
#include "Poco/Net/HTTPRequest.h"

class ofxHttpUtilsPlus : public ofxHttpUtils {

public:
    
    ofxHttpUtilsPlus();
    ~ofxHttpUtilsPlus();
    
    ofxHttpResponse putData(string url, const ofBuffer & data, string contentType="", string method = Poco::Net::HTTPRequest::HTTP_PUT);
};


#endif /* defined(__ofxHttpUtilsPlus__) */
