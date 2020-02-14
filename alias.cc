#include "alias.hh"
#include <stdio.h>
#include <string>
#include <map>
#include "error.h"

struct alias_table {
	//alias table is made from a map
	std::map<std::string, std::string>
		aliastable; //first is the alias, right is the fuction
};

struct alias_table *alias_table_new(void)
{
	//new alias table
	return new alias_table;
}

void alias_table_free(struct alias_table *table)
{
	delete table; //delete table that is sent
}

void alias_set(struct alias_table *table, std::string *name,
	       std::string *replacement)
{
	//TODO("Set an alias.");
	std::string Name = *name;
	std::string Replacement = *replacement;

	table->aliastable.emplace(
		Name,
		Replacement); //insert a new pair of strings, the alias and the cmd
}

std::string alias_unset(struct alias_table *table, std::string *name)
{
	//TODO("Unset an entry.");
	std::string output = "";
	if (table->aliastable.count(*name) > 0) {
		table->aliastable.erase(*name);
		output = "success";
	}
	else
	{
		output = "fail";
	}
	
	return output;
}

std::string alias_find(struct alias_table *table, std::string *name)
{
	std::string func = "";
	if (table->aliastable.count(*name) > 0) {
		func = table->aliastable.at(*name);
	}
	return func;
}

std::string alias_all(struct alias_table *table)
{
	std::string output = "";

	for (const auto &elem : table->aliastable) {
		output += ("\n" + elem.first + "=" + elem.second);
	}

	return output;
}
