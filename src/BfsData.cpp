#include "BfsData.h"
#include <sstream>
#include "strops.h"

namespace joblevel 
{

const std::string BfsData::kDataGroup = "BFS";

BfsData::BfsData()
{
	ullHashkey = 0ull;
	playerColor = PLAYER_ROOT;
	winningStatus = UNKNOWN;
	iSequenceOfGeneration = 0;
	iUnderRunningJobs = 0;
	bFlagged = false;
	bRunningJob = false;
	bStopExpanding = false;
}

std::string BfsData::getDataGroup() const
{
	return kDataGroup;
}

std::string BfsData::serialize() const
{
	std::ostringstream oss;
	oss << kDataGroup
		<< "[" << ullHashkey << "]"
		<< "[" << playerColor << "]"
		<< "[" << winningStatus << "]"
		<< "[" << bFlagged << "]"
		<< "[" << bRunningJob << "]"
		<< "[" << bStopExpanding << "]"
		<< "[" << iSequenceOfGeneration << "]"
		<< "[" << iUnderRunningJobs << "]";
	return oss.str();
}

BaseData::StringPairVector BfsData::getStringPairs() const
{
	BaseData::StringPairVector vStringPairs;
	vStringPairs.push_back(std::make_pair("Hashkey", ToString(ullHashkey)));
	vStringPairs.push_back(std::make_pair("Color", getPlayerColorString()));
	vStringPairs.push_back(std::make_pair("Win", getWinningStatusString()));
	vStringPairs.push_back(std::make_pair("Flagged", ToString(bFlagged)));
	vStringPairs.push_back(std::make_pair("Running", ToString(bRunningJob)));
	vStringPairs.push_back(std::make_pair("Stop Expanding", ToString(bStopExpanding)));
	vStringPairs.push_back(std::make_pair("Generate Seq.#", ToString(iSequenceOfGeneration)));
	vStringPairs.push_back(std::make_pair("Jobs#", ToString(iUnderRunningJobs)));
	return vStringPairs;
}

std::string BfsData::getPlayerColorString() const
{
	std::string sPlayerColor;
	if (playerColor == PLAYER_BLACK)
		sPlayerColor = "Black";
	else if (playerColor == PLAYER_WHITE)
		sPlayerColor = "White";
	else if (playerColor == PLAYER_ROOT)
		sPlayerColor = "Root";
	else
		sPlayerColor = "Unknown";
	return sPlayerColor;
}

std::string BfsData::getWinningStatusString() const
{
	std::string sWinningStatus;
	if (winningStatus == BLACK_WIN)
		sWinningStatus = "Black Win";
	else if (winningStatus == WHITE_WIN)
		sWinningStatus = "White Win";
	else
		sWinningStatus = "Unknown";
	return sWinningStatus;
}

BfsData::Accessor::Accessor(NodePtr pNode)
	: BaseData::Accessor(pNode, kDataGroup),
	  m_pBfsData(nullptr)
{
	checkData();
	m_pBfsData = dynamic_cast<BfsData*>(getBaseData());
}

BaseDataPtr BfsData::Accessor::createData()
{
	BfsDataPtr pBfsData = new BfsData;
	return pBfsData;
}

uint64 BfsData::Accessor::getHashkey() const
{
	return m_pBfsData->ullHashkey;
}

void BfsData::Accessor::setHashkey(uint64 ullHashkey)
{
	m_pBfsData->ullHashkey = ullHashkey;
}

BfsData::PlayerColor BfsData::Accessor::getPlayerColor() const
{
	return m_pBfsData->playerColor;
}

void BfsData::Accessor::setPlayerColor(BfsData::PlayerColor playerColor)
{
	m_pBfsData->playerColor = playerColor;
}

BfsData::WinningStatus BfsData::Accessor::getWinningStatus() const
{
	return m_pBfsData->winningStatus;
}

void BfsData::Accessor::setWinningStatus(BfsData::WinningStatus winningStatus)
{
	m_pBfsData->winningStatus = winningStatus;
}

bool BfsData::Accessor::isFlagged() const
{
	return m_pBfsData->bFlagged;
}

void BfsData::Accessor::setFlagged(bool bFlagged)
{
	m_pBfsData->bFlagged = bFlagged;
}

bool BfsData::Accessor::isRunningJob() const
{
	return m_pBfsData->bRunningJob;
}

void BfsData::Accessor::setRunningJob(bool bRunningJob)
{
	m_pBfsData->bRunningJob = bRunningJob;
}

bool BfsData::Accessor::getStopExpanding() const
{
	return m_pBfsData->bStopExpanding;
}

void BfsData::Accessor::setStopExpanding(bool bStopExpanding)
{
	m_pBfsData->bStopExpanding = bStopExpanding;
}

int BfsData::Accessor::getSequenceOfGeneration() const
{
	return m_pBfsData->iSequenceOfGeneration;
}

void BfsData::Accessor::setSequenceOfGeneration(int iSequenceOfGeneration)
{
	m_pBfsData->iSequenceOfGeneration = iSequenceOfGeneration;
}

void BfsData::Accessor::increaseUnderRunningJobs()
{
	m_pBfsData->iUnderRunningJobs++;
}

void BfsData::Accessor::decreaseUnderRunningJobs()
{
	m_pBfsData->iUnderRunningJobs--;
}

} // joblevel
