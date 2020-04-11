#ifndef MAIN_H
#define MAIN_H

enum program_states { start, setup, can_setup, vcan_cfg, main_menu, rule_wiz, print, end };

enum program_states menu_start();
enum program_states menu_setup();
enum program_states menu_can_setup();
enum program_states menu_vcan_cfg();
enum program_states menu_main();
enum program_states menu_rule_wiz();
void interactive_menu();

#endif //MAIN_H
