#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <regex>

constexpr unsigned char OPT_SET = (1 << 0);
constexpr unsigned char REQ_ARGUMNET = (1 << 1);

class argsParser
{
public:
	bool addOpt(std::string longOpt, char shortOpt, bool argument = false);
	short parse(int& argc, char** argv);
	bool isOptSet(std::string opt);
	bool isOptSet(char opt);
	std::string getArgument(std::string opt);
	std::string getArgument(char opt);
private:
	std::string exe = "";
	std::vector <char> shortOpt;
	std::vector <std::string> longOpt;
	std::vector <std::string> argument;
	std::vector <unsigned char> meta;
};