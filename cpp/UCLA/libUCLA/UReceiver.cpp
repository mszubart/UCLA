#include "UReceiver.h"
#include "config.h"

#ifdef UCLA_HAVE_UNIX
#include <xs/xs.hpp>
#else
#include <xs.hpp>
#endif

using namespace UCLA;

UReceiver::UReceiver(UConfig &config, std::function<void(char*, int)> handler, bool autostart): _receive_handler(handler){
	this->_isStarted = false;
	this->_ctx = NULL;
	this->_sock = NULL;
	this->_endpoint = NULL;

	CopyEndpoint(config.Endpoint());

	if(autostart){
		Start();
	}
}

void UReceiver::Start(void){
	if(this->_isStarted){
		return;
	}

	try{
		this->_ctx = new xs::context_t();
		this->_sock = new xs::socket_t(*(static_cast<xs::context_t*>(this->_ctx)), XS_PULL);

		static_cast<xs::socket_t*>(this->_sock)->bind(this->_endpoint);
	}catch(xs::error_t &err){
		throw UException(err.what());
	}

	this->_isStarted = true;
}

void UReceiver::Receive(void){
	if(!this->_isStarted){
		this->Start();
	}

	char *buf = new char[UCLA_MAX_MESSAGE_LEN];
	int received_len = -1;

	try{
		received_len = static_cast<xs::socket_t*>(this->_sock)->recv(buf, UCLA_MAX_MESSAGE_LEN);
	}catch(xs::error_t &err){
		throw UException(err.what());
	}

	this->_receive_handler(buf, received_len);

	delete[] buf;
}

void UReceiver::Run(void){
	while(true){
		this->Receive();
	}
}

void UReceiver::SetupReceiveHandler(std::function<void(char*, int)> handler){
	this->_receive_handler = handler;
}

UReceiver::UReceiver(UReceiver &&that): _receive_handler(that._receive_handler){
	if(this->_isStarted)
	{
		this->CleanUpXS();
	}

	this->_isStarted = false;
	this->_ctx = NULL;
	this->_sock = NULL;
	this->_endpoint = NULL;
	that._receive_handler = nullptr;

	CopyEndpoint(that.Endpoint());

	that.~UReceiver();
}

UReceiver& UReceiver::operator=(UReceiver&& that){
	if (this != &that){
		if(this->_isStarted)
		{
			this->CleanUpXS();
		}

		this->_isStarted = false;
		this->_ctx = NULL;
		this->_sock = NULL;
		this->_receive_handler = that._receive_handler;
		that._receive_handler = nullptr;

		CopyEndpoint(that.Endpoint());

		that.~UReceiver();
	}

	return *this;
}

void UReceiver::CopyEndpoint(const char* endpoint){
	using namespace Utils;

	if(this->_endpoint != NULL)
		delete[] this->_endpoint;

	int strLength = strlen(endpoint) + 1;

	char* tmp_endpoint = new char[strLength];
	this->_endpoint = tmp_endpoint;

	m_strlcpy(this->_endpoint, strLength, endpoint);
}

bool UReceiver::IsStarted(void) const{
	return this->_isStarted;
}

void UReceiver::CleanUpXS(void){
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

UReceiver::~UReceiver(void){
	this->_isStarted = false;

	delete[] this->_endpoint;
	this->_endpoint = NULL;

	CleanUpXS();
}
