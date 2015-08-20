#ifndef JL_GOJMSGPARSER_H
#define JL_GOJMSGPARSER_H

#include "BaseJMsgParser.h"
#include "UctParserInterface.h"

namespace joblevel
{

class GoJMsgParser
	: public BaseJMsgParser,
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
