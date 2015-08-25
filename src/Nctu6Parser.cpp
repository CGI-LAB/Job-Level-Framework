#include "Nctu6Parser.h"

namespace joblevel 
{

Nctu6Parser::Nctu6Parser(const std::string& sResult)
	: GameParser(sResult)
{
}

BaseMovePtr Nctu6Parser::getMove() const
{
	GoMove::PlayerColor color = getColor();
	int n = m_sResult.find(";");
	Point point(static_cast<int>(m_sResult[n + 3] - 'A'),
				static_cast<int>(m_sResult[n + 4] - 'A'));
	if (n + 7 >= m_sResult.length() && m_sResult[n + 7] != m_sResult[n + 1]) {
		// the first move of connect6 only has one piece
		GoMovePtr pGoMove = GoMove::AllocMove(color, point);
		return pGoMove;
	} else {
		n = m_sResult.find(";", n + 1);
		Point point2(static_cast<int>(m_sResult[n + 3] - 'A'),
					static_cast<int>(m_sResult[n + 4] - 'A'));
		Connect6MovePtr pConnect6Move = Connect6Move::AllocMove(color, point, point2);
		return pConnect6Move;
	}
}

std::string Nctu6Parser::getGameStatus() const
{
	return getStringFromResult("C");
}

GoMove::PlayerColor Nctu6Parser::getColor() const
{
	int n = m_sResult.find("AB_RESULT");
	n = m_sResult.find(";", n);
	char cColor = m_sResult[n + 1];
	GoMove::PlayerColor color = (cColor == 'B')?GoMove::PLAYER_BLACK:GoMove::PLAYER_WHITE;
	return color;
}

} // joblevel
