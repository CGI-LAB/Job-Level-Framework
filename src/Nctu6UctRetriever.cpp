#include "Nctu6UctRetriever.h"
#include "Nctu6Parser.h"

namespace joblevel
{

Nctu6UctRetriever::Nctu6UctRetriever(Nctu6Parser* pNctu6Parser)
	: m_pNctu6Parser(pNctu6Parser)
{
	initializeWinRateTable();
}

BfsData::WinningStatus Nctu6UctRetriever::getWinningStatus() const
{
	// CWIN: 0 is UNKNOWN, 1 is player win, 2 is opponent win
	std::string sStatus = m_pNctu6Parser->getGameStatus();
	if (sStatus == "B:w")
		return BfsData::BLACK_WIN;
	else if (sStatus == "W:w")
		return BfsData::WHITE_WIN;
	else
		return BfsData::UNKNOWN;
}

bool Nctu6UctRetriever::getStopExpanding() const
{
	return false;
}

double Nctu6UctRetriever::getWinRate() const
{
	GoMove::PlayerColor color = m_pNctu6Parser->getColor();
	std::string sStatus = m_pNctu6Parser->getGameStatus();
	if (color == GoMove::PLAYER_BLACK)
		return m_winRateTable[sStatus];
	else
		return 1.0f - m_winRateTable[sStatus];
}

void Nctu6UctRetriever::initializeWinRateTable()
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

}