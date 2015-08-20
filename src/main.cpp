#include "Application.h"
#include "Arguments.h"
#include "JobLevelConfigure.h"
#include <iostream>

using namespace joblevel;

int main(int argc, char* argv[])
{
	Arguments arguments;
	arguments.initProgramOption();
	arguments.initConfigure(JobLevelConfigure::g_configure);
	arguments.parse(argc, argv);
	if (arguments.shouldGenConfigureFile()) {
		arguments.genConfigureFile();
		return 0;
	}
	arguments.loadConfigure();
	arguments.reset();

	if(arguments.getMode() == "joblevel") {
		Application jlApp;
		jlApp.run();
	} else {
		std::cerr << "Unknown mode \"" << arguments.getMode() << "\"" << std::endl;
		exit(1);
	}
	return 0;
}


