#include "UServer.h"
#include "config.h"

#ifdef UCLA_HAVE_UNIX
#include <xs/xs.hpp>
#else
#include <xs.hpp>
#endif

using namespace UCLA;

UServer::UServer(UConfig &config, bool autostart){
	this->_isStarted = false;
	this->_receive_handler = NULL;
	this->_ctx = NULL;
	this->_sock = NULL;
	this->_endpoint = NULL;

	CopyEndpoint(config.Endpoint());

	if(autostart){
		Start();
	}
}

void UServer::Start(void){
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

void UServer::Receive(void){
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

	if(this->_receive_handler != NULL){
		this->_receive_handler(buf, received_len);
	}

	delete[] buf;
}

void UServer::Run(void){
	while(true){
		this->Receive();
	}
}

void UServer::SetupReceiveHandler(UCLA_RECEIVE_HANDLER handler){
	this->_receive_handler = handler;
}

UServer::UServer(UServer &&that){
	if(this->_isStarted)
	{
		this->CleanUpXS();
	}

	this->_isStarted = false;
	this->_ctx = NULL;
	this->_sock = NULL;
	this->_endpoint = NULL;

	CopyEndpoint(that.Endpoint());

	that.~UServer();
}

UServer& UServer::operator=(UServer&& that){
	if (this != &that){
		if(this->_isStarted)
		{
			this->CleanUpXS();
		}

		this->_isStarted = false;
		this->_ctx = NULL;
		this->_sock = NULL;

		CopyEndpoint(that.Endpoint());

		that.~UServer();
	}

	return *this;
}

void UServer::CopyEndpoint(const char* endpoint){
	using namespace Utils;

	if(this->_endpoint != NULL)
		delete[] this->_endpoint;

	int strLength = strlen(endpoint) + 1;

	char* tmp_endpoint = new char[strLength];
	this->_endpoint = tmp_endpoint;

	m_strlcpy(this->_endpoint, strLength, endpoint);
}

bool UServer::IsStarted(void) const{
	return this->_isStarted;
}

void UServer::CleanUpXS(void){
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

UServer::~UServer(void){
	this->_isStarted = false;

	delete[] this->_endpoint;
	this->_endpoint = NULL;

	CleanUpXS();
}
