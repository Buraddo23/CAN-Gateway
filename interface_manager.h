#ifndef INTERFACE_MANAGER_H
#define INTERFACE_MANAGER_H

void vcan_init();
void vcan_create(char *name);
void can_config(char *name, int bitrate);

#endif //INTERFACE_MANAGER_H
