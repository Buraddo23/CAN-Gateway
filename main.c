#include <stdio.h>
#include <string.h>

#include "main.h"
#include "interface_manager.h"
#include "routing_rules.h"
#include "traffic_logger.h"

int opt_to_int(char *);
void menu_add_rule();
void menu_remove_rule();

int main(void) {
	open_log();
	interactive_menu();
	close_log();
	return 0;
}

void interactive_menu() {
	enum program_states curr_state = start;
	int main_loop = 1;	
	
	while (main_loop) {
		switch (curr_state) {
		case start:
			curr_state = menu_start();
			break;
		case setup:
			curr_state = menu_setup();
			break;
		case can_setup:
			curr_state = menu_can_setup();
			break;
		case vcan_cfg:
			curr_state = menu_vcan_cfg();
			break;
		case main_menu:
			curr_state = menu_main();
			break;
		case rule_wiz:
			curr_state = menu_rule_wiz();
			break;
		case end:
			main_loop = 0;
			break;
		default:
			main_loop = 0;
			printf("Invalid state");
			break;
		}
	}
}

enum program_states menu_start() {
	char opt[4];
	do {
		printf("Do you want to setup CAN interfaces? (y/n)\n");
		scanf("%3s", opt);
	} while (opt_to_int(opt) == -1);
	
	if (opt_to_int(opt))
		return setup;
	else
		return main_menu;
}

enum program_states menu_setup() {
	int n;
	do {
		printf("Select type: \n");
		printf("1. Hardware CAN\n");
		printf("2. Virtual CAN\n");
		printf("0. Setup done\n");
		scanf("%d", &n);
		printf("%d", n!=2);
	} while (n != 1 && n != 2 && n != 0);
	
	if (n == 1)
		return can_setup;
	else if (n == 2)
		return vcan_cfg;
	else if (n == 0)
		return main_menu;
}

enum program_states menu_can_setup() {
	char name[5], opt[4];
	int br;
	printf("CAN interface name: ");
	scanf("%4s", name);
	printf("Bitrate: ");
	scanf("%d", &br);
	do {
		printf("Do you want CAN-FD? (y/n)\n");
		scanf("%3s", opt);
	} while (opt_to_int(opt) == -1);
	if (opt_to_int(opt)) {
		int dbr;
		printf("Dbitrate: ");
		scanf("%d", &dbr);
		
		canfd_config(name, br, dbr);
	} else {
		can_config(name, br);
	}
	return setup;
}

enum program_states menu_vcan_cfg() {
	char name[6];
	printf("VCAN interface name: ");
	scanf("%5s", name);
	
	vcan_create(name);
	
	return setup;
}

enum program_states menu_main() {
	int n;
	do {
		printf("1. Add/remove/list rules\n");
		printf("2. Print frame traffic\n");
		printf("0. Exit program\n");
		scanf("%d", &n);
	} while (n != 1 && n != 2 && n != 0);
	
	if (n == 1)
		return rule_wiz;
	else if (n == 2)
		return print;
	else if (n == 0)
		return end;
}

enum program_states menu_rule_wiz() {
	int n;
	do {
		printf("1. Add a rule\n");
		printf("2. List all rules\n");
		printf("3. Remove rule\n");
		printf("4. Remove all rules\n");
		printf("0. Back to menu\n");
		scanf("%d", &n);
	} while (n != 1 && n != 2 && n != 3 && n != 4 && n != 0);
	
	switch (n) {
	case 1:				
		menu_add_rule();
		return rule_wiz;
	case 2:
		list_rules();				
		return rule_wiz;
	case 3:
		menu_remove_rule();
		return rule_wiz;
	case 4:
		flush_rules();
		return rule_wiz;
	case 0:
		return main_menu;
	}
}

int opt_to_int(char *opt) {
	if (!strcmp(opt, "yes") || !strcmp(opt, "y")) {
		return 1;
	} else if (!strcmp(opt, "no") || !strcmp(opt, "n")) {
		return 0;
	} else {
		return -1;
	}
}

void menu_add_rule() {
	char s[6], d[6], opt[4];
	
	printf("Source: ");
	scanf("%s", s);
	printf("Destination: ");
	scanf("%s", d);
	do {
		printf("Add filter? (y/n) \n");
		scanf("%3s", opt);
	} while (opt_to_int(opt) == -1);
	if (opt_to_int(opt)) {
		struct id_filter i_f;
		
		printf("CAN ID filter follows the rule: id&mask ==/!= frame_id&mask \n");
		printf("ID: ");
		scanf("%d", &i_f.id);
		printf("Mask: ");
		scanf("%d", &i_f.mask);
		
		char o[4];
		do {
			printf("Matches (==)? (y/n) ");
			scanf("%3s", o);
		} while (opt_to_int(o) == -1);
		i_f.is_match = opt_to_int(o);
		
		add_rule_filter(s,d,i_f);					
	} else {
		add_rule(s,d);
	}
}

void menu_remove_rule() {
	int n;
	list_rules();
	printf("Type the ID of the rule to remove: ");
	scanf("%d", &n);
	remove_rule(n);
}
