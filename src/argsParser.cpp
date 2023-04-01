#include "argsParser.h"

void argsParser::addOpt(std::string longOpt, char shortOpt, std::string description, bool argument, std::string argumentDescription)
{
	help << "  ";
	if ((shortOpt >= 'a' && shortOpt <= 'z') || (shortOpt >= 'A' && shortOpt <= 'Z'))
	{
		this->shortOpt.push_back(shortOpt);
		help << "-" << shortOpt << "\t";
	}
	else if (shortOpt == 0)
	{
		this->shortOpt.push_back(shortOpt);
		help << "\t";
	}
	else
	{
		throw std::invalid_argument("incorrect shortOpt");
	}

	if (longOpt.length() == 1)
	{
		throw std::invalid_argument("longOpt must have 0 or more than 1 char");
	}
	else if (std::regex_match(longOpt, std::regex("^([a-zA-Z]{1}[a-zA-Z0-9]{1,15})$")))
	{
		this->longOpt.push_back(longOpt);
		help << "--" << longOpt << "\t";
	}
	else if (longOpt.length() > 1)
	{
		throw std::invalid_argument("incorrect longOpt");
	}
	else
	{
		help << "\t";
		this->longOpt.push_back("");
	}

	if (argument)
	{
		this->meta.push_back(REQ_ARGUMNET);
		help << " <" << argumentDescription << "> \t";
	}
	else
	{
		this->meta.push_back(0);
		help << "\t\t";
	}
	this->argument.push_back("");

	help << "\t" << description << std::endl;
}

short argsParser::parse(int& argc, char** argv, std::string execOpt)
{
	exe << argv[0] << " " << execOpt << std::endl;
	int i = 0;
	while (++i < argc)
	{
		std::string arg(argv[i]);
		if (std::regex_match(arg, std::regex("^(-[a-zA-Z]{1})$")))
		{
			auto search = std::find(shortOpt.begin(), shortOpt.end(), arg[1]);
			if (search != shortOpt.end())
			{
				if (meta[search - shortOpt.begin()] & REQ_ARGUMNET)
				{
					if (i + 1 < argc)
						argument[search - shortOpt.begin()] = argv[++i];
					else return false;
				}
				meta[search - shortOpt.begin()] |= OPT_SET;
			}
			else return false;
		}
		else if (std::regex_match(arg, std::regex("^(--[a-zA-Z]{1}[a-zA-Z0-9]{1,15})$")))
		{
			auto search = std::find(longOpt.begin(), longOpt.end(), arg.erase(0, 2));
			if (search != longOpt.end())
			{
				if (meta[search - longOpt.begin()] & REQ_ARGUMNET)
				{
					if ((i + 1) < argc)
						argument[search - longOpt.begin()] = argv[++i];
					else return false;
				}
				meta[search - longOpt.begin()] |= OPT_SET;
			}
			else return false;
		}
		else return false;
	}
	return true;
}

bool argsParser::isOptSet(std::string opt)
{
	auto search = std::find(longOpt.begin(), longOpt.end(), opt);
	if (opt.length() < 2 || search == longOpt.end()) throw std::invalid_argument("Opt not found");
	if (meta[search - longOpt.begin()] & OPT_SET) return true;
	return false;
}

bool argsParser::isOptSet(char opt)
{
	auto search = std::find(shortOpt.begin(), shortOpt.end(), opt);
	if (opt == 0 || search == shortOpt.end()) throw std::invalid_argument("Opt not found");
	if (meta[search - shortOpt.begin()] & OPT_SET) return true;
	return false;
}

std::string argsParser::getArgument(std::string opt)
{
	auto search = std::find(longOpt.begin(), longOpt.end(), opt);
	if (search != longOpt.end())
		if (meta[search - longOpt.begin()] & REQ_ARGUMNET)
			return argument[search - longOpt.begin()];
		else
			throw std::invalid_argument("opt without argument!");
	throw std::invalid_argument("Opt not found");
}

std::string argsParser::getArgument(char opt)
{
	auto search = std::find(shortOpt.begin(), shortOpt.end(), opt);
	if (search != shortOpt.end())
		if (meta[search - shortOpt.begin()] & REQ_ARGUMNET)
			return argument[search - shortOpt.begin()];
		else
			throw std::invalid_argument("opt without argument!");
	throw std::invalid_argument("Opt not found");
}

void argsParser::addHelpTextLine(std::string text)
{
	help << text << std::endl;
}

std::string argsParser::getHelp()
{
	return exe.str() + help.str();
}
