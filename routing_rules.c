#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can/raw.h>

#include "routing_rules.h"

struct monitor_data {
	int socket_id;
	int rule_id;
};

int configure_can(char *name);
struct can_frame gen_frame(int id, unsigned char dlc, unsigned char *data);
void monitor_can(int socket);

int add_rule(char *src, char *dst) {
	int i = 0;
	while(active_rules[i]) i++;
	active_rules[i] = 1;

	sprintf(list_of_rules[i], "source: %s; destination: %s", src, dst);
	printf("%s \n", list_of_rules[i]);
	
	int socket_src = configure_can(src);
	int socket_dst = configure_can(dst);
	
	
}

void *read_can(void *arg) {
	int s0 = configure_can((char*) arg);
	
	monitor_can(s0);
}

void write_can(char *name) {
    int s0 = configure_can(name);

	unsigned char a[8];
	for (int i = 0; i < 8; ++i) {
		a[i] = 0xAA;
	}

    struct can_frame myFrame = gen_frame(0x10, 8, a);    
	
    while(1) {
        char bytes_wr=write(s0,&myFrame,sizeof(myFrame));
        printf("bytes_wr: %d \n", bytes_wr);
        sleep(1);
    }
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

struct can_frame gen_frame(int id, unsigned char dlc, unsigned char *data) {
	struct can_frame myFrame;    	     
    
    myFrame.can_id  = id;
    myFrame.can_dlc = dlc; 
    memcpy(myFrame.data, data, dlc*sizeof(unsigned char));
        
    return myFrame;  
}

void monitor_can(int socket) {
	int nbytes_rd;
	struct can_frame myFrameRec;

	while(1) {
        nbytes_rd = read(socket, &myFrameRec, sizeof(struct can_frame));
                        
        printf("\n nbytes_rd:%d  ",nbytes_rd );
        printf("can_id:%02X  ", myFrameRec.can_id);
        printf("can_dlc:%02X  data:  ", myFrameRec.can_dlc);
        for (int i = 0; i < myFrameRec.can_dlc; i++)
            printf("%02X ", myFrameRec.data[i]);
    }
}
