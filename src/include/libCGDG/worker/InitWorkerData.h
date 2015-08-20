#ifndef INITWORKERDATA_H
#define INITWORKERDATA_H

#include "common/CommandData.h"
#include <string>

namespace cgdg
{
	namespace worker
	{

class InitWorkerData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	int getWId() const;
	const std::string& getBrokerVersion() const;
	const std::string& getWorkerVersion() const;
private:
	int m_iWId;
	std::string m_brokerVersion;
	std::string m_workerVersion;
};

inline int InitWorkerData::getWId() const
{
	return m_iWId;
}

inline const std::string& InitWorkerData::getBrokerVersion() const
{
	return m_brokerVersion;
}

inline const std::string& InitWorkerData::getWorkerVersion() const
{
	return m_workerVersion;
}

	}
}

#endif
