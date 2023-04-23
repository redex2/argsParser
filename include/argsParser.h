#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <regex>

constexpr unsigned char OPT_SET = (1 << 0);
constexpr unsigned char REQ_ARGUMNET = (1 << 1);

class argsParser
{
public:
	void addOpt(std::string longOpt = "", char shortOpt = 0, std::string description = "", bool argument = false, std::string argumentDescription = "value");
	/*
		use after addOpt
	*/
	short parse(int& argc, char** argv, std::string execOpt = "[OPTIONS]");
	bool isOptSet(std::string opt);
	bool isOptSet(char opt);
	std::string getArgument(std::string opt);
	std::string getArgument(char opt);

	void addHelpTextLine(std::string text);
	std::string getHelp();
private:
	std::stringstream exe;
	std::stringstream help;
	std::vector <char> shortOpt;
	std::vector <std::string> longOpt;
	std::vector <std::string> argument;
	std::vector <unsigned char> meta;
};