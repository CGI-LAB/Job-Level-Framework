#include "JobLevelConfigure.h"

namespace joblevel
{

JobLevelConfigure JobLevelConfigure::g_configure;

JobLevelConfigure::JobLevelConfigure()
	: sBfsAlgorithmType("BFS"),
	  sUctHandlerType("UCT"),
	  sMiniMaxHandlerType("MINIMAX"),
	  sGoGameType("Go"),
	  sConnect6GameType("Connect6")
{
	// broker
	bAutoConnectToBroker = false;
	sBrokerIp = "";
	iBrokerPort = 0;
	bShowBrokerEvent = false;

	// CGDG
	bAutoLoginCgdg = false;
	sCgdgLoginAccount = "";
	sCgdgLoginPassword = "";	
	sCgdgLogFile = "EditorLog.txt";
	iCgdgLogLevel = 3;

	// job setting
	iJobPriority = 3; 
	nJobCores = 1;
	bJobIsAbortable = true; 
	sJobAverageTime = "";
	sJobMaxTime = "";
	bUseJobLog = false;
	sJobLogFile = "JobSubmit.log";

	// job level BFS
	nMaxRunningJobs = 8;
	iJobLimit = 20000;
	iDelayedExpansionLimit = 15;

	// UCT
	dUcbConstant = 0.3;

	// Go
	sGoAppName = "CGI9";
	sGoAppVersion = "15061001";
	iGoSimulationLimit = 10000;

	// Connect6
	sConnect6AppName = "NCTU6";
	sConnect6AppVersion = "2006";

	// Manager
	// Defalt settings
	sGameType = sConnect6GameType;
	sAlgorithmType = sBfsAlgorithmType;
	sBfsHandlerType = sUctHandlerType;

	// Search tree browser
	iPrintNodeNumber = 10;
	iPrintCommentWidth = 79;
	iPrintCommentLine = 5;
	iPrintDataColumn = 3;
}

void JobLevelConfigure::setConfigureOptions(ConfigureLoader& cl)
{
	// broker
	cl.addOption("AUTO_CONNECT_TO_BROKER", bAutoConnectToBroker,
		ToString(bAutoConnectToBroker),	"Auto connect with broker", "Broker");
	cl.addOption("BROKER_IP", sBrokerIp, sBrokerIp, "Broker IP", "Broker");
	cl.addOption("BROKER_PORT", iBrokerPort, ToString(iBrokerPort), "Broker port", "Broker");
	cl.addOption("BROKER_SHOW_EVENT", bShowBrokerEvent, ToString(bShowBrokerEvent), 
		"Show broker event", "Broker");

	// CGDG
	cl.addOption("CGDG_AUTO_LOGIN", bAutoLoginCgdg,
		ToString(bAutoLoginCgdg), "Auto login CGDG", "CGDG");
	cl.addOption("CGDG_ACCOUNT", sCgdgLoginAccount, sCgdgLoginAccount,
		"CGDG login account", "CGDG");
	cl.addOption("CGDG_PASSWORD", sCgdgLoginPassword, sCgdgLoginPassword,
		"CGDG login password", "CGDG");
	cl.addOption("CGDG_LOG_FILE", sCgdgLogFile, sCgdgLogFile,
		"CGDG log file", "CGDG");
	cl.addOption("CGDG_LOG_LEVEL", iCgdgLogLevel, ToString(iCgdgLogLevel),
		"CGDG log level", "CGDG");

	// job setting
	cl.addOption("JOB_PRIORITY", iJobPriority, ToString(iJobPriority),
		"Job priority", "Job");
	cl.addOption("JOB_CORES", nJobCores, ToString(nJobCores),
		"The number of cores a job uses", "Job");
	cl.addOption("JOB_IS_ABORTABLE", bJobIsAbortable, ToString(bJobIsAbortable),
		"Is job abortable", "Job");
	cl.addOption("JOB_AVERAGE_TIME", sJobAverageTime, sJobAverageTime,
		"Average running time of a job", "Job");
	cl.addOption("JOB_MAX_TIME", sJobMaxTime, sJobMaxTime,
		"Max running time of a job", "Job");
	cl.addOption("USE_JOB_LOG", bUseJobLog, ToString(bUseJobLog),
		"Use job log", "Job");
	cl.addOption("JOB_LOG_FILE", sJobLogFile, sJobLogFile,
		"Job log file", "Job");

	// job level BFS
	cl.addOption("MAX_RUNNING_JOBS", nMaxRunningJobs, ToString(nMaxRunningJobs),
		"Max number of running jobs", "JobLevel");
	cl.addOption("JOB_LIMIT", iJobLimit, ToString(iJobLimit),
		"Total jobs limit", "JobLevel");
	cl.addOption("DELAYED_EXPANDSION_LIMIT", iDelayedExpansionLimit, 
		ToString(iDelayedExpansionLimit), "Delayed expansion limit", "JobLevel");

	// UCT
	cl.addOption("UCB_CONSTANT", dUcbConstant, ToString(dUcbConstant),
		"UCB constant", "JL-UCT");

	// Go
	cl.addOption("GO_APP_NAME", sGoAppName, sGoAppName,
		"Go application name", "Go");
	cl.addOption("GO_APP_VERSION", sGoAppVersion, sGoAppVersion,
		"Go application version", "Go");
	cl.addOption("GO_SIM_LIMIT", iGoSimulationLimit, ToString(iGoSimulationLimit),
		"Go simulation limit", "Go");

	// Connect6
	cl.addOption("CONNECT6_APP_NAME", sConnect6AppName, sConnect6AppName,
		"Connect6 application name", "Connect6");
	cl.addOption("CONNECT6_APP_VERSION", sConnect6AppVersion, sConnect6AppVersion,
		"Connect6 application version", "Connect6");

	// manager
	cl.addOption("MANAGER_GAME_TYPE", sGameType, sGameType,
		"Game type", "Manager");
	cl.addOption("MANAGER_ALGORITHM_TYPE", sAlgorithmType, sAlgorithmType,
		"Algorithm type", "Manager");
	cl.addOption("BFS_HANDLER_TYPE", sBfsHandlerType, sBfsHandlerType,
		"BFS handler type (UCT, MINI-MAX)", "Manager");

	// Search tree browser
	cl.addOption("PRINT_NODE_NUM", iPrintNodeNumber, ToString(iPrintNodeNumber),
		"Print node number", "Search tree browser");
	cl.addOption("PRINT_COMMENT_WIDTH", iPrintCommentWidth, ToString(iPrintCommentWidth),
		"Print comment width", "Search tree browser");
	cl.addOption("PRINT_COMMENT_LINE", iPrintCommentLine, ToString(iPrintCommentLine),
		"Print comment line", "Search tree browser");
	cl.addOption("PRINT_DATA_COLUMN", iPrintDataColumn, ToString(iPrintDataColumn),
		"Print data browser", "Search tree browser");

}

}
