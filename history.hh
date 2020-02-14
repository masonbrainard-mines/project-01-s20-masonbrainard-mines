#ifndef HISTORYSHELL
#define HISTORYSHELL

#include <vector>
#include <string>

struct history_table;

struct history_table *history_table_new(void);

void history_table_free(struct history_table *table);

int history_size(struct history_table *table);

void history_set(struct history_table *table, std::string *cmd);

std::string history_retrieve(struct history_table *table, int *number);

std::string history_find(struct history_table *table, std::string *search);

std::string history_all(struct history_table *table);

#endif