#include "CgiParser.h"
#include "GoMove.h"

namespace joblevel
{

CgiParser::CgiParser(const std::string& sResult) : GameParser(sResult) 
{
}

BaseMovePtr CgiParser::getMove() const
{
	GoMove::PlayerColor color = (m_sResult[0] == 'B')?GoMove::PLAYER_BLACK:GoMove::PLAYER_WHITE;
	Point point(static_cast<int>(m_sResult[2] - 'A'),
				static_cast<int>(m_sResult[3] - 'A'));
	GoMovePtr pGoMove = GoMove::AllocMove(color, point);
	return pGoMove;
}

std::string CgiParser::getColor() const
{
	return m_sResult.substr(0, 1);
}

int CgiParser::getCWin() const
{
	// CWIN: 0 is UNKNOWN, 1 is player win, 2 is opponent win
	return getDataFromResult<int>("CWIN");
}

bool CgiParser::getLast() const
{
	return static_cast<bool>(getDataFromResult<int>("LAST"));
}

double CgiParser::getWinRate() const
{
	return getDataFromResult<double>("WR");
}

}
