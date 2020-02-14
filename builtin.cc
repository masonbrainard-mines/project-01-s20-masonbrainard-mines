#include "builtin.hh"
#include "history.hh"
#include "alias.hh"

#include <unistd.h> //pwd
#include <pwd.h>
#include <sys/types.h>
#define GetCurrentDir getcwd
#include <limits.h> //pwd
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

//exit
std::string exit_builtin(std::vector<std::string> *args)
{
	return "exit";
}

//help
std::string help_builtin(void)
{
	return "Help is on the way!\necho\npwd\ncd\nexit\nalias\nunalias\n!!\n!n\n!-n\n!prefix\n!?search\n!#";
}
//echo
std::string echo_builtin(std::vector<std::string> *args)
{
	//throw them all in a string
	std::string echoed;

	for (int i = 1; i < args->size(); ++i) {
		echoed += args->at(i) + " ";
	}
	return echoed;
}
//cd
std::string cd_builtin(std::vector<std::string> *args)
{
	std::string output;
	std::string dir;
	if (args->size() > 1) {
		dir = args->at(1);
	} else {
		dir = "~";
	}
	int success = chdir(dir.c_str());
	if (success == 0) {
		output == "success!";
	} else {
		output == "failed";
	}
	return output;
}
//pwd
std::string pwd_builtin(void)
{
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}
//history
std::string history_builtin(history_table *history)
{
	return history_all(history);
}
//alias
std::string alias_builtin(alias_table *alias, std::vector<std::string> *args)
{
	std::string output = "";
	//figure out if we're printing out all or adding
	int numargs = args->size();
	if(numargs == 1)
	{
		output = alias_all(alias);
	}
	else
	{
		//for each argument
		for(int i = 1; i < args->size(); i++)
		{
			std::string temp = ""; //actually temp
			std::string alias_name = ""; //alias
			std::string func = ""; //func

			temp = args->at(i);
			alias_name = temp.substr(0, (temp.find('=')));
			func = temp.substr(temp.find('=') + 1, temp.length());

			alias_set(alias, &alias_name, &func);
		}
	}
	return output;
}
//unalias
std::string unalias_builtin(alias_table *alias, std::vector<std::string> *args)
{
	std::string output = "";
	
	for(int i = 1; i < args->size(); i++)
		{
			alias_unset(alias, &(args->at(i)));
		}

	return output;
}
//check builtin
std::string check_builtin(std::vector<std::string> *args, history_table *history, alias_table *alias)
{
	std::string output = "";
	int success = 0;
	std::string cmd_word = args->at(0);

	//args[0] is the command word
	if (cmd_word == "exit") {
		output = exit_builtin(args);
	} else if (cmd_word == "help") {
		output = help_builtin();
	} else if (cmd_word == "echo") {
		output = echo_builtin(args);
	} else if (cmd_word == "cd") {
		output = cd_builtin(args);
	} else if (cmd_word == "pwd") {
		output = pwd_builtin();
	} else if (cmd_word == "history") {
		output = history_builtin(history);
	} else if (cmd_word.at(0) == '!') {
		//!! previous command
		if(cmd_word.at(1) == '!'){
			int size = history_size(history) - 2;
			output = history_retrieve(history, &size);
		}
		//-nth command from current command
		else if(cmd_word.at(1) == '-')
		{
			//convert the thing into a number
			int temp = std::stoi(cmd_word.substr(2, cmd_word.length()));
			int size = history_size(history);
			if(temp < size)
			{
				temp = size - temp; //number of commands from the last
				output = history_retrieve(history, &temp);
			}
		}
		//!?search
		else if(cmd_word.at(1) == '?')
		{
			std::string temp = cmd_word.substr(2, cmd_word.length());
			output = history_find(history, &temp);
		}
		//!# current command
		else if(cmd_word.at(1) == '#')
		{
			int size = history_size(history) - 1;
			output = history_retrieve(history, &size);
		}
		else
		{
			//convert the thing into a number
			int temp = std::stoi(cmd_word.substr(1, cmd_word.length()));
			int size = history_size(history);
			std::string temps = cmd_word.substr(1, cmd_word.length());
			if(temp < size)
			{
				output = history_retrieve(history, &temp);
			}
			else
			{
				output = history_find(history, &temps);
			}
		}
		
		//output = "";
	} else if (cmd_word == "alias") {
		output = alias_builtin(alias, args);
	} else if (cmd_word == "unalias") {
		output = unalias_builtin(alias, args);
	} else {
		//check alias cmds
		std::string alias_cmd = alias_find(alias, &cmd_word);
		if(alias_cmd == "")
		{
			output = "fail";
		}
		else
		{
			std::vector<std::string> newargs;
			newargs.push_back(alias_cmd);
			for(int i = 1; i < args->size(); ++i)
			{
				newargs.push_back(args->at(i));
			}
			output = check_builtin(&newargs, history, alias);
		}		
	}
	return output;
}