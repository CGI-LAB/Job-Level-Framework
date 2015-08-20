#ifndef JL_BFSDATA_H
#define JL_BFSDATA_H

#include "BaseData.h"

namespace joblevel 
{

typedef unsigned long long uint64;

class BfsData : public BaseData
{
public:
	// forward declaration of BfsData::Accessor, need to declare below
	class Accessor;

	enum WinningStatus 
	{
		BLACK_WIN, WHITE_WIN, UNKNOWN
	};

	enum PlayerColor
	{
		PLAYER_BLACK, PLAYER_WHITE, PLAYER_ROOT
	};

	static const std::string kDataGroup;

public:
	virtual ~BfsData() {};
	virtual std::string serialize() const;
	virtual BaseData::StringPairVector getStringPairs() const;
	virtual std::string getDataGroup() const;

protected:
	BfsData();
	BfsData(const BfsData&);
	BfsData& operator=(const BfsData&);

private:
	std::string getPlayerColorString() const;
	std::string getWinningStatusString() const;

private:
	uint64 ullHashkey;
	PlayerColor playerColor;
	WinningStatus winningStatus;
	bool bFlagged;
	bool bRunningJob;
	bool bStopExpanding;
	int iSequenceOfGeneration;
	int iUnderRunningJobs;
};

typedef BfsData* BfsDataPtr;

class BfsData::Accessor : public BaseData::Accessor
{
public:
	Accessor(NodePtr pNode);
	~Accessor() {};
	uint64 getHashkey() const;
	void setHashkey(uint64 ullHashkey);
	PlayerColor getPlayerColor() const;
	void setPlayerColor(PlayerColor playerColor);
	WinningStatus getWinningStatus() const;
	void setWinningStatus(WinningStatus winningStatus);
	bool isFlagged() const;
	void setFlagged(bool bFlagged);
	bool isRunningJob() const;
	void setRunningJob(bool bRunningJob);
	bool getStopExpanding() const;
	void setStopExpanding(bool bStopExpanding);
	int getSequenceOfGeneration() const;
	void setSequenceOfGeneration(int iSequenceOfGeneration);
	void increaseUnderRunningJobs();
	void decreaseUnderRunningJobs();

private:
	BaseDataPtr createData();

private:
	BfsDataPtr m_pBfsData;
};

} // joblevel

#endif // JL_BFSDATA_H
