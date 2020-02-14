#ifndef ALIAS
#define ALIAS

#include <vector>
#include <string>
#include <map>
#include "alias.hh"


#include <stdio.h>
#include <string>
#include <map>

struct alias_table;

struct alias_table *alias_table_new(void);

void alias_table_free(struct alias_table *table);

void alias_set(struct alias_table *table, std::string *name,
	       std::string *replacement);

std::string alias_unset(struct alias_table *table, std::string *name);

std::string alias_find(struct alias_table *table, std::string *name);

std::string alias_all(struct alias_table *table);

#endif