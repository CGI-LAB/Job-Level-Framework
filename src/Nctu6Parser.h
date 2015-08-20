#ifndef JL_NCTU6PARSER_H
#define JL_NCTU6PARSER_H

#include <map>
#include "GameParser.h"
#include "UctParserInterface.h"
#include "Connect6Move.h"

namespace joblevel 
{

class Nctu6Parser
	: public GameParser,
	  public UctParserInterface
{
public:
	Nctu6Parser();
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
