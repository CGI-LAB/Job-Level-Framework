#ifndef JL_CGIPARSER_H
#define JL_CGIPARSER_H

#include "GameParser.h"
#include "UctParserInterface.h"

namespace joblevel
{

class CgiParser
	: public GameParser,
	  public UctParserInterface
{
public:
	BaseMovePtr getMove(const std::string& sResult) const;
	BfsData::WinningStatus getWinningStatus(const std::string& sResult) const;
	bool getStopExpanding(const std::string& sResult) const;
	double getWinRate(const std::string& sResult) const;
};

}

#endif
