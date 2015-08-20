#include "SearchTreeBrowser.h"
#include <sstream>
#include <vector>
#include <termios.h>
#include <cassert>
#include "SReadLine.h"
#include "SearchTree.h"
#include "JobLevelConfigure.h"

namespace joblevel 
{

SearchTreeBrowser::SearchTreeBrowser(SearchTree& searchTree)
	: m_searchTree(searchTree)
{
}

void SearchTreeBrowser::startBrowserMode() const
{
	NodePtr pCurrentNode = m_searchTree.getCurrentNode();
	bool bExtendComment = false;
	bool bHideComment = true;
	bool bShowData = false;
	showPrompt();
	printNode(std::cout, pCurrentNode);
	std::cout << std::endl;
	printComment(std::cout, pCurrentNode, bExtendComment, bHideComment);
	printData(std::cout, pCurrentNode, bShowData);
	unsigned char c = 0;
	while ((c = getch()) != 'q' && c != 'Q') {
		bool bRedraw = false;
		// Arrow key is start with esc
		if (c == '\033') {
			bRedraw = handlePressArrowKey(pCurrentNode); 
		} else if (c == 'e' || c == 'E') {
			bExtendComment = !bExtendComment;
			bRedraw = true;
		} else if (c == 'c' || c == 'C') {
			bHideComment = !bHideComment;
			bRedraw = true;
		} else if (c == 'd' || c == 'D') {
			bShowData = !bShowData;
			bRedraw = true;
		}
		
		if (bRedraw) {
			showPrompt();
			printNode(std::cout, pCurrentNode);	
			std::cout << std::endl;
			printComment(std::cout, pCurrentNode, bExtendComment, bHideComment);
			printData(std::cout, pCurrentNode, bShowData);
		}
	}
	m_searchTree.setCurrentNode(pCurrentNode);
}

char SearchTreeBrowser::getch() const
{
    int i;//check whether read a value
    char ch;
    struct termios _old, _new;

    tcgetattr (0, &_old);
    memcpy (&_new, &_old, sizeof (struct termios));
    _new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (0, TCSANOW, &_new);
    i = read (0, &ch, 1);
    tcsetattr (0, TCSANOW, &_old);
    if (i == 1)/* ch is the character to use */ 
        return ch;
    else/* there was some problem; complain, return error, whatever */ 
        printf("error!");;
    return 0;
}

void SearchTreeBrowser::showPrompt() const
{
	rl_clear_screen(0, 0);
	std::cout << std::endl << "Press <Q> to exit browse mode." << std::endl
			  << "Use arrow key to move node." << std::endl;
}

bool SearchTreeBrowser::handlePressArrowKey(NodePtr& pNode) const
{
	// Arrow key is start with esc
	getch(); // skip the [
	switch(getch()) { // the real value
    case 'A':
        // code for arrow up
    	if (pNode->hasParent()) {
    		pNode = pNode->getParent();
    		return true;
    	}
        break;
    case 'B':
        // code for arrow down
    	if (pNode->hasChild(0)) {
    		pNode = pNode->getChild(0);
    		return true;
    	}
        break;
    case 'C':
        // code for arrow right
    	if (pNode->hasRight()) {
    		pNode = pNode->getRight();
    		return true;
    	}
        break;
    case 'D':
        // code for arrow left
    	if (pNode->hasLeft()) {
    		pNode = pNode->getLeft();
    		return true;
    	}
        break;
	}
	return false;
}

void SearchTreeBrowser::printNode(std::ostream& os, NodePtr pNode) const
{
	/* example
	  ROOT
	    |
	    +------+------+
	    |      |      |
	  B[DF]  W[AD]  W[FC]    
	           |
	    +------+------+
	    |      |      |
	  W[CD]  W[AD]  W[FC]
	*/
	os << "\033[1;37m"; // white
	if (pNode->hasParent()) {
		printParentLayer(os, pNode->getParent(), false);
		printChildrenLayer(os, pNode->getParent(), pNode->getIndex());
	}
	else {
		printParentLayer(os, pNode, true);
	}
	if (pNode->hasChild(0))
		printChildrenLayer(os, pNode, -1);
	os << "\033[0m"; // no color
}

void SearchTreeBrowser::printParentLayer(std::ostream& os, NodePtr pNode, bool bHighLight) const
{
	const int kPrintNodeShift = JobLevelConfigure::g_configure.iPrintNodeNumber / 2;
	// print sequence in color light blue
	os << "\033[1;32m" << pNode->getSequence() << "\033[1;37m   ";
	if (pNode->getSequence() < 10)
		os << " ";
	if (bHighLight)
		os << "\033[1;33m"; // yellow
	if (pNode->isRoot()) {
		os << "ROOT";
	} else {
		int iOriginIndex = pNode->getIndex();
		int iStartIndex = (iOriginIndex <= kPrintNodeShift)?0:(iOriginIndex - kPrintNodeShift);
		std::string sSecondLine = "     ";
		for (; iStartIndex != iOriginIndex; iStartIndex++) {
			os << "        ";
			sSecondLine += "        ";
		}
		std::string sMove = pNode->getMove()->serialize();
		os << sMove.substr(0, 5);
		if (sMove.length() > 5)
			os << std::endl << sSecondLine << sMove.substr(5, 5);
	}
	os << "\033[1;37m" << std::endl; // white
}

void SearchTreeBrowser::printChildrenLayer(std::ostream& os, NodePtr pParent, int iCurrentIndex) const
{
	const int kPrintNodeNumber = JobLevelConfigure::g_configure.iPrintNodeNumber;
	const int kPrintNodeShift = kPrintNodeNumber / 2;
	int iParentOriginIndex = pParent->getIndex();
	int iParentStartIndex = (iParentOriginIndex <= kPrintNodeShift)?0:(iParentOriginIndex - kPrintNodeShift);
	int iCurrentStartIndex = (iCurrentIndex <= kPrintNodeShift)?0:(iCurrentIndex - kPrintNodeShift);
	std::string sSecondLine;
	std::string sThirdLine;
	os << "       ";
	sSecondLine += (iCurrentStartIndex == 0)?"       ":"     --";
	sThirdLine += "       ";
	NodePtr pParentSibling = pParent->getLeft(iParentOriginIndex - iParentStartIndex);
	NodePtr pParentEndPtr = pParent->getRight();
	NodePtr pSibling = pParent->getChild(iCurrentStartIndex);
	NodePtr pSiblingEndPtr = pSibling->getRight(kPrintNodeNumber);
	bool bFindParent = false;
	while (pParentSibling != pParentEndPtr || pSibling != pSiblingEndPtr) {
		if (pParentSibling == pParent)
			bFindParent = true;
		os << (pParentSibling == pParent?"|":" ");
		if (pSibling != pSiblingEndPtr) {
			if (pSibling->hasLeft() && pSibling->hasRight()) {
				sSecondLine += pParentSibling == pParent?"+":
					(pSibling->getRight() == pSiblingEndPtr?"+--":"+");
			} else if (pSibling->hasLeft()) {
				sSecondLine += pParentSibling == pParent?"+":(bFindParent?"+":"+");
			} else if (pSibling->hasRight()) {
				sSecondLine += pParentSibling == pParent?"+":"+";
			} else {
				sSecondLine += pParentSibling == pParent?"|":"+";
			}
		} else {
				sSecondLine += pParentSibling == pParent?"+":"-";
		}
		os << "       ";
		if ((pSibling != pSiblingEndPtr && pSibling->getRight() != pSiblingEndPtr)
			|| bFindParent == false)
			sSecondLine += "-------";
		if (pSibling != pSiblingEndPtr)
			sThirdLine += "|       ";


		if (pParentSibling != pParentEndPtr)
			pParentSibling = pParentSibling->getRight();
		if (pSibling != pSiblingEndPtr)
			pSibling = pSibling->getRight();
	}

	os << std::endl << sSecondLine << std::endl << sThirdLine << std::endl;
	// don't use pCurrent to get sequence, see below
	os << "\033[1;32m" << pParent->getSequence() + 1 << "\033[1;37m   ";
	if (pParent->getSequence() + 1 < 10)
		os << " ";
	sSecondLine.clear();
	sSecondLine = "     ";
	//  this pCurrent will sometimes be NULL since it is only used to drow color.
	NodePtr pCurrent = pParent->getChild(iCurrentIndex);
	pSibling = pParent->getChild(iCurrentStartIndex);
	pSiblingEndPtr = pSibling->getRight(kPrintNodeNumber);
	for (; pSibling != pSiblingEndPtr; pSibling = pSibling->getRight()) {
		std::string sMove = pSibling->getMove()->serialize();
		os << (pCurrent == pSibling?"\033[1;33m":"") 
			<< sMove.substr(0, 5) << "   \033[1;37m";
		if (sMove.length() > 5) 
			sSecondLine += (pCurrent == pSibling?"\033[1;33m":"") 
				+ sMove.substr(5, 5) + "   \033[1;37m";
	}
	if (sSecondLine != "     ")
		os << std::endl << sSecondLine;
	os << std::endl;
}

void SearchTreeBrowser::printComment(std::ostream& os, NodePtr pNode, bool bExtend, bool bHide) const
{
	if (bHide) {
		std::string sHint = "[Press <C> to toogle comments]";
		os << "  \033[1;36m" << sHint << "\033[0m" << std::endl;
		return;
	}
	const int kPrintCommentWidth = JobLevelConfigure::g_configure.iPrintCommentWidth;
	const int kPrintCommentLine = JobLevelConfigure::g_configure.iPrintCommentLine;
	// print ┌── Comment ────────┐
	std::string sHeadLine = "\033[1;37m+-- Comments ";
	sHeadLine = fillString(sHeadLine, kPrintCommentWidth - 11, "-");
	sHeadLine.append("-+");
	os << sHeadLine << std::endl;
	// print │ some comments...  │
	int iLineCounter = 0;
	bool bStopPrinting = false;
	std::string sHint;
	std::istringstream iss(pNode->getComment());
	std::string sLineOfComment;
	while (bStopPrinting == false && getline(iss, sLineOfComment)) {
		do {
			std::string sLine = sLineOfComment.substr(0, kPrintCommentWidth);
			int nFindReturnR = sLine.find('\r');
			if (nFindReturnR != std::string::npos)
				sLine.erase(nFindReturnR);
			if (sLine.length() < kPrintCommentWidth)
				sLine.append(kPrintCommentWidth - sLine.length(), ' ');
			os << "| " << sLine << " |" << std::endl;
			if (sLineOfComment.length() > kPrintCommentWidth)
				sLineOfComment = sLineOfComment.substr(kPrintCommentWidth);
			else
				sLineOfComment.clear();
			// increment line counter and check if need stop
			iLineCounter++;
			if (bExtend == false) {
				if (iLineCounter == kPrintCommentLine) {
					sHint = "[Press <E> to extend]";
					sHint.append(kPrintCommentWidth - sHint.length(), ' ');
					os << "| \033[1;34m" << sHint << "\033[1;37m |" << std::endl;
					bStopPrinting = true;
					break;
				}
			}
		} while (sLineOfComment.length() != 0);
	}
	if (bExtend && iLineCounter > kPrintCommentLine) {
		sHint = "[Press <E> to shrink]";
		sHint.append(kPrintCommentWidth - sHint.length(), ' ');
		os << "| \033[1;34m" << sHint << "\033[1;37m |" << std::endl;
	} 
	// print └───────────────────┘
	std::string sFootLine = "+-";
	sFootLine = fillString(sFootLine, kPrintCommentWidth, "-");
	sFootLine.append("-+\033[0m");
	os << sFootLine << std::endl;
	/* if (bStopPrinting) {
		std::string sHint = "[Press <C> to show all comments]";
		sHint.append(kPrintCommentWidth - sHint.length(), ' ');
		os << "  \033[1;36m" << sHint << "\033[0m" << std::endl;
	} */
}

std::string SearchTreeBrowser::fillString(const std::string& sOrigin, int nTimes, 
	const std::string& sFilled) const
{
	std::string sResult = sOrigin;
	for (int i = 0; i < nTimes; ++i)
		sResult.append(sFilled);
	return sResult;
}

void SearchTreeBrowser::printData(std::ostream& os, NodePtr pNode, bool bShowData) const
{
	std::string sHint;
	if (bShowData == false) {
		sHint = "[Press <D> to toggle data]";
		os << "  \033[1;36m" << sHint << "\033[0m" << std::endl;
		return;
	}
	os << "\033[1;37m";
	std::vector<std::string> vStringBuffer;
	int iCounter = 0;
	const Node::DataMap& dataMap = pNode->getDataMap();
	if (dataMap.empty()) {
		os << "+---------+" << std::endl
		   << "| No data |" << std::endl
		   << "+---------+" << std::endl;
	}
	for (Node::DataMap::const_iterator cit = dataMap.begin(); cit != dataMap.end(); ++cit) {
		BaseData::StringPairVector vStringPairs = (cit->second)->getStringPairs();
		printStringPairsToStringBuffer(vStringBuffer, (cit->second)->getDataGroup(), vStringPairs);
		if (++iCounter % 2 == 0) {
			printStringBuffer(os, vStringBuffer);
			vStringBuffer.clear();
		}
	}
	printStringBuffer(os, vStringBuffer);
	os << "\033[0m";
}

void SearchTreeBrowser::printStringPairsToStringBuffer(std::vector<std::string>& vStringBuffer,
	const std::string& sDataGroup, const BaseData::StringPairVector& vStringPairs) const
{
	while (vStringBuffer.size() < vStringPairs.size() + 2) {
		std::string stringBuffer;
		if (vStringBuffer.size() != 0) {
			std::string sLastLine = vStringBuffer.back();
			if (sLastLine.length() != 0) {
				std::string sFilledWhiteSpace;
				sFilledWhiteSpace.append(sLastLine.length(), ' ');
				stringBuffer += sFilledWhiteSpace;
			}
		}
		vStringBuffer.push_back(stringBuffer);
	}
	assert(vStringBuffer.size() >= 2);
	std::pair<int, int> maxLength = getMaxLengthOfStringPairs(vStringPairs);
	int iTotalLength = maxLength.first + maxLength.second;
	vStringBuffer[0] += "+-- " + sDataGroup + " data -";
	vStringBuffer[0] += fillString(std::string(), iTotalLength - sDataGroup.length() - 5, "-")
					 + "+  ";
	for (BaseData::StringPairVector::const_iterator cit = vStringPairs.begin();
		cit != vStringPairs.end(); ++cit) {
		int iStringBufferIndex = cit - vStringPairs.begin() + 1;
		std::string sProperty = cit->first;
		if (sProperty.length() < maxLength.first)
			sProperty.append(maxLength.first - sProperty.length(), ' ');
		std::string sValue = cit->second;
		if (sValue.length() < maxLength.second)
			sValue.append(maxLength.second - sValue.length(), ' ');
		vStringBuffer[iStringBufferIndex] += "| " + sProperty + " | " + sValue + " |  ";
	}
	vStringBuffer[vStringPairs.size() + 1] += "+-" + fillString(std::string(), iTotalLength + 3, "-")
						 				+ "-+  ";
}

std::pair<int, int> SearchTreeBrowser::getMaxLengthOfStringPairs(const BaseData::StringPairVector& vStringPairs) const
{
	int iMaxPropertyLength = 0;
	int iMaxValueLength = 0;
	for (BaseData::StringPairVector::const_iterator cit = vStringPairs.begin();
		cit != vStringPairs.end(); ++cit) {
		if ((cit->first).length() > iMaxPropertyLength)
			iMaxPropertyLength = (cit->first).length();
		if ((cit->second).length() > iMaxValueLength)
			iMaxValueLength = (cit->second).length();
	}
	return std::make_pair(iMaxPropertyLength, iMaxValueLength);
}

void SearchTreeBrowser::printStringBuffer(std::ostream& os, const std::vector<std::string>& vStringBuffer) const
{
	for (std::vector<std::string>::const_iterator cit = vStringBuffer.begin();
		cit != vStringBuffer.end(); ++cit) {
		os << *cit << std::endl;
	}
}

} // joblevel
