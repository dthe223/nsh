#include "Builtin_Cmds.h"
#include <iostream>
#include <string>
#include <vector>

void prompt_Change(std::string &prompt, std::vector<std::string> &tokens) {
	if (tokens.size() > 2)
		std::cerr << tokens[0] << ": too many arguments\n";
	else if (tokens.size() < 2)
		std::cerr << tokens[0] << ": not enough arguments\n";
	else {
		prompt = tokens[1];
		prompt += "> ";
	}
	return;
}
