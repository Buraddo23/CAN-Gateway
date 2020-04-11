#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface_manager.h"

static int VCAN_INIT = 0;

void vcan_init();

void vcan_create(char *name) {
	char cmd[100];
	
	vcan_init();
		
	sprintf(cmd, "sudo ip link add %s type vcan", name);
	system(cmd);
	//printf("%s \n", cmd);
	
	sprintf(cmd, "sudo ip link set up %s", name);
	system(cmd);
	//printf("%s \n", cmd);
}

void can_config(char *name, int bitrate) {
	char cmd[100];
	
	sprintf(cmd, "sudo ip link set %s type can up bitrate %d", name, bitrate);
	system(cmd);
	//printf("%s \n", cmd);
}

void canfd_config(char *name, int bitrate, int dbitrate) {
	char cmd[100];
	
	sprintf(cmd, "sudo ip link set %s type can up bitrate %d dbitrate %d fd on", name, bitrate, dbitrate);
	system(cmd);
	//printf("%s \n", cmd);
}

void vcan_init() {
	if (!VCAN_INIT) {
		system("sudo modprobe vcan");
		VCAN_INIT = 1;
	}
}
