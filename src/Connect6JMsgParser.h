#ifndef JL_CONNECT6JMSGPARSER_H
#define JL_CONNECT6JMSGPARSER_H

#include <map>
#include "BaseJMsgParser.h"
#include "UctParserInterface.h"
#include "Connect6Move.h"

namespace joblevel 
{

class Connect6JMsgParser
	: public BaseJMsgParser,
	  public UctParserInterface
{
public:
	Connect6JMsgParser();
	BaseMovePtr getMove(const std::string& sResult) const;
	BfsData::WinningStatus getWinningStatus(const std::string& sResult) const;
	bool getStopExpanding(const std::string& sResult) const;
	double getWinRate(const std::string& sResult) const;

private:
	GoMove::PlayerColor getColor(const std::string& sResult) const;
	void initializeWinRateTable();

private:
	mutable std::map<std::string, double> m_winRateTable;
};

} // joblevel

#endif //JL_CONNECT6JMSGPARSER_H
