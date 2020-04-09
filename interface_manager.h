#ifndef INTERFACE_MANAGER_H
#define INTERFACE_MANAGER_H

void vcan_init();
void vcan_create(char *);
void can_config(char *, char *);
void canfd_config(char *, char *, char *);

#endif //INTERFACE_MANAGER_H
