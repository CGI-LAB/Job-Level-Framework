#ifndef JL_SEARCH_TREE_BROWSER_H
#define JL_SEARCH_TREE_BROWSER_H

#include <iostream>
#include <utility>
#include "Node.h"
#include "BaseData.h"

namespace joblevel 
{

class SearchTree;

class SearchTreeBrowser
{
public:
	SearchTreeBrowser(SearchTree& searchTree);
	void startBrowserMode() const;
	void printNode(std::ostream& os, NodePtr pNode) const;

private:
	/*!
	 * get a character without pressing enter
	 * @return the key pressed
	 * @from http://falldog7.blogspot.tw/2007/09/linux-linuxgetch-getche.html
	 */
	char getch() const;
	/*!
	 * handler of pressing the arror key, change the node
	 * @param  pNode reference of node, use to change current node
	 * @return true if node is changed, otherwise false
	 */
	bool handlePressArrowKey(NodePtr& pNode) const;
	void showPrompt() const;
	// print parent, current and children in console
	void printParentLayer(std::ostream& os, NodePtr pNode, bool bHighLight) const;
	void printChildrenLayer(std::ostream& os, NodePtr pParent, int iCurrentIndex) const;

	void printComment(std::ostream& os, NodePtr pNode, bool bExtend, bool bHide) const;
	std::string fillString(const std::string& sOrigin, int nTimes, 
		const std::string& sFilled) const;

	void printData(std::ostream& os, NodePtr pNode, bool bShowData) const;
	void printStringPairsToStringBuffer(std::vector<std::string>& vStringBuffer,
		const std::string& sDataGroup, const BaseData::StringPairVector& vStringPairs) const;
	std::pair<int, int> getMaxLengthOfStringPairs(const BaseData::StringPairVector& vStringPairs) const;
	void printStringBuffer(std::ostream& os, const std::vector<std::string>& vStringBuffer) const;

private:
	SearchTree& m_searchTree;
};

} // joblevel

#endif // JL_SEARCH_TREE_BROWSER_H