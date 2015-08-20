#ifndef JL_BASEDATA_H
#define JL_BASEDATA_H

#include <string>
#include <utility>
#include <vector>

namespace joblevel 
{
/*!
	@brief	Base data for decouple the node and data. Node doesn't need to know
			which data it has and how to serialize and use.
	@author	chaochin
	@date	2015/7/22
 */
class BaseData
{
public:
	// forword declaration of BaseData::Accessor, need to declare below
	class Accessor;

	typedef std::pair<std::string, std::string> StringPair;
	typedef std::vector<StringPair> StringPairVector;

public:
	virtual ~BaseData() {};
	virtual std::string serialize() const = 0;
	virtual StringPairVector getStringPairs() const = 0;
	virtual std::string getDataGroup() const = 0;

protected:
	BaseData() {};
	BaseData(const BaseData&);
	BaseData& operator=(const BaseData&);
};

typedef BaseData* BaseDataPtr;

// forward declaration for NodePtr
class Node;
typedef Node* NodePtr;

/*!
	@brief	Base Accessor of base data, used to retrive data from node and check
			whether the data is exist, if not, create the data by derived class.
	@author	chaochin
	@date	2015/7/23
 */
class BaseData::Accessor
{
public:
	Accessor(NodePtr pNode, const std::string& sDataGroup);
	virtual ~Accessor() {};
	NodePtr getNode() const;

protected:
	BaseDataPtr getBaseData() const;
	void checkData();
	virtual BaseDataPtr createData() = 0;

private:
	NodePtr m_pNode;
	BaseDataPtr m_pBaseData;
};

} // joblevel

#endif // JL_BASEDATA_H
