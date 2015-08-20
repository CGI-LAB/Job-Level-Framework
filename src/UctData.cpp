#include "UctData.h"
#include <sstream>
#include "strops.h"

namespace joblevel 
{

const std::string UctData::kDataGroup = "UCT";

UctData::UctData()
{
	iMoveCount = 0;
	iPreUpdateMoveCount = 0;
	dWinRate = 0.0f;
	dUcbScore = 0.0f;
}

std::string UctData::getDataGroup() const
{
	return kDataGroup;
}

std::string UctData::serialize() const
{
	std::ostringstream oss;
	oss << kDataGroup
		<< "[" << iMoveCount << "]"
		<< "[" << iPreUpdateMoveCount << "]"
		<< "[" << dWinRate << "]"
		<< "[" << dUcbScore << "]";
	return oss.str();
}

BaseData::StringPairVector UctData::getStringPairs() const
{
	BaseData::StringPairVector vStringPairs;
	vStringPairs.push_back(std::make_pair("Visit#", ToString(iMoveCount)));
	vStringPairs.push_back(std::make_pair("Pre-Update#", ToString(iPreUpdateMoveCount)));
	vStringPairs.push_back(std::make_pair("Win Rate", ToString(dWinRate)));
	vStringPairs.push_back(std::make_pair("UCB", ToString(dUcbScore)));
	return vStringPairs;
}

UctData::Accessor::Accessor(NodePtr pNode)
	: BaseData::Accessor(pNode, kDataGroup),
	  m_pUctData(nullptr)
{
	checkData();
	m_pUctData = dynamic_cast<UctData*>(getBaseData());
}

BaseDataPtr UctData::Accessor::createData()
{
	UctDataPtr pUctData = new UctData;
	return pUctData;
}
int UctData::Accessor::getMoveCount() const
{
	return m_pUctData->iMoveCount;
}

void UctData::Accessor::setMoveCount(int iMoveCount)
{
	m_pUctData->iMoveCount = iMoveCount;
}

void UctData::Accessor::increaseMoveCount()
{
	m_pUctData->iMoveCount++;
}

void UctData::Accessor::decreaseMoveCount()
{
	m_pUctData->iMoveCount--;
}

int UctData::Accessor::getPreUpdateMoveCount() const
{
	return m_pUctData->iPreUpdateMoveCount;
}

void UctData::Accessor::increasePreUpdateMoveCount()
{
	m_pUctData->iPreUpdateMoveCount++;
}

void UctData::Accessor::decreasePreUpdateMoveCount()
{
	m_pUctData->iPreUpdateMoveCount--;
}

double UctData::Accessor::getWinRate() const
{
	return m_pUctData->dWinRate;
}

void UctData::Accessor::setWinRate(double dWinRate)
{
	m_pUctData->dWinRate = dWinRate;
}

double UctData::Accessor::getUcbScore() const
{
	return m_pUctData->dUcbScore;
}

void UctData::Accessor::setUcbScore(double dUcbScore)
{
	m_pUctData->dUcbScore = dUcbScore;
}

} // joblevel
