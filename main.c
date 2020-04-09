#include "interface_manager.h"
#include "routing_rules.h"

int main(void) {
	//vcan_init();
	//vcan_create("vcan0");
	//vcan_create("vcan1");
	//can_config("can0", "250000");
	//canfd_config("can0", "250000", "400000");
	
	add_rule("vcan0", "vcan1");
	list_rules();
	add_rule("vcan1", "vcan0");
	list_rules();
	remove_rule(0);
	list_rules();
	add_rule("vcan0", "vcan1");
	list_rules();
	flush_rules();
	list_rules();
	
	//while(1);
	
	return 0;
}
