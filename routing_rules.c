#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can/raw.h>

#include "routing_rules.h"

struct monitor_data {
	int src_id, dst_id, rule_id;
	char *src_name, *dst_name;
};

int configure_can(char *name);
void *monitor_can(void *args);

int add_rule(char *src, char *dst) {
	int rule_id = 0;
	while(active_rules[rule_id]) rule_id++;
	active_rules[rule_id] = 1;
	sprintf(list_of_rules[rule_id], "source: %s; destination: %s", src, dst);
	printf("%s \n", list_of_rules[rule_id]);
	
	int socket_src = configure_can(src);
	int socket_dst = configure_can(dst);
	
	pthread_t monitor_thread;
	struct monitor_data *mon_args = malloc(sizeof *mon_args);
	mon_args->src_id   = socket_src;
	mon_args->dst_id   = socket_dst;
	mon_args->rule_id  = rule_id;
	mon_args->src_name = src;
	mon_args->dst_name = dst;
	int th_err = pthread_create(&monitor_thread, NULL, monitor_can, (void *)mon_args);
}

int configure_can(char *name) {
	int s0;
                 
    struct sockaddr_can addr0;
    struct ifreq ifr0;        
    char fl_bind;
    char bytes_wr;

    s0=socket(PF_CAN, SOCK_RAW, CAN_RAW);

    //CAN0 interface set up
    strcpy(ifr0.ifr_name, name);
    ioctl(s0, SIOCGIFINDEX, &ifr0);
    addr0.can_family = AF_CAN;
    addr0.can_ifindex = ifr0.ifr_ifindex;
    fl_bind=bind(s0,(struct sockaddr*)&addr0, sizeof(addr0));
    if(fl_bind==0){printf("bind ok\n");}
    
    return s0;
}

void *monitor_can(void *args) {
	struct monitor_data *data = args;
	int nbytes_rd;
	struct can_frame myFrame;

	while(active_rules[data->rule_id]) {
        nbytes_rd = read(data->src_id, &myFrame, sizeof(myFrame));
        
        printf("\n%d bytes: %s -> %s", nbytes_rd, data->src_name, data->dst_name);
        printf("\t%03X\t%02X\t", myFrame.can_id, myFrame.can_dlc);
        for (int i = 0; i < myFrame.can_dlc; i++)
            printf("%02X ", myFrame.data[i]);
        
        write(data->dst_id, &myFrame, sizeof(myFrame));
    }
}
