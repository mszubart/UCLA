#include "UServer.h"

UServer::UServer(UConfig &config, bool autostart){
	this->_isStarted = false;
	this->_receive_handler = NULL;
	this->_ctx = NULL;
	this->_sock = NULL;

	this->_endpoint = config.Endpoint();

	if(autostart){
		Start();
	}
}

void UServer::Start(void){
	if(this->_isStarted){
		return;
	}

	this->_ctx = new xs::context_t();
	this->_sock = new xs::socket_t(*(this->_ctx), XS_PULL);

	this->_sock->bind(this->_endpoint);

	this->_isStarted = true;
}

void UServer::Receive(void){
	char *buf = new char[UCLA_MAX_MESSAGE_LEN];

	int received_len = this->_sock->recv(buf, UCLA_MAX_MESSAGE_LEN);
	
    if(this->_receive_handler != NULL){
		this->_receive_handler(buf, received_len);
	}

	delete buf;
}

void UServer::Run(void){
	while(true){
		this->Receive();
	}
}

void UServer::SetupReceiveHandler(UCLA_RECEIVE_HANDLER handler){
	this->_receive_handler = handler;
}

bool UServer::IsStarted(void){
	return this->_isStarted;
}

UServer::~UServer(void){
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
