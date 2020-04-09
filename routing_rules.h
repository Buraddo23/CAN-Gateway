#ifndef ROUTING_RULES_H
#define ROUTING_RULES_H

int add_rule_filter(char*, char*, char*);
int add_rule(char*, char*);
void list_rules();
void remove_rule(int);
void flush_rules();

#endif //ROUTING_RULES_H
