#include "BaseData.h"
#include "Node.h"

namespace joblevel
{

BaseData::Accessor::Accessor(NodePtr pNode, const std::string& sDataGroup)
	: m_pNode(pNode),
	  m_pBaseData(pNode->getData(sDataGroup))
{
}

void BaseData::Accessor::checkData()
{
	if (m_pBaseData == nullptr) {
		m_pBaseData = createData();
		m_pNode->setData(m_pBaseData->getDataGroup(), m_pBaseData);
	}
}

BaseDataPtr BaseData::Accessor::getBaseData() const
{
	return m_pBaseData;
}

NodePtr BaseData::Accessor::getNode() const
{
	return m_pNode;
}

}
