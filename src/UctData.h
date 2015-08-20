#ifndef JL_UCTDATA_H
#define JL_UCTDATA_H

#include "BaseData.h"

namespace joblevel 
{

class UctData : public BaseData
{
public:
	// forword declaration of UctData::Accessor, need to declare below
	class Accessor;

	static const std::string kDataGroup;

public:
	virtual ~UctData() {};
	virtual std::string serialize() const;
	virtual BaseData::StringPairVector getStringPairs() const;
	virtual std::string getDataGroup() const;

protected:
	UctData();
	UctData(const UctData&);
	UctData& operator=(const UctData&);
	
private:
	int iMoveCount;
	int iPreUpdateMoveCount;
	double dWinRate; //<! this is for the aspect of move color
	double dUcbScore;
};

typedef UctData* UctDataPtr;

class UctData::Accessor : public BaseData::Accessor
{
public:
	Accessor(NodePtr pNode);
	~Accessor() {};
	int getMoveCount() const;
	void setMoveCount(int iMoveCount);
	void increaseMoveCount();
	void decreaseMoveCount();
	int getPreUpdateMoveCount() const;
	void increasePreUpdateMoveCount();
	void decreasePreUpdateMoveCount();
	double getWinRate() const;
	void setWinRate(double dWinRate);
	double getUcbScore() const;
	void setUcbScore(double dUcbScore);

private:
	BaseDataPtr createData();

private:
	UctDataPtr m_pUctData;
};

} // joblevel

#endif // JL_UCTDATA_H
