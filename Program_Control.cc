#include "Program_Control.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

void scanner(std::string input, std::vector<std::string> &tokens) {
	std::vector<std::string>().swap(tokens); // free mem & replace with empty 1
	std::cout << tokens.size() << '\n';
	// Check for usage of quotes
	std::size_t pos1 = input.find("\""), pos2=1;
	while (pos1 != std::string::npos && (pos1 != 0 && pos2 != 0)) { // if char(") is found in input str
		std::cout << "butt1:   pos1 = " << pos1 << "\n";
		if (input.substr(pos1-1,1) != "\\") {
			std::cout << "butt2\n";
			std::cout << "input.substr(" << pos1 << "-1,1) = \"" << input.substr(pos1-1,1) << "\"\n";
			pos2 = input.find("\"", pos1+1);
			if (pos2 == std::string::npos) {
				std::cerr << "Quotations do not match\n";
				return;
			}
			if (input.substr(pos2-1,1) != "\\") { 	// FOR SOME REASON DOESN'T ENTER HERE
				std::cout << "butt3:   pos2 = " << pos2 << "\n";
				tokens.push_back(input.substr(0,pos1));
				std::cout << tokens.size() << '\n';
				tokens.push_back(input.substr(pos1, pos2-pos1));
				std::cout << tokens.size() << '\n';
				std::cout << "input is \"" << input << "\"\t";
				input = input.substr(pos2+1);	// pos2 until end
				std::cout << "input is \"" << input << "\"\n";
				pos1 = input.find("\"");
			}
			else
				pos1 = input.find("\"", pos2+1);
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
