#ifndef JSUBMITACKDATA_H
#define JSUBMITACKDATA_H

#include "common/CommandData.h"

#include <string>

namespace cgdg
{
	namespace client
	{

class JSubmitAckData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JSubmitAckData();
	int getUId() const;
	int getJId() const;
	const std::string& getErrorCode() const;
	const std::string& getMessage() const;
private:
	int m_iUId;
	int m_iJId;
	std::string m_errorCode;
	std::string m_message;
};

inline JSubmitAckData::JSubmitAckData()
: m_iUId(-1), m_iJId(-1), m_errorCode(""), m_message("")
{
}

inline int JSubmitAckData::getUId() const
{
	return m_iUId;
}

inline int JSubmitAckData::getJId() const
{
	return m_iJId;
}

inline const std::string& JSubmitAckData::getErrorCode() const
{
	return m_errorCode;
}

inline const std::string& JSubmitAckData::getMessage() const
{
	return m_message;
}

	}
}

#endif
