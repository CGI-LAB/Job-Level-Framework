#include "Arguments.h"
#include "BaseConfigure.h"
#include <cstdlib>
#include <fstream>

namespace joblevel 
{

Arguments::Arguments()
	: m_sMode("joblevel")
{
}

void Arguments::initProgramOption()
{
	ProgramOption& po = m_programOption;
	po.regOption("gen", m_sGenFileName,
		"generate default configure file");
	po.regOption("mode", m_sMode,
		"specify running mode (joblevel)");
	po.regOption("conf_file", m_sConfigureFileName,
		"specify configure file (load first)");
	po.regOption("conf_str", m_sConfigureString,
		"specify configure string (overwrite conf_file)");
}

void Arguments::initConfigure(BaseConfigure& configure)
{
	configure.setConfigureOptions(m_configureLoader);
}

void Arguments::parse(int argc, char* argv[])
{
	ProgramOption& po = m_programOption;
	if (!po.parse(argc, argv)) {
		std::cerr << po.getErrorMsg() << std::endl
				  << po.getUsage(argv[0]) << std::endl;
		exit(1);
	}
}

void Arguments::loadConfigure()
{
	ConfigureLoader& cl = m_configureLoader;
	std::string& sConfigureFileName = m_sConfigureFileName;
	std::string& sConfigureString = m_sConfigureString;
	if (sConfigureFileName.length() != 0) {
		if (!cl.loadConfigureFromFile(sConfigureFileName)) {
			std::cerr << "Loading from file: " 
					  << cl.getErrorMsg() << std::endl; 
			exit(1);
		}
	}
	if (sConfigureString.length() != 0) {
		if (!cl.loadConfigureFromString(sConfigureString)) {
			std::cerr << "Loading from string: " 
					  << cl.getErrorMsg() << std::endl; 
			exit(1);
		}
	}
}

bool Arguments::shouldGenConfigureFile()
{
	return m_sGenFileName.length() != 0;
}

void Arguments::genConfigureFile()
{
	std::string& sGenFileName = m_sGenFileName;
	std::ofstream fout(sGenFileName.c_str());
	if (!fout) {
		std::cerr << "unable to open file " << sGenFileName
				  << " to write" << std::endl;
		exit(1);
	}
	fout << m_configureLoader.getDefaultConfigure() << std::endl;
	fout.close();
}

void Arguments::printDefaultConfigure(std::ostream& os)
{
	os << m_configureLoader.getDefaultConfigure() << std::endl;
}

void Arguments::reset()
{
	m_programOption.reset();
	m_configureLoader.reset();
}

std::string Arguments::getMode()
{
	return m_sMode;
}

}

