#ifndef JL_JOBLEVELCONFIGURE_H
#define JL_JOBLEVELCONFIGURE_H

#include "BaseConfigure.h"
#include <string>

namespace joblevel
{

class JobLevelConfigure : public BaseConfigure
{
public:
	static JobLevelConfigure g_configure;

private:
	JobLevelConfigure();
	JobLevelConfigure(const JobLevelConfigure&);
	JobLevelConfigure& operator=(const JobLevelConfigure&);

public:
	virtual void setConfigureOptions(ConfigureLoader& cl);

public:
	// broker
	bool bAutoConnectToBroker;
	std::string sBrokerIp;
	int iBrokerPort;
	bool bShowBrokerEvent;

	// CGDG
	bool bAutoLoginCgdg;
	std::string sCgdgLoginAccount;
	std::string sCgdgLoginPassword;
	std::string sCgdgLogFile;
	int iCgdgLogLevel;

	// job setting
	int iJobPriority;
	int nJobCores; 
	bool bJobIsAbortable;
	std::string sJobAverageTime;
	std::string sJobMaxTime;
	bool bUseJobLog;
	std::string sJobLogFile;

	// job level BFS
	int nMaxRunningJobs;
	int iJobLimit;
	int iDelayedExpansionLimit;
	const std::string sBfsAlgorithmType;

	// UCT
	double dUcbConstant;
	const std::string sUctHandlerType;

	// Mini-Max
	const std::string sMiniMaxHandlerType;

	// Go
	const std::string sGoGameType;
	std::string sGoAppName;
	std::string sGoAppVersion;
	int iGoSimulationLimit;

	// Connect6
	const std::string sConnect6GameType;
	std::string sConnect6AppName;
	std::string sConnect6AppVersion;

	// manager
	std::string sGameType;
	std::string sAlgorithmType;
	std::string sBfsHandlerType;

	// Search tree browser
	int iPrintNodeNumber;
	int iPrintCommentWidth;
	int iPrintCommentLine;
	int iPrintDataColumn;
	
};

}

#endif
