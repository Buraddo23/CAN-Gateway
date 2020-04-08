#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can/raw.h>

#include "interface_monitor.h"

int configure_can(char *name);
void *monitor_can(void *ptr);

void read_can(char *name) {
	pthread_t read_thread;
	int th_err;

	int s0 = configure_can(name);
	
	printf("s0 %d \n", s0);
	
	th_err = pthread_create(&read_thread, NULL, monitor_can, &s0);
	printf("pthread return %d \n", th_err);
	
	pthread_join(read_thread, NULL);
}

int configure_can(char *name) {
	int s0;
                 
    struct sockaddr_can addr0;
    struct ifreq ifr0;        
    char fl_bind;
    char bytes_wr;

    s0=socket(PF_CAN, SOCK_RAW, CAN_RAW);

    //CAN0 interface set up
    strcpy(ifr0.ifr_name, "vcan0");
    ioctl(s0, SIOCGIFINDEX, &ifr0);
    addr0.can_family = AF_CAN;
    addr0.can_ifindex = ifr0.ifr_ifindex;
    fl_bind=bind(s0,(struct sockaddr*)&addr0, sizeof(addr0));
    if(fl_bind==0){printf("bind ok\n");}
    
    return s0;
}

void *monitor_can(void *ptr) {
	int s0, nbytes_rd;
	struct can_frame myFrameRec;
	
	s0 = *(int *)ptr;

	while(1) { 
		//printf("s0 %d \n", s0);}
        nbytes_rd = read(s0, &myFrameRec, sizeof(struct can_frame));
                        
        printf("\n nbytes_rd:%d  ",nbytes_rd );
        printf("can_id:%02X  ", myFrameRec.can_id);
        printf("can_dlc:%02X  data:  ", myFrameRec.can_dlc);
        for (int i = 0; i < myFrameRec.can_dlc; i++)
            printf("%02X ", myFrameRec.data[i]);
    }
}
