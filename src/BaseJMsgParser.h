#ifndef JL_BASEJMSGPARSER_H
#define JL_BASEJMSGPARSER_H

#include <string>
#include <sstream>
#include "BfsData.h"
#include "BaseMove.h"

namespace joblevel
{
/*!
	@brief	Base job message parser, provides functions which game handler needed.
	@author	chaochin
	@date	2015/7/22
 */
class BaseJMsgParser
{
public:
	virtual BaseMovePtr getMove(const std::string& sResult) const = 0;
	virtual BfsData::WinningStatus getWinningStatus(const std::string& sResult) const = 0;
	virtual bool getStopExpanding(const std::string& sResult) const = 0;

protected:
	std::string getStringFromResult(const std::string& sTag, 
		const std::string& sResult) const;
	template<typename T>
	T getDataFromResult(const std::string& sTag, const std::string& sResult) const;
};

template<typename T>
inline T BaseJMsgParser::getDataFromResult(const std::string& sTag, const std::string& sResult) const
{
	std::istringstream iss(getStringFromResult(sTag, sResult));
	T data;
	iss >> data;
	return data;
}

}

#endif
