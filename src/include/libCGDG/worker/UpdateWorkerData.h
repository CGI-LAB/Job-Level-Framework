#ifndef UPDATEWORKERDATA_H
#define UPDATEWORKERDATA_H

#include "common/CommandData.h"
#include <string>

namespace cgdg
{
	namespace worker
	{

class UpdateWorkerData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	UpdateWorkerData();

	const std::string& getWorkerVersion() const;
	const std::string& getBrokerHost() const;
	unsigned short getBrokerPort() const;
	const std::string& getOrganization() const;
	int getCoreNumber() const;
	const std::string& getFileServer() const;
	const std::string& getBrokerList() const;
private:
	std::string m_workerVersion;
	std::string m_brokerHost;
	unsigned short m_brokerPort;
	std::string m_organization;
	int m_nCore;
	std::string m_fileServer;
	std::string m_brokerList;
};

inline UpdateWorkerData::UpdateWorkerData()
: m_workerVersion(""), m_brokerHost(""), m_brokerPort(0), m_organization(""), m_nCore(0), m_fileServer(""), m_brokerList("")
{
}

inline const std::string& UpdateWorkerData::getWorkerVersion() const
{
	return m_workerVersion;
}

inline const std::string& UpdateWorkerData::getBrokerHost() const
{
	return m_brokerHost;
}

inline unsigned short UpdateWorkerData::getBrokerPort() const
{
	return m_brokerPort;
}

inline const std::string& UpdateWorkerData::getOrganization() const
{
	return m_organization;
}

inline int UpdateWorkerData::getCoreNumber() const
{
	return m_nCore;
}

inline const std::string& UpdateWorkerData::getFileServer() const
{
	return m_fileServer;
}

inline const std::string& UpdateWorkerData::getBrokerList() const
{
	return m_brokerList;
}

	}
}

#endif
