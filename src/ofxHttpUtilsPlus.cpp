//
//  ofxHttpUtilsPlus.cpp
//  hueControlSample
//
//  Created by hiroshi yamato on 4/15/15.
//
//

#include "ofxHttpUtilsPlus.h"

//#include "Poco/Net/SSLManager.h"
#include "Poco/Net/HTTPSClientSession.h"
//#include "Poco/Net/ConsoleCertificateHandler.h"
//#include "Poco/Net/FilePartSource.h"
//#include "Poco/Net/StringPartSource.h"
//#include "Poco/Net/KeyConsoleHandler.h"
//#include "Poco/Net/HTTPSession.h"
//#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
//#include "Poco/Net/HTMLForm.h"
//#include "Poco/StreamCopier.h"
//#include "Poco/Path.h"
#include "Poco/URI.h"
//#include "Poco/Exception.h"

//using namespace std;
using namespace Poco;
using namespace Poco::Net;

ofxHttpUtilsPlus::ofxHttpUtilsPlus(){

}

ofxHttpUtilsPlus::~ofxHttpUtilsPlus(){
    
}

ofxHttpResponse ofxHttpUtilsPlus::putData(string url, const ofBuffer &data, string contentType, string method){
    ofxHttpResponse response;
    try{
        URI uri( url.c_str() );
        std::string path(uri.getPathAndQuery());
        if (path.empty()) path = "/";
        
        //HTTPClientSession session(uri.getHost(), uri.getPort());
        HTTPRequest req(method, path, HTTPMessage::HTTP_1_1);
        if(auth.getUsername()!="") auth.authenticate(req);
        
        if(sendCookies){
            for(unsigned i=0; i<cookies.size(); i++){
                NameValueCollection reqCookies;
                reqCookies.add(cookies[i].getName(),cookies[i].getValue());
                req.setCookies(reqCookies);
            }
        }
        
        if(contentType!=""){
            req.setContentType(contentType);
        }
        
        req.setContentLength(data.size());
        
        HTTPResponse res;
        ofPtr<HTTPSession> session;
        istream * rs;
        if(uri.getScheme()=="https"){
            HTTPSClientSession * httpsSession = new HTTPSClientSession(uri.getHost(), uri.getPort());//,context);
            httpsSession->setTimeout(Poco::Timespan(20,0));
            httpsSession->sendRequest(req) << data;
            rs = &httpsSession->receiveResponse(res);
            session = ofPtr<HTTPSession>(httpsSession);
        }else{
            HTTPClientSession * httpSession = new HTTPClientSession(uri.getHost(), uri.getPort());
            httpSession->setTimeout(Poco::Timespan(20,0));
            httpSession->sendRequest(req) << data;
            rs = &httpSession->receiveResponse(res);
            session = ofPtr<HTTPSession>(httpSession);
        }
        
        response = ofxHttpResponse(res, *rs, url);
        
        if(sendCookies){
            cookies.insert(cookies.begin(),response.cookies.begin(),response.cookies.end());
        }
        
        if(response.status>=300 && response.status<400){
            Poco::URI uri(req.getURI());
            uri.resolve(res.get("Location"));
            response.location = uri.toString();
        }
        
        ofNotifyEvent(newResponseEvent, response, this);
    }catch (Exception& exc){
        
        ofLogError("ofxHttpUtils") << "ofxHttpUtils error postData--";
        
        //ofNotifyEvent(notifyNewError, "time out", this);
        
        // for now print error, need to broadcast a response
        ofLogError("ofxHttpUtils") << exc.displayText();
        response.status = -1;
        response.reasonForStatus = exc.displayText();
        ofNotifyEvent(newResponseEvent, response, this);
        
    }
    return response;

}
