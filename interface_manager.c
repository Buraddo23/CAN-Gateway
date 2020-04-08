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
	
	strcpy(cmd, "sudo ip link set up ");
	strcat(cmd, name);
	
	//system(cmd);
	printf("%s \n", cmd);
}

void can_config(char *name, char *bitrate) {
	char cmd[100];
	
	strcpy(cmd, "sudo ip link set ");
	strcat(cmd, name);
	strcat(cmd, " type can up bitrate ");
	strcat(cmd, bitrate);
	
	//system(cmd);
	printf("%s \n", cmd);
}

void canfd_config(char *name, char *bitrate, char *dbitrate) {
	char cmd[100];
	
	strcpy(cmd, "sudo ip link set ");
	strcat(cmd, name);
	strcat(cmd, " type can up bitrate ");
	strcat(cmd, bitrate);
	strcat(cmd, " dbitrate ");
	strcat(cmd, dbitrate);
	strcat(cmd, " fd on");
	
	//system(cmd);
	printf("%s \n", cmd);
}
