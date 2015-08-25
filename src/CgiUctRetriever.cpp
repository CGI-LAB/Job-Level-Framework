#include "CgiUctRetriever.h"
#include "CgiParser.h"

namespace joblevel
{

CgiUctRetriever::CgiUctRetriever(CgiParser* pCgiParser)
	: m_pCgiParser(pCgiParser)
{
}

BfsData::WinningStatus CgiUctRetriever::getWinningStatus() const
{
	// CWIN: 0 is UNKNOWN, 1 is player win, 2 is opponent win
	int iCWinValue = m_pCgiParser->getCWin();
	if (iCWinValue == 0)
		return BfsData::UNKNOWN;
	else if ((m_pCgiParser->getColor() == "B" && iCWinValue == 1) 
		|| (m_pCgiParser->getColor() == "W" && iCWinValue == 2))
		return BfsData::BLACK_WIN;
	else
		return BfsData::WHITE_WIN;
}

bool CgiUctRetriever::getStopExpanding() const
{
	return m_pCgiParser->getLast();
}

double CgiUctRetriever::getWinRate() const
{
	return m_pCgiParser->getWinRate();
}

}