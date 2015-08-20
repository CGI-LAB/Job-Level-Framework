#ifndef UNKNOWNDATA_H
#define UNKNOWNDATA_H

#include "common/CommandData.h"

#include <string>
#include <cassert>

namespace cgdg
{
	namespace common
	{

class UnknownData : public CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	UnknownData(const std::string& xmlString);

	const std::string& getXmlString() const;
private:
	std::string m_xmlString;
};

inline UnknownData::UnknownData(const std::string& xmlString)
: m_xmlString(xmlString)
{
}

inline void UnknownData::insertInto(TiXmlNode& parentNode) const
{
	assert(false);
}

inline int UnknownData::fetch(const TiXmlNode& parentNode)
{
	assert(false);
	return -1;
}

inline const std::string& UnknownData::getXmlString() const
{
	return m_xmlString;
}

	}
}

#endif
