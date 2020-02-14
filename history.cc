#include "history.hh"

#include <stddef.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>


struct history_table {
	//alias table is made from a map
	std::vector<std::string> historytable;
};

struct history_table *history_table_new(void)
{
	return new history_table;
}

void history_table_free(struct history_table *table)
{
	delete table;
}

int history_size(struct history_table *table){
    return table->historytable.size();
}

void history_set(struct history_table *table, std::string *cmd)
{
	std::string temp = *cmd;
	table->historytable.push_back(temp);
}

std::string history_retrieve(struct history_table *table, int *number)
{
	int temp = *number;
	return table->historytable.at(temp);
}

std::string history_find(struct history_table *table, std::string *search)
{
	std::string temp = *search;
	std::string output = "not found";
	for (int i = 0; i < table->historytable.size() -1 ; ++i) {
		if (table->historytable.at(i).find(temp) != std::string::npos) {
			output = table->historytable.at(i);			
		}
	}
	return output;
}

std::string history_all(struct history_table *table)
{
	std::string output = "";

	for (int i = 0; i < table->historytable.size(); ++i) {
		output += ("\n" + table->historytable.at(i));
	}

	return output;
}
