#ifndef JL_SEARCHTREE_H
#define JL_SEARCHTREE_H

#include <string>
#include "Node.h"
#include "SgfSerializer.h"

namespace joblevel
{

class SearchTree
{
public:
	SearchTree();
	~SearchTree();
	NodePtr getRoot() const;
	NodePtr getCurrentNode() const;
	void setCurrentNode(NodePtr pNode);
	bool loadSgfFile(std::string sFileName);
	bool saveSgfFile(std::string sFileName);

private:
	NodePtr& m_pRoot;
	NodePtr m_pCurrentNode;
	SgfSerializer m_sgfSerializer;
};

}

#endif