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
	
	char *argv[tokens.size()];
	for (int i = 1; i < tokens.size(); i+=1)
		argv[i-1] = const_cast<char *>(tokens[i].c_str());
	argv[tokens.size()-1] = NULL;
	
	pid_t pid = fork();
	if (pid > 0) {			// parent
		int status;
		waitpid(pid, &status, 0);
	} else if (pid == 0) {	// child
		execvp(argv[0], argv);
		std::cerr << "ERROR: Could not execute command \"" << argv[0] << "\"\n";		// exec shouldn't return
		exit(1);
	} else {
		std::cerr << "ERROR: Could not execute fork for \"" << argv[0] << "\"\n";
		exit(1);
	}
	return;
}

int scanner(std::string input, std::vector<std::string> &tokens) {		// NEEDS TO IGNORE ALL WHITESPACE B/W TOKENS AND NEEDS
																		// TO ACCEPT \" IN THE MIDDLE OF QUOTATIONS
	std::vector<std::string>().swap(tokens); // free mem & replace with empty 1
	std::vector<std::string> currTokens;	// tokens split at quotes
	std::vector<bool> quoteTokens;		// keeps track of if each token is a quote or not
	// Check for usage of quotes
	// one "two \" two"
	std::size_t pos1 = input.find("\""), pos2=1, firstQuote=-1, secondQuote=-1;
	bool contSearch = true;
	while (pos1 != std::string::npos && contSearch) {			// if (") is found in input
		if (pos1 == 0) {		// if first (") is in begin of input
			firstQuote = pos1;
			input.erase(pos1,1);
			pos1 = input.find("\"");
		} else if (pos1 == input.size()-1 && firstQuote != -1) {
			std::cerr << "Error: Unmatched quotations\n";
			return(1);
		} else {				// if (") not first char in innut
			if (input[pos1-1] != '\\') {			// if first (") isn't escaped
				if (firstQuote != -1) {
					secondQuote = pos1;
					input.erase(pos1,1);
					currTokens.push_back(input.substr(firstQuote, secondQuote-firstQuote));
					quoteTokens.push_back(true);
					input = input.substr(secondQuote, input.size()-secondQuote);
					pos1 = input.find("\"");
					if (pos1 == std::string::npos && input.size() != 0) {		// if string w/ no quotes exists
						currTokens.push_back(input);
						quoteTokens.push_back(false);
					} else if (pos1 != std::string::npos && input.size() != 0)
						firstQuote = -1;
					continue;
				}
				firstQuote = pos1; 		// save pos1
				input.erase(pos1,1);	// get that (") out of here!!!!
				pos2 = input.find("\"");	// find next quotation
				if (input[pos2-1] != '\\' && pos2 != std::string::npos) {		// if next (") not escaped
					secondQuote = pos2;
					input.erase(pos2,1);
					currTokens.push_back(input.substr(0, firstQuote-1));	// add string b4 first (") to currTokens
					quoteTokens.push_back(false);
					currTokens.push_back(input.substr(firstQuote, secondQuote-firstQuote-1));	// add string b/w (") to currTokens
					quoteTokens.push_back(true);
					if (pos2+1 != input.size()) {	// if last (") not last char of input
						if (input.find("\"", pos2+1) == std::string::npos) {	// if no more (") left in input
							currTokens.push_back(input.substr(secondQuote, input.size()-secondQuote-1));
							quoteTokens.push_back(false);
							contSearch = false;
						} else { 					// if >=1 (") left in input
							input = input.substr(secondQuote, input.size()-secondQuote-1);
							pos1 = input.find("\"");
						}
					} else {						// if last (") is last char of input
						contSearch = false;
					}
				} else if (input[pos2-1] == '\\' && pos2 != std::string::npos) {			// if next (") is escaped
					input.erase(pos2-1,1);
					pos1 = input.find("\"", pos2);
				} else { 	// if firstQuote is found but not second one
					if (firstQuote != -1) {
						std::cerr << "Error: Unmatched quotations\n";
						return(1);
					}
				}
			} else {								// if first (") is escaped
				pos1 = input.find("\"", pos1+1);
			}
		}
	}

	if (currTokens.empty()) { // if no char(") was found
		currTokens.push_back(input);
		quoteTokens.push_back(false);
	}
	// Split each not quoted token and keep order
	for (int i = 0; i < currTokens.size(); i+=1) {
		if (!quoteTokens[i]) 		// if 'false' for no quotes in that element
			split(tokens, currTokens[i], ' ');
		else
			tokens.push_back(currTokens[i]);
	}
	return(0);
}

void split(std::vector<std::string> &tokens, const std::string &item, char delim) {
	std::stringstream ss;
	ss.str(item);
	std::string temp;
	while (std::getline(ss, temp, delim))
		if (temp != "")
			tokens.push_back(temp);
}
