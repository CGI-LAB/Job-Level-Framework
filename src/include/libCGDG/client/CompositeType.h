#ifndef COMPOSITETYPE_H
#define COMPOSITETYPE_H

#include <string>
#include <vector>

namespace cgdg
{
	namespace client
	{

struct Filter
{
	std::string m_ip;
	bool m_vm;
	std::string m_os;
	std::string m_hostName;
	std::string m_organization;
	int m_nCore;
	int m_nAvaliableCore;
	std::string m_cpuSpeed;
	std::string m_cpuUsage;
	std::string m_ramSize;
	std::string m_ramUsage;
	std::string m_inops;
	std::string m_flops;
};

struct Job
{
	int m_iUId;
	std::string m_userIp;
	std::string m_userName;
	std::string m_time;
	int m_iPriority;
	bool m_bisLocked;
	std::string m_applicationName;
};

struct WorkerStatus
{
	int m_iWId;
	std::string m_internalIp;
	std::string m_externalIp;
	std::string m_brokerIp;
	std::string m_brokerPort;
	bool m_bVm;
	std::string m_os;
	std::string m_hostName;
	std::string m_organization;
	int m_nCoreNum;
	int m_nCoreAvailable;
	int m_nCoreUsed;
	std::string m_cpuSpeed;
	std::string m_cpuUsage;
	std::string m_ramSize;
	std::string m_ramUsage;
	std::string m_inops;
	std::string m_flops;
	std::vector<Job> m_jobList;
	std::string m_description;
};

	}
}

#endif
