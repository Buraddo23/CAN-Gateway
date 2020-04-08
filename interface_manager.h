#ifndef INTERFACE_MANAGER_H
#define INTERFACE_MANAGER_H

void vcan_init();
void vcan_create(char *name);
void can_config(char *name, char *bitrate);
void canfd_config(char *name, char *bitrate, char *dbitrate);

#endif //INTERFACE_MANAGER_H
