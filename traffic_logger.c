#include <stdio.h>

#include "traffic_logger.h"

FILE *fptr;
static int STDOUT = 0;

void set_verbosity(int v) {
	STDOUT = v;
}

void open_log() {
	fptr = fopen("gw.log", "w");
	
	if (fptr == NULL)
        printf("Could not open file");
}

void log_traffic(int bytes, char *s, char *d, struct can_frame frame, int filtered, int id, int mask, int is_match) {
	if (!filtered) {
		fprintf(fptr, "\nRedirected\t\t");
		if (STDOUT)
			printf("\nRedirected\t\t");
	} else {
		char sf[17];
		sprintf(sf, "%03X%c%03X", id, is_match ? ':' : '~', mask);
		fprintf(fptr, "\nBlocked by %s\t", sf);
		if (STDOUT)
			printf("\nBlocked by %s\t", sf);
	}
	
	fprintf(fptr, "%d bytes: %s->%s\t%03X\t%02X\t", bytes, s, d, frame.can_id, frame.can_dlc);
	if (STDOUT)
		printf("%d bytes: %s->%s\t%03X\t%02X\t", bytes, s, d, frame.can_id, frame.can_dlc);
	for (int i = 0; i < frame.can_dlc; i++) {
		fprintf(fptr, "%02X ", frame.data[i]);
		if (STDOUT)
			printf("%02X ", frame.data[i]);
	}
}

void close_log() {
	fclose(fptr);
}
