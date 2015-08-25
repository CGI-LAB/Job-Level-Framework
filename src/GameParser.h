#ifndef JL_GAMEPARSER_H
#define JL_GAMEPARSER_H

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
class GameParser
{
public:
	GameParser(const std::string& sResult);
	virtual ~GameParser() {}
	virtual BaseMovePtr getMove() const = 0;

protected:
	std::string getStringFromResult(const std::string& sTag) const;
	template<typename T>
	T getDataFromResult(const std::string& sTag) const;

protected:
	std::string m_sResult;
};

template<typename T>
inline T GameParser::getDataFromResult(const std::string& sTag) const
{
	std::istringstream iss(getStringFromResult(sTag));
	T data;
	iss >> data;
	return data;
}

}

#endif
