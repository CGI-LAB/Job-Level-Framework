#ifndef EXITDATA_H
#define EXITDATA_H

#include "common/CommandData.h"

namespace cgdg
{
	namespace common
	{

class ExitData : public CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);
};

inline void ExitData::insertInto(TiXmlNode& parentNode) const
{
	//do nothing
}

inline int ExitData::fetch(const TiXmlNode& parentNode)
{
	return 0;
}

	}
}

#endif
