#ifndef INITCONNECTDATA_H
#define INITCONNECTDATA_H

#include "common/CommandData.h"
#include <string>

namespace cgdg
{
	namespace common
	{

class InitConnectData : public CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	const std::string& getHost() const;
	unsigned short getPort() const;
private:
	std::string m_host;
	unsigned short m_port;
};

inline const std::string& InitConnectData::getHost() const
{
	return m_host;
}

inline unsigned short InitConnectData::getPort() const
{
	return m_port;
}

	}
}

#endif
