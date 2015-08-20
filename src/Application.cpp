#include "Application.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <common/Logger.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include "SReadLine.h"
#include "JobLevelConfigure.h"

namespace joblevel
{

Application::Application()
	: m_ioService(),
	  m_pWork(new boost::asio::io_service::work(m_ioService)),
	  m_brokerAgent(std::cout, m_ioService),
	  m_searchTree(),
	  m_commandsEngine(std::cout),
	  m_searchTreeCommands(std::cout, m_commandsEngine, m_searchTree),
	  m_jobLevelCommands(std::cout, m_commandsEngine, m_brokerAgent, m_searchTree),
	  m_lock(false)
{
}

void Application::run()
{
	if (JobLevelConfigure::g_configure.bAutoConnectToBroker) {
		m_brokerAgent.connectToBroker(JobLevelConfigure::g_configure.sBrokerIp,
			JobLevelConfigure::g_configure.iBrokerPort);
	}

	boost::thread t(boost::bind(&boost::asio::io_service::run, &m_ioService));

	readLine();

	t.join();
	std::cout << "Exit application" << std::endl;
}

void Application::readLine()
{
	swift::SReadline reader("./.jlapphist", 32);

	reader.RegisterCompletions(m_commandsEngine.getCompleters());

	std::string sCommandline;
	bool isEof = false;
	for(;;) {
		while (m_lock == true);
		sCommandline = reader.GetLine("> ", isEof);
		if (isEof || sCommandline == "exit" || sCommandline == "quit") {
			m_pWork.reset();
			m_ioService.post(boost::bind(&Application::handleReadInput, this, "exit"));
			return;
		} else if (sCommandline == "browser") {
			m_searchTreeCommands.cmdStartBrowserMode();
			continue;
		}
		m_lock = true;
		m_ioService.post(boost::bind(&Application::handleReadInput, this, sCommandline));
	}
}

void Application::handleReadInput(std::string sCommandline)
{
	m_commandsEngine.runCommand(sCommandline);

	if (m_commandsEngine.hasQuit()) {
		m_ioService.stop();
		return;
	}

	m_lock = false;
}

}
