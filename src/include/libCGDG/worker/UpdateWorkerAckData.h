#ifndef UPDATEWORKERACKDATA_H
#define UPDATEWORKERACKDATA_H

#include "common/CommandData.h"
#include <string>

namespace cgdg
{
	namespace worker
	{

class UpdateWorkerAckData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	UpdateWorkerAckData(const std::string& errorCode, const std::string& message);
private:
	std::string m_errorCode;
	std::string m_message;
};


inline UpdateWorkerAckData::UpdateWorkerAckData(const std::string& errorCode, const std::string& message)
: m_errorCode(errorCode), m_message(message)
{
}

	}
}

#endif
