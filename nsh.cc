#include <iostream>
#include <string>
#include <vector>
#include "Program_Control.h"
//using namespace std;

int main() {

	std::string prompt = "nsh> ", userin = "";
	std::vector<std::string> tokens;
	std::cout << prompt;
	std::getline(std::cin, userin);
	while (userin != "done" && userin != "<control-D>") {
		scanner(userin, tokens);
		//std::cout << "The tokens are";
		//for (int i=0; i<tokens.size();i+=1)
		//	std::cout << " " << tokens[i];
		//std::cout << '\n';
		std::cout << prompt;
		std::getline(std::cin, userin);
	}

	return 0;
}
