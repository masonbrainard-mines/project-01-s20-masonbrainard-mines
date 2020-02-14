#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "builtin.hh"
#include "parser.hh"
#include "history.hh"
#include "alias.hh"

using namespace std;

int main()
{
	//get user name
	std::string cmd = "";
	vector<string> args;
	std::string output = "";

	bool cmd_output = true;

	char *name;
	struct passwd *pass;
	pass = getpwuid(getuid());
	name = pass->pw_name;

	auto history = history_table_new();

	auto alias = alias_table_new();

	while (output != "exit") {
		if (output != "fail") {
			cmd_output = true;
		} else {
			cmd_output = false;
		}

		cout << endl;
		//print username

		printf("%s", name);

		//print bool
		if (cmd_output) {
			cout << " O";
		} else {
			cout << " X";
		}
		cout << " $ ";
		//get user input

		getline(cin, cmd);

		//put in table
		history_set(history, &cmd);
		//parser(cmd)// -> send to command check
		try {
			args = parser(&cmd);
			//throw 10;
		} catch (int e) {
			output = "fail";
			continue;
		}
		try {
			output = check_builtin(&args, history, alias);
			//throw 20
		} catch (int e) {
			output = "fail";
			continue;
		}

		if (output == "exit") {
			break;
		}

		cout << output;
	}
	history_table_free(history);
	alias_table_free(alias);
	cout << "\nGoodbye World!";
	return 0;
}
