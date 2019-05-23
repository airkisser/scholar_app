//
// Created by junluo on 2019/5/23.
//

#include "NetworkUtils.h"

using namespace cqdn::network;

static NetworkUtils* instance = nullptr;

NetworkUtils* NetworkUtils::getInstance()
{
	if (instance == nullptr)
	{
		instance = new NetworkUtils();
	}
	return instance;
}

void NetworkUtils::destroyInstance()
{
	CC_SAFE_DELETE(instance);
}

NetworkUtils::NetworkUtils(): m_delegate(nullptr)
{
	// 设置连接超时时间
	HttpClient::getInstance()->setTimeoutForConnect(1);
	// 设置读超时时间
	HttpClient::getInstance()->setTimeoutForRead(3);
}

NetworkUtils::~NetworkUtils()
{
	HttpClient::destroyInstance();
}

void NetworkUtils::doRequest(const RequestParams &params)
{
	HttpRequest *request = new HttpRequest();
	request->setRequestType(params.requestType);
	request->setUrl(params.url);
	request->setTag(params.tag);
	if(!params.requestData.empty())
	{
		std::string tmp(params.requestData.begin(), params.requestData.end());
		request->setRequestData(tmp.data(), tmp.size());
	}
	this->beforeRequest(request, params.isAuth);
	if (params.isImmediate)
	{
		log("%s", "HttpClient send request immediately.");
		HttpClient::getInstance()->sendImmediate(request);
	}
	else
	{
		log("%s", "HttpClient send request.");
		HttpClient::getInstance()->send(request);
	}
	request->release();
}

void NetworkUtils::setDelegate(NetworkDelegate* delegate)
{
	m_delegate = delegate;
}

void NetworkUtils::beforeRequest(HttpRequest* request, bool auth)
{
	std::vector<std::string> headers = request->getHeaders();
	request->setResponseCallback(CC_CALLBACK_2(NetworkUtils::onRequestCompleted, this));
	if(auth)
	{
		// @TODO 从配置中读取Token信息
		headers.emplace_back("Authorization:Bearer 填充Token");
	}
	request->setHeaders(headers);
}

void NetworkUtils::onRequestCompleted(HttpClient* client, HttpResponse* response)
{
	if (!response) 
	{
		log("%s", "Error: Response is null!");
	}

	auto request = response->getHttpRequest();
	std::string tag = request->getTag();
	long statusCode = response->getResponseCode();
	
	if(response->isSucceed())
	{// 状态码在[200,300)之间
		log("Request succeed, HTTP Status Code: %ld, tag = %s", statusCode, tag.empty() ? "null" : tag);
		std::vector<char>* responseHeader = response->getResponseHeader();
		// @TODO 解析数据
	}
	else
	{
		log("Request succeed, HTTP Status Code: %ld, tag = %s, error: ", statusCode, tag.empty() ? "null" : tag, 
			response->getErrorBuffer());
		// 处理常用的错误码
		switch (statusCode)
		{
		case 400:
			break;
		case 401:
			break;
		case 403:
			break;
		default:
			break;
		}
	}

	if (!response->isSucceed())
	{
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}

	// dump data
	std::vector<char> *buffer = response->getResponseData();
}
