#include "parser.hh"

#include <stdio.h>
#include <string>
#include <vector>
    
std::vector<std::string> parser(std::string *cmd)
{
    //the full command string
	std::string full_command = *cmd;
	std::vector<std::string> args;
	int spaces = 0;
	int index = 0;
	int spaceloc = 0;
	//see if there are more than 1 arg
	for (int i = 0; i < full_command.length(); ++i) {
		//need to count spaces
		if (full_command.at(i) == ' ') {
			spaces++;
		}
	}
	if (spaces == 0) {
		args.push_back(full_command);
	} else {
		//if there is 1 space, there are 2 arguements etc
		for (int i = 0; i < spaces; ++i) {
			spaceloc = full_command.find(' ');
			args.push_back(
				full_command.substr(0, spaceloc));
			full_command =
				full_command.substr(spaceloc + 1,
						    full_command.length());
			//this may need reworked
		}
		//the last argument
		args.push_back(full_command.substr(0, full_command.length()));
	}
return args;
}
