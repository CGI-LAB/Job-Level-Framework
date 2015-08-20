#include "Connect6JMsgParser.h"

namespace joblevel 
{

Connect6JMsgParser::Connect6JMsgParser()
	: BaseJMsgParser(),
	  UctParserInterface(),
	  m_winRateTable()
{
	initializeWinRateTable();
}

BaseMovePtr Connect6JMsgParser::getMove(const std::string& sResult) const
{
	GoMove::PlayerColor color = getColor(sResult);
	int n = sResult.find(";");
	Point point(static_cast<int>(sResult[n + 3] - 'A'),
				static_cast<int>(sResult[n + 4] - 'A'));
	if (n + 7 >= sResult.length() && sResult[n + 7] != sResult[n + 1]) {
		// the first move of connect6 only has one piece
		GoMovePtr pGoMove = GoMove::AllocMove(color, point);
		return pGoMove;
	} else {
		n = sResult.find(";", n + 1);
		Point point2(static_cast<int>(sResult[n + 3] - 'A'),
					static_cast<int>(sResult[n + 4] - 'A'));
		Connect6MovePtr pConnect6Move = Connect6Move::AllocMove(color, point, point2);
		return pConnect6Move;
	}
}

BfsData::WinningStatus Connect6JMsgParser::getWinningStatus(
	const std::string& sResult) const
{
	// CWIN: 0 is UNKNOWN, 1 is player win, 2 is opponent win
	std::string sStatus = getStringFromResult("C", sResult);
	if (sStatus == "B:w")
		return BfsData::BLACK_WIN;
	else if (sStatus == "W:w")
		return BfsData::WHITE_WIN;
	else
		return BfsData::UNKNOWN;
}

bool Connect6JMsgParser::getStopExpanding(const std::string& sResult) const
{
	return false;
}

double Connect6JMsgParser::getWinRate(const std::string& sResult) const
{
	GoMove::PlayerColor color = getColor(sResult);
	std::string sStatus = getStringFromResult("C", sResult);
	if (color == GoMove::PLAYER_BLACK)
		return m_winRateTable[sStatus];
	else
		return 1.0f - m_winRateTable[sStatus];
}

GoMove::PlayerColor Connect6JMsgParser::getColor(const std::string& sResult) const
{
	int n = sResult.find("AB_RESULT");
	n = sResult.find(";", n);
	char cColor = sResult[n + 1];
	GoMove::PlayerColor color = (cColor == 'B')?GoMove::PLAYER_BLACK:GoMove::PLAYER_WHITE;
	return color;
}

void Connect6JMsgParser::initializeWinRateTable()
{
	m_winRateTable["B:w"] = 1.00f;
	m_winRateTable["B:a_w"] = 0.90f;
	m_winRateTable["a-b:unstable"] = 0.50f;
	m_winRateTable["*"] = 0.50f;
	m_winRateTable["a-b:B3"] = 0.80f;
	m_winRateTable["a-b:B2"] = 0.70f;
	m_winRateTable["a-b:B1"] = 0.60f;
	m_winRateTable["a-b:stable"] = 0.50f;
	m_winRateTable["a-b:W1"] = 0.40f;
	m_winRateTable["a-b:W2"] = 0.30f;
	m_winRateTable["a-b:W3"] = 0.20f;
	m_winRateTable["W:a_w"] = 0.10f;
	m_winRateTable["W:w"] = 0.00f;
}

} // joblevel
