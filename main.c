#include "interface_manager.h"
#include "routing_rules.h"

int main(void) {
	//vcan_init();
	//vcan_create("vcan0");
	//vcan_create("vcan1");
	//can_config("can0", "250000");
	//canfd_config("can0", "250000", "400000");
	
	//add_rule("vcan0", "vcan1");
	//list_rules();
	
	struct id_filter i_f;
	i_f.id = 0;
	i_f.mask = 15;
	i_f.is_match = 1;
	
	add_rule_filter("vcan1", "vcan0", i_f);
	list_rules();
	
	while(1);
	
	return 0;
}
