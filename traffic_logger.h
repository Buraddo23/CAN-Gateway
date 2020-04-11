#ifndef TRAFFIC_LOGGER_H
#define TRAFFIC_LOGGER_H

#include <linux/can/raw.h>

void set_verbosity(int);
void open_log();
void log_traffic(int, char *, char *, struct can_frame, int, int, int, int);
void close_log();

#endif //TRAFFIC_LOGGER_H
