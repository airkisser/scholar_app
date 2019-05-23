//
// Created by junluo on 2019/5/23.
//

#include "NetworkUtils.h"

using namespace cqdn::network;

static NetworkUtils *instance = nullptr;

NetworkUtils *NetworkUtils::getInstance() {
    if (instance == nullptr) {
        instance = new NetworkUtils();
    }
    return instance;
}

void NetworkUtils::destroyInstance() {
    CC_SAFE_DELETE(instance);
}

NetworkUtils::NetworkUtils() {
    // 设置连接超时时间
    HttpClient::getInstance()->setTimeoutForConnect(1);
    // 设置读超时时间
    HttpClient::getInstance()->setTimeoutForRead(3);
}

NetworkUtils::~NetworkUtils() {
    HttpClient::destroyInstance();
}

void NetworkUtils::doRequest(HttpRequest *request, bool immediately) {
    if (!request) {
        CCLOG("%s", "Request can not be null.");
        return;
    }
    this->beforeRequest(request);
    if (immediately) {
        HttpClient::getInstance()->sendImmediate(request);
    } else {
        HttpClient::getInstance()->send(request);
    }
}

void NetworkUtils::beforeRequest(HttpRequest *request) {
    std::vector<std::string> headers = request->getHeaders();
    headers.emplace_back("Authorization:Bearer 填充Token");
//    request->set
    request->setHeaders(headers);
}

void NetworkUtils::afterRequest(HttpRequest *request) {

}