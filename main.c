#include <pthread.h>

#include "interface_manager.h"
#include "routing_rules.h"

int main(void) {
	pthread_t read_thread;
	int th_err;

	//vcan_init();
	//vcan_create("vcan0");
	//vcan_create("vcan1");
	//can_config("can0", "250000");
	//canfd_config("can0", "250000", "400000");
	
	th_err = pthread_create(&read_thread, NULL, read_can, (void *)"vcan0");
	
	//read_can("vcan0");
	//read_can("vcan1");
	//write_can("vcan0");
	
	while(1);
	
	return 0;
}

/*
int main() {
    int s0,i;

    struct sockaddr_can addr0;
    struct ifreq ifr0;
    struct can_frame myFrame;         
    char fl_bind;
    char bytes_wr;

    system("sudo ip link set vcan0 down");
    sleep(1);// sec
    system("sudo ip link set vcan0 up");
    printf("sudo ip link set vcan0 up \n");
    sleep(1); 

    s0=socket(PF_CAN, SOCK_RAW, CAN_RAW);
    //CAN0 interface set up
    strcpy(ifr0.ifr_name, "vcan0");
    ioctl(s0, SIOCGIFINDEX, &ifr0);
    addr0.can_family = AF_CAN;
    addr0.can_ifindex = ifr0.ifr_ifindex;
    fl_bind=bind(s0,(struct sockaddr*)&addr0, sizeof(addr0));
    if(fl_bind==0){printf("bind ok\n");}

    //define the CAN frame
    myFrame.can_id=0x10;
    myFrame.can_dlc=8;
    for(i=0;i<7;i++) myFrame.data[i]=0x55;        
    myFrame.data[0]=0xAA;        

        // infinite loop
    while(1) {
        bytes_wr=write(s0,&myFrame,sizeof(myFrame));
        printf("bytes_wr: %d \n", bytes_wr);
        sleep(1);
    }
}*/
