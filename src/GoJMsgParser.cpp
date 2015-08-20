#include "GoJMsgParser.h"
#include "GoMove.h"

namespace joblevel
{

BaseMovePtr GoJMsgParser::getMove(const std::string& sResult) const
{
	GoMove::PlayerColor color = (sResult[0] == 'B')?GoMove::PLAYER_BLACK:GoMove::PLAYER_WHITE;
	Point point(static_cast<int>(sResult[2] - 'A'),
				static_cast<int>(sResult[3] - 'A'));
	GoMovePtr pGoMove = GoMove::AllocMove(color, point);
	return pGoMove;
}

BfsData::WinningStatus GoJMsgParser::getWinningStatus(
	const std::string& sResult) const
{
	// CWIN: 0 is UNKNOWN, 1 is player win, 2 is opponent win
	int iCWinValue = getDataFromResult<int>("CWIN", sResult);
	if (iCWinValue == 0)
		return BfsData::UNKNOWN;
	else if ((sResult[0] == 'B' && iCWinValue == 1) || (sResult[0] == 'W' && iCWinValue == 2))
		return BfsData::BLACK_WIN;
	else
		return BfsData::WHITE_WIN;
}

bool GoJMsgParser::getStopExpanding(const std::string& sResult) const
{
	return static_cast<bool>(getDataFromResult<int>("LAST", sResult));
}

double GoJMsgParser::getWinRate(const std::string& sResult) const
{
	return getDataFromResult<double>("WR", sResult);
}

}
