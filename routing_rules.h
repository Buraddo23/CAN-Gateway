#ifndef ROUTING_RULES_H
#define ROUTING_RULES_H

#define MAX_RULES 64
#define MAX_STRING_SIZE 64

char list_of_rules[MAX_RULES][MAX_STRING_SIZE];
int active_rules[MAX_RULES];

int add_rule(char *src, char *dst);

void *read_can(void *arg);
void write_can(char *name);

#endif //ROUTING_RULES_H
