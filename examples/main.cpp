#include <argsParser.h>
#include <iostream>

int main(int argc, char* argv[])
{
	argsParser parser;
	parser.addOpt("sqlite", 's', "set sqlite database file", true, "file");
	parser.addOpt("solve", 0, "solve puzzle", true, "puzzle");
	parser.addOpt("", 'l', "set level", true, "level");
	parser.addOpt("cli", 0, "ouptut to stdout");

	if (parser.parse(argc, argv))
	{
		if (parser.isOptSet('s'))
			std::cout << parser.getArgument('s') << std::endl;
		if (parser.isOptSet("sqlite"))
			std::cout << parser.getArgument("sqlite") << std::endl;
		if (parser.isOptSet("cli"))
			std::cout << "cli set";
	}
	else
	{
		std::cerr << parser.getHelp();
	}
}