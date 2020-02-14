#ifndef BUILTIN
#define BUILTIN

#include "history.hh"
#include "alias.hh"

#include <string>
#include <vector>
#include <map>

std::string check_builtin(std::vector<std::string> *args, history_table *history, alias_table *alias);

#endif