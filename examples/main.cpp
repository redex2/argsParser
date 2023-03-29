#include <argsParser.h>
#include <iostream>

int main(int argc, char* argv[])
{
	argsParser parser;
	parser.addOpt("sqlite", 's', true);

	if (parser.parse(argc, argv))
	{
		if (parser.isOptSet('s'))
			std::cout << parser.getArgument('s') << std::endl;
		if (parser.isOptSet("sqlite"))
			std::cout << parser.getArgument("sqlite") << std::endl;
	}
	else
	{
		std::cout << "parse failed" << std::endl;
	}
}