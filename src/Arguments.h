#ifndef JL_ARGUMENTS_H
#define JL_ARGUMENTS_H

#include <string>
#include <iostream>
#include "ProgramOption.h"
#include "ConfigureLoader.h"

namespace joblevel
{

class BaseConfigure;
/*!
	@brief	This class is for parsing arguments of program, including
			setting up configure and generate configure file
	@author	T.F. Liao, chaochin
	@date	2015/7/13
 */
class Arguments
{
public:
	Arguments();
	void initProgramOption();
	void initConfigure(BaseConfigure& configure);
	void parse(int argc, char* argv[]);
	void loadConfigure();
	bool shouldGenConfigureFile();
	void genConfigureFile();
	void printDefaultConfigure(std::ostream& os);
	void reset();
	std::string getMode();

private:
	ProgramOption m_programOption;
	ConfigureLoader m_configureLoader;

	std::string m_sMode;
	std::string m_sGenFileName;
	std::string m_sConfigureFileName;
	std::string m_sConfigureString;
};

}

#endif
