#include "Program_Control.h"
#include <string>
#include <vector>
#include <iostream>

void scanner(std::string input, std::vector<std::string> &tokens) {
// just look for next quotation, unless "\" is in front of it
	std::vector<std::string>().swap(tokens); // free mem & replace with empty 1
	std::size_t pos = input.find("\"");
	if (pos != std::string::npos) { // if char(") found in input str
// gotta check to see if quotations match,  fuck this shit	
	} 
	pos = input.find("'");
	if (pos != std::string::npos) { // if char(') found in input str

	}
}
