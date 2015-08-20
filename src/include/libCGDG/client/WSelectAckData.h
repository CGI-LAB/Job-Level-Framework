#ifndef WSELECTACKDATA_H
#define WSELECTACKDATA_H

#include "common/CommandData.h"

#include <string>
#include <vector>

namespace cgdg
{
	namespace client
	{

class WSelectAckData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	WSelectAckData();
	int getUId() const;
	const std::string& getErrorCode() const;
	const std::string& getMessage() const;
	const std::vector<int>& getSelectedWorkerIds() const;
private:
	int m_iUId;
	std::string m_errorCode;
	std::string m_message;
	std::vector<int> m_workerList;
};

inline WSelectAckData::WSelectAckData()
: m_iUId(-1), m_errorCode(""), m_message("")
{
}

inline int WSelectAckData::getUId() const
{
	return m_iUId;
}

inline const std::string& WSelectAckData::getErrorCode() const
{
	return m_errorCode;
}

inline const std::string& WSelectAckData::getMessage() const
{
	return m_message;
}

inline const std::vector<int>& WSelectAckData::getSelectedWorkerIds() const
{
	return m_workerList;
}

	}
}

#endif
