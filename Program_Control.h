#ifndef PROGRAM_CONTROL_H
#define PROGRAM_CONTROL_H

#include <string>
#include <vector>

void do_Command(std::vector<std::string> &tokens);
int scanner(std::string input, std::vector<std::string> &tokens);
void split(std::vector<std::string> &currTokens, const std::string &item, char delim);

#endif
