#ifndef HEARTBEATDATA_H
#define HEARTBEATDATA_H

#include "common/CommandData.h"
#include <cassert>

namespace cgdg
{
	namespace common
	{

class HeartBeatData : public CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);
};

inline void HeartBeatData::insertInto(TiXmlNode &parentNode) const
{
	assert(false);
}

inline int HeartBeatData::fetch(const TiXmlNode &parentNode)
{
	return 0;
}

	}
}

#endif
