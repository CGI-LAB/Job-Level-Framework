#include "AsyncSocket.h"
#include <cstring>
#include <sstream>
#include <iostream>

namespace joblevel
{

using boost::asio::ip::tcp;

AsyncSocket::AsyncSocket(cgdg::client::BrokerAgentExtension& aliasBrokerAgent, 
	boost::asio::io_service& ioService)
	: m_aliasBrokerAgent(aliasBrokerAgent),
	  m_ioService(ioService),
	  m_socket(ioService),
	  m_bufferLength(0),
	  m_timer(ioService, boost::posix_time::seconds(3))
{
}

AsyncSocket::~AsyncSocket()
{
	m_socket.close();
}

int AsyncSocket::connect(const std::string& host, unsigned short port)
{
	tcp::resolver resolver(m_ioService);
	std::ostringstream oss;
	oss << port;
	tcp::resolver::query query(host, oss.str());
	tcp::resolver::iterator iterator = resolver.resolve(query);

	boost::asio::async_connect(m_socket, iterator,
		boost::bind(&AsyncSocket::handleConnect, this,
			boost::asio::placeholders::error));

	m_timer.async_wait(boost::bind(&AsyncSocket::handleConnectTimeOut, this,
		boost::asio::placeholders::error));
	return 0;
}

int AsyncSocket::read(void* pBuffer, unsigned nLength)
{
	m_buffer.sgetn(static_cast<char*>(pBuffer), m_bufferLength);
	return m_bufferLength;
}

int AsyncSocket::write(const void* pBuffer, unsigned nLength)
{
	boost::asio::async_write(m_socket,
		boost::asio::buffer(pBuffer, nLength),
		boost::bind(&AsyncSocket::handleWrite, this,
			boost::asio::placeholders::error));
	return nLength;
}

void AsyncSocket::close()
{
	m_socket.close();
}

void AsyncSocket::handleConnect(const boost::system::error_code& error)
{
	if (error) {
		m_aliasBrokerAgent.processConnectEvent(cgdg::common::SocketInterface::CONNECTIONRESULT_FAIL);
	} else {
		m_timer.cancel();
		m_aliasBrokerAgent.processConnectEvent(cgdg::common::SocketInterface::CONNECTIONRESULT_SUCESS);
		
		asyncRead();
	}
}

void AsyncSocket::handleConnectTimeOut(const boost::system::error_code& error)
{
	if (!error) {
		std::cerr << "Error: Socket connect Time out" << std::endl << "> " << std::flush;
		m_socket.close();
	}
}

void AsyncSocket::asyncRead()
{
	boost::asio::async_read_until(m_socket, 
		m_buffer, '\n',
		boost::bind(&AsyncSocket::handleRead, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void AsyncSocket::handleRead(const boost::system::error_code& error, size_t length)
{
	if (error) {
		std::cerr << "Error: Socket read data failed: " << error.message() << std::endl << "> " << std::flush;
		// for BrokerAgent read buffer size 0;
		m_bufferLength = 0;
		m_aliasBrokerAgent.processReadEvent();
	} else {
		m_bufferLength = length;
		m_aliasBrokerAgent.processReadEvent();

		asyncRead();
	}
}

void AsyncSocket::handleWrite(const boost::system::error_code& error)
{
	if (error) {
		std::cerr << "Error: Socket write data failed: " << error.message() << std::endl << "> " << std::flush;
	} else {
		m_aliasBrokerAgent.processWriteEvent();
	}
}

}
