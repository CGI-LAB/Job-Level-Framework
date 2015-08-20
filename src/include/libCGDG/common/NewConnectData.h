#ifndef NEWCONNECTDATA_H
#define NEWCONNECTDATA_H

#include "common/CommandData.h"
#include <cassert>

namespace cgdg
{
	namespace common
	{

class NewConnectData : public CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);
};

inline void NewConnectData::insertInto(TiXmlNode& parentNode) const
{
	//do nothing
}

inline int NewConnectData::fetch(const TiXmlNode& parentNode)
{
	assert(false);
	return -1;
}

	}
}

#endif
