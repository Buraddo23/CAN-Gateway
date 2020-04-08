#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface_manager.h"

void vcan_init() {
	//system("sudo modprobe vcan");
	printf("sudo modprobe vcan \n");
}

void vcan_create(char *name) {
	char cmd[100];
	
	strcpy(cmd, "sudo ip link add ");
	strcat(cmd, name);
	strcat(cmd, " type vcan");
	
	//system(cmd);
	printf("%s \n", cmd);
}
