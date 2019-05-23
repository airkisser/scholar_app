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
struct RequestParams;

class NetworkUtils
{
	const char* APPLICATION_JSON_UTF8 = "Content-Type: application/json; charset=utf-8";
public:
	/**
	 * 获取单例
	 */
	static NetworkUtils* getInstance();
	/*
	 * 销毁单例
	 */
	void destroyInstance();

	/*
	 * 执行请求
	 */
	void doRequest(const RequestParams &params);

	void setDelegate(NetworkDelegate *delegate);

protected:
	void beforeRequest(HttpRequest* request, bool auth);
	void onRequestCompleted(HttpClient* client, HttpResponse* response);

private:
	NetworkUtils();
	~NetworkUtils();

	NetworkDelegate* m_delegate;
};

struct RequestParams
{
	HttpRequest::Type           requestType = HttpRequest::Type::GET; // 请求类型,默认为GET
	bool						isImmediate = false;	// 是否使用单独的线程立即执行，true-使用单独的线程执行请求, 
														//		false-添加到队列用同一线程执行，默认值：false
	bool						isAuth = false;			// 是否需要添加Token进Header，默认值：false
	std::string                 url;					// 要请求的URL完整路径
	std::string                 tag;					// user defined tag, to identify different requests in response callback
	std::vector<char>           requestData;			// used for POST/PUT/PATCH
	std::vector<std::string>    headers;				// custom http headers
};


class NetworkDelegate
{
public:
	virtual void OnNetworkSuccess(HttpClient* sender, HttpResponse* response){};
	virtual void OnNetworkError(HttpClient* sender, HttpResponse* response){};
};

#endif //PROJ_ANDROID_NETWORKUTILS_H
