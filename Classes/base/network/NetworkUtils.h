//
// Created by junluo on 2019/5/23.
//

#ifndef PROJ_ANDROID_NETWORKUTILS_H
#define PROJ_ANDROID_NETWORKUTILS_H

#include "cocos2d.h"
#include "HttpClient.h"

USING_NS_CC;
using namespace cqdn::network;

class NetworkDelegate;

class NetworkUtils {
public:
    static NetworkUtils *getInstance();
    void destroyInstance();
    void doRequest(HttpRequest *request, bool immediately = false);

protected:
    void beforeRequest(HttpRequest *request);
    void afterRequest(HttpRequest *request);

private:
    NetworkUtils();
    ~NetworkUtils();
//
//    NetworkDelegate *delegate;
};

class NetworkDelegate{
public:
    virtual void OnNetworkSuccess(HttpClient * sender, HttpResponse * response) = 0;
    virtual void OnNetworkError(HttpClient * sender, HttpResponse * response) = 0;
};

#endif //PROJ_ANDROID_NETWORKUTILS_H
