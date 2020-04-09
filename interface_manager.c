#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface_manager.h"

void vcan_init() {
	system("sudo modprobe vcan");
	printf("sudo modprobe vcan \n");
}

void vcan_create(char *name) {
	char cmd[100];
	
	sprintf(cmd, "sudo ip link add %s type vcan", name);
	system(cmd);
	printf("%s \n", cmd);
	
	sprintf(cmd, "sudo ip link set up %s", name);
	system(cmd);
	printf("%s \n", cmd);
}

void can_config(char *name, char *bitrate) {
	char cmd[100];
	
	sprintf(cmd, "sudo ip link set %s type can up bitrate %s", name, bitrate);
	system(cmd);
	printf("%s \n", cmd);
}

void canfd_config(char *name, char *bitrate, char *dbitrate) {
	char cmd[100];
	
	sprintf(cmd, "sudo ip link set %s type can up bitrate %s dbitrate %s fd on", name, bitrate, dbitrate);
	system(cmd);
	printf("%s \n", cmd);
}
