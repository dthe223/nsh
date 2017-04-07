#include "Builtin_Cmds.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/types.h>

void prompt_Change(std::string &prompt, std::vector<std::string> &tokens) {
	if (tokens.size() > 2)
		std::cerr << tokens[0] << ": too many arguments\n";
	else if (tokens.size() < 2)
		std::cerr << tokens[0] << ": not enough arguments\n";
	else {
		prompt = tokens[1];
		std::cout << prompt << std::endl;
		//prompt += "> ";
	}
	return;
}

void setvar(std::vector<std::string> &tokens, std::map<std::string, std::string> &userVars) {
	if(tokens.size() > 3)
		std::cerr << tokens[0] << ": too many arguments\n";
	else if(tokens.size() < 3)
		std::cerr << tokens[0] << ": not enough arguments\n";
	else 
		userVars[tokens[1]] = tokens[2];
}

void dir(std::vector<std::string> &tokens) {
	if(tokens.size() > 2)
	{
		std::cerr << tokens[1] << ": too many arguments \n";
		return;
	}
	else if(tokens.size() < 2)
	{
		std::cerr << tokens[1] << ": not enough arguments\n";
		return;
	}
	else
	{
		int marker = chdir(tokens[1].c_str());
		if(marker == 0){
			chdir(tokens[1].c_str());
		}
		else{
			std::cerr << tokens[1] << ": No such file or directory \n";
		}
	}
}

void procs(std::map<int, std::string> &processes) {
	int status;
	if(processes.empty())
	{
		std::cout << "No processes are running in the background" << std::endl;
		return;
	}
	for(std::map<int, std::string>::const_iterator i = processes.begin(); i != processes.end(); ++i) {
		std::cout << "Background Processes: \n";
		std::cout << "Process ID: " << i->first << " ";
		std::cout << i->second << '\n';
		//if(waitpid(proglist[i], &status, WNOHANG))
		//{
		//	std::cout << "(completed)" << std::endl;
		//	proglist.erase(proglist.begin()+i);
		//}
	}
}

void display_Vars(std::map<std::string, std::string> &userVars) {
	std::cout << "User Variables:\n";
	for(std::map<std::string, std::string>::const_iterator i = userVars.begin(); i != userVars.end(); ++i)
		std::cout << i->first << " : " << i->second << '\n';
}
