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
	 * ��ȡ����
	 */
	static NetworkUtils* getInstance();
	/*
	 * ���ٵ���
	 */
	void destroyInstance();

	/*
	 * ִ������
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
	HttpRequest::Type           requestType = HttpRequest::Type::GET; // ��������,Ĭ��ΪGET
	bool						isImmediate = false;	// �Ƿ�ʹ�õ������߳�����ִ�У�true-ʹ�õ������߳�ִ������, 
														//		false-��ӵ�������ͬһ�߳�ִ�У�Ĭ��ֵ��false
	bool						isAuth = false;			// �Ƿ���Ҫ���Token��Header��Ĭ��ֵ��false
	std::string                 url;					// Ҫ�����URL����·��
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
