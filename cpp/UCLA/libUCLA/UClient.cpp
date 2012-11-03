#include "UClient.h"

using namespace UCLA;

UClient::UClient(UConfig &config, bool autostart): _endpoint(config.Endpoint()){
	this->_isStarted = false;
	this->_ctx = NULL;
	this->_sock = NULL;

	this->_endpoint = config.Endpoint();

	if(autostart){
		Start();
	}
}

void UClient::Start(void){
	if(this->_isStarted){
		return;
	}

	this->_ctx = new xs::context_t();
	this->_sock = new xs::socket_t(*(this->_ctx), XS_PUSH);

	this->_sock->connect(this->_endpoint);

	this->_isStarted = true;
}

void UClient::SendData(const char *buf, size_t len, bool nonBlocking){
	if(!this->_isStarted){
		Start();
	}

	this->_sock->send(buf, len, nonBlocking? XS_DONTWAIT : 0);
}

bool UClient::IsStarted(void){
	return this->_isStarted;
}

UClient::~UClient(void){
	if(this->_sock != NULL){
		this->_sock->close();
		delete this->_sock;

		this->_sock = NULL;
	}

	if(this->_ctx != NULL){
		delete this->_ctx;

		this->_ctx = NULL;
	}
}
