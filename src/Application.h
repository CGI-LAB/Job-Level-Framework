#ifndef JL_APPLICATION_H
#define JL_APPLICATION_H 

#include <boost/asio.hpp>
#include "BrokerAgent.h"
#include "SearchTree.h"
#include "CommandsEngine.h"
#include "SearchTreeCommands.h"
#include "JobLevelCommands.h"

namespace joblevel
{
/*!
	@brief	main class of job-level application, mainly control the input 
			and run boost asynchronized I/O
	@author	chaochin
	@date	2015/7/21
 */
class Application
{
public:
	Application();
	void run();

private:
	void readLine();
	void handleReadInput(std::string sCommandline);

private:
	boost::asio::io_service m_ioService; //<! for asynchronised I/O
	std::auto_ptr<boost::asio::io_service::work> m_pWork; //<! make ioService run in another thread
	BrokerAgent m_brokerAgent; //<! for CGDG and job-level algorithm

	SearchTree m_searchTree; //<! search tree of the application

	CommandsEngine m_commandsEngine; //<! for handling input commands
	SearchTreeCommands m_searchTreeCommands; //<! register handler of search tree commands
	JobLevelCommands m_jobLevelCommands; //<! register handler of job-level commands

	volatile bool m_lock; //<! for prevent console from printing '>' before message
};

}

#endif
