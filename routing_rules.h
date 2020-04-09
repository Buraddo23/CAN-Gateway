#ifndef ROUTING_RULES_H
#define ROUTING_RULES_H

struct id_filter {
	int id, mask, is_match;
};

int add_rule_filter(char*, char*, struct id_filter);
int add_rule(char*, char*);
void list_rules();
void remove_rule(int);
void flush_rules();

#endif //ROUTING_RULES_H
