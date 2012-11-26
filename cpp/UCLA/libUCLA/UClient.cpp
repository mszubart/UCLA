#include "UClient.h"
#include "config.h"

#ifdef UCLA_HAVE_UNIX
#include <xs/xs.hpp>
#else
#include <xs.hpp>
#endif

using namespace UCLA;

UClient::UClient(UConfig &config, bool autostart){
	this->_isStarted = false;
	this->_ctx = NULL;
	this->_sock = NULL;
	this->_endpoint = NULL;

	CopyEndpoint(config.Endpoint());

	if(autostart){
		Start();
	}
}

UClient::UClient(UClient&& that){
	if(this->_isStarted)
	{
		this->CleanUpXS();
	}

	this->_isStarted = false;
	this->_ctx = NULL;
	this->_sock = NULL;
	this->_endpoint = NULL;

	CopyEndpoint(that.Endpoint());

	that.~UClient();
}

UClient& UClient::operator=(UClient&& that){
	if (this != &that){
		if(this->_isStarted)
		{
			this->CleanUpXS();
		}

		this->_isStarted = false;
		this->_ctx = NULL;
		this->_sock = NULL;

		CopyEndpoint(that.Endpoint());

		that.~UClient();
	}

	return *this;
}

void UClient::CopyEndpoint(const char* endpoint){
	using namespace Utils;

	if(this->_endpoint != NULL)
		delete[] this->_endpoint;

	int strLength = strlen(endpoint) + 1;

	char* tmp_endpoint = new char[strLength];
	this->_endpoint = tmp_endpoint;

	m_strlcpy(this->_endpoint, strLength, endpoint);
}

void UClient::Start(void){
	if(this->_isStarted){
		return;
	}

	try{
		this->_ctx = new xs::context_t();
		this->_sock = new xs::socket_t(*(static_cast<xs::context_t*>(this->_ctx)), XS_PUSH);

		static_cast<xs::socket_t*>(this->_sock)->connect(this->_endpoint);
	}catch(xs::error_t &err){
		throw UException(err.what());
	}

	this->_isStarted = true;
}

void UClient::SendData(const char *buf, size_t len, bool nonBlocking){
	if(!this->_isStarted){
		Start();
	}

	try{
		static_cast<xs::socket_t*>(this->_sock)->send(buf, len, nonBlocking? XS_DONTWAIT : 0);
	}catch(xs::error_t &err){
		throw UException(err.what());
	}
}

bool UClient::IsStarted(void) const{
	return this->_isStarted;
}

void UClient::CleanUpXS(void){
	if(this->_sock != NULL){
		static_cast<xs::socket_t*>(this->_sock)->close();
		delete static_cast<xs::socket_t*>(this->_sock);

		this->_sock = NULL;
	}

	if(this->_ctx != NULL){
		delete static_cast<xs::context_t*>(this->_ctx);

		this->_ctx = NULL;
	}
}

UClient::~UClient(void){
	this->_isStarted = false;

	delete[] this->_endpoint;
	this->_endpoint = NULL;

	this->CleanUpXS();
}
