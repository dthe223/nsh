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
		std::cout << "userin is \"" << userin << "\"\n";
		scanner(userin, tokens);
		std::cout << prompt;
		std::getline(std::cin, userin);
	}

	return 0;
}
