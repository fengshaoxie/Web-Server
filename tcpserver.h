#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "eventloop.h"
#include "channel.h"
#include "base/log.h"

class TcpServer
{
public:
	typedef EventLoop::ChannelPtr ChannelPtr;
	typedef std::function<void (std::shared_ptr<Channel>)> CallbackType;
	
	TcpServer(const char * serverIp, uint16_t port);
	~TcpServer();
	
	void SetReadCallback(CallbackType readCallback);
	void SetWriteCallback(CallbackType writeCallback);
	void SetErrorCallback(CallbackType errorCallback);
	void Loop();
	
private:
	void NewConnectReadHandler(EventLoop & eventLoop, std::shared_ptr<Channel> ptChannel);
	void ReadFromFdToBuffer(EventLoop & eventLoop, std::shared_ptr<Channel> ptChannel);
	void WriteFromBufferToFd(EventLoop & eventLoop, std::shared_ptr<Channel> ptChannel);
	void ErrorCallBack(EventLoop & eventLoop, std::shared_ptr<Channel> ptChannel);
	
private:
	int m_listenFd;
	ChannelPtr m_ptListenChannel;
	EventLoop m_eventLoop;
	CallbackType m_readCallback;
	CallbackType m_writeCallback;
	CallbackType m_errorCallback;
};

#endif