#include "Program_Control.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <sys/wait.h>	// waitpid()
#include <sys/types.h>	// waitpid()
#include <unistd.h>		// fork(),exec(),pid_t,chdir()
#include <stdlib.h>		// exit()

void do_Command(std::vector<std::string> &tokens) {
	pid_t pid = fork();
	
	if (pid > 0) {			// parent
		int status;
		waitpid(pid, &status, 0);
	} else if (pid == 0) {	// child
		execv(&tokens[1], &tokens[1]);
	} else {
		std::cerr << tokens[1];
		exit(1);
	}
	return;
}

void scanner(std::string input, std::vector<std::string> &tokens) {
	std::vector<std::string>().swap(tokens); // free mem & replace with empty 1
	// Check for usage of quotes
	// one "two \" two"
	std::size_t pos1 = input.find("\""), pos2=1;
	int firstQuote = -1, secondQuote = -1;
	while (pos1 != std::string::npos && pos2 != std::string::npos) {//&& (pos1 != 0 && pos2 != 0)) { // if char(") is found in input str
		std::cout << "pos1 = " << pos1 << "\n";
		std::cout << "firstQuote = " << firstQuote << "\n";
		if (input[pos1-1] != '\\') {
			std::cout << "input[pos1-1] = '" << input[pos1-1] << "'\n";
			if (firstQuote == -1)
				firstQuote = pos1;
			pos2 = input.find("\"", pos1+1);
			if (pos2 == std::string::npos) {
				std::cerr << "Quotations do not match\n";
				return;
			}
			std::cout << "input[pos2-1] = '" << input[pos2-1] << "'\n";
			if (input[pos2-1] != '\\') {
				std::cout << "pos2 = " << pos2 << "\n";
				std::cout << "input.substr(0,firstQuote) = \"" << input.substr(0,firstQuote) << "\"\n";
				tokens.push_back(input.substr(0,firstQuote));
				std::cout << tokens.size() << '\n';
				std::cout << "input.substr(firstQuote,pos2-firstQuote) = \"" << input.substr(firstQuote,pos2-firstQuote) << "\"\n";
				tokens.push_back(input.substr(firstQuote+1, pos2-firstQuote));
				std::cout << tokens.size() << '\n';
				std::cout << "input is \"" << input << "\"\t";
				input = input.substr(pos2+1);	// pos2 until end
				std::cout << "input is \"" << input << "\"\n";
				firstQuote = -1;
				pos1 = input.find("\"");
			}
			else if (pos2+1 != input.size())	// if quote isn't at end, continue
				pos1 = input.find("\"", pos2+1);
			else {								// if at end, pos1 = npos to stop while
				if (input[input.size()-1] == '"' && firstQuote != -1) {
					tokens.push_back(input.substr(0,firstQuote));
					tokens.push_back(input.substr(firstQuote+1, pos2-firstQuote));
				}
				pos1 = std::string::npos;
			}
		}
	}
	if (tokens.empty()) // if no char(") was found
		tokens.push_back(input);
	std::cout << tokens.size() << '\n';
	// Split each not quoted token and keep order
	for (int i = 0; i < tokens.size(); i+=1) {
		std::vector<std::string> currTokens;
		split(currTokens, tokens[i], ' ');
		if (currTokens.size() > 1) {
			tokens.erase(tokens.begin()+i);
			for (int j = 0; j < currTokens.size(); j+=1)
				tokens.insert(tokens.begin()+i+j, currTokens[j]);
		}
	}
	std::cout << tokens.size() << '\n';
	return;
}

void split(std::vector<std::string> &currTokens, const std::string &item, char delim) {
	std::stringstream ss;
	ss.str(item);
	std::string temp;
	while (std::getline(ss, temp, delim))
		currTokens.push_back(temp);
}
