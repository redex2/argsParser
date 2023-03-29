#include "argsParser.h"

bool argsParser::addOpt(std::string longOpt, char shortOpt, bool argument)
{
	if (longOpt.length() <= 1)return false;
	if (!((shortOpt >= 'a' && shortOpt <= 'z') || (shortOpt >= 'A' && shortOpt <= 'Z'))) return false;
	this->longOpt.push_back(longOpt);
	this->shortOpt.push_back(shortOpt);
	if (argument)
		this->meta.push_back(REQ_ARGUMNET);
	else
		this->meta.push_back(0);
	this->argument.push_back("");
	return true;
}

short argsParser::parse(int& argc, char** argv)
{
	exe = argv[0];
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
		else if (std::regex_match(arg, std::regex("^(--[a-zA-Z]{1}[a-zA-Z0-9]{1,})$")))
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
	if (search == longOpt.end()) throw std::invalid_argument("Opt not found");
	if (meta[search - longOpt.begin()] & OPT_SET) return true;
	return false;
}

bool argsParser::isOptSet(char opt)
{
	auto search = std::find(shortOpt.begin(), shortOpt.end(), opt);
	if (search == shortOpt.end()) throw std::invalid_argument("Opt not found");
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