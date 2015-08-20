#ifndef NEWWORKERDATA_H
#define NEWWORKERDATA_H

#include "common/CommandData.h"
#include <string>

namespace cgdg
{
	namespace worker
	{

class NewWorkerData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	NewWorkerData(
		int iWId,
		const std::string& workerVersion,
		int nCore,
		const std::string& internalIp,
		const std::string& hostName,
		const std::string& os,
		const std::string& organization,
		const std::string& description,
		const std::string& fileServer,
		const std::string& brokerList,
		const std::string& inops,
		const std::string& flops);
private:
	int m_iWId;
	std::string m_workerVersion;
	int m_nCore;
	std::string m_internalIp;
	std::string m_hostName;
	std::string m_os;
	std::string m_organization;
	std::string m_description;
	std::string m_fileServer;
	std::string m_brokerList;
	std::string m_inops;
	std::string m_flops;
};

inline NewWorkerData::NewWorkerData(
	int iWId,
	const std::string& workerVersion,
	int nCore,
	const std::string& internalIp,
	const std::string& hostName,
	const std::string& os,
	const std::string& organization,
	const std::string& description,
	const std::string& fileServer,
	const std::string& brokerList,
	const std::string& inops,
	const std::string& flops)
: m_iWId(iWId), m_workerVersion(workerVersion), m_nCore(nCore), m_internalIp(internalIp), m_hostName(hostName), m_os(os), m_organization(organization), m_description(description), m_fileServer(fileServer), m_brokerList(brokerList), m_inops(inops), m_flops(flops)
{
}

	}
}

#endif
