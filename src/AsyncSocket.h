#ifndef JL_ASYNCSOCKET_H
#define JL_ASYNCSOCKET_H

#include <client/BrokerAgentExtension.h>
#include <common/SocketInterface.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace joblevel
{
/*!
	@brief	implementation of SocketInterface of CGDG, based on boost
			asynchronized socket I/O 
	@author	chaochin
	@date	2015/7/13
 */
class AsyncSocket : public cgdg::common::SocketInterface
{
public:
	AsyncSocket(cgdg::client::BrokerAgentExtension& aliasBrokerAgent,
		boost::asio::io_service& ioService);
	virtual ~AsyncSocket();
	//////////////////////////////////////////
	// Override function of SocketInterface //
	//////////////////////////////////////////
	int connect(const std::string& host, unsigned short port);
	int read(void* pBuffer, unsigned nLength);
	int write(const void* pBuffer, unsigned nLength);
	void close();
	////////////////////////////////////////////
	// Asynchronized socket handler for boost //
	////////////////////////////////////////////
	void handleConnect(const boost::system::error_code& error);
	void handleConnectTimeOut(const boost::system::error_code& error);
	void asyncRead();
	void handleRead(const boost::system::error_code& error, size_t length);
	void handleWrite(const boost::system::error_code& error);

private:
	cgdg::client::BrokerAgentExtension& m_aliasBrokerAgent;
	boost::asio::io_service& m_ioService;
	boost::asio::ip::tcp::socket m_socket;
	static const unsigned BUFFER_SIZE = 65536; 
	boost::asio::streambuf m_buffer;
	size_t m_bufferLength;
	boost::asio::deadline_timer m_timer;
};

}

#endif