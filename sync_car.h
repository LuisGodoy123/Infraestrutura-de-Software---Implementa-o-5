#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

struct station {
	pthread_mutex_t lock;
	pthread_cond_t car_arrived;
	int free_seats;
	int waiting;
	int boarding;
};

void station_init(struct station *station);
void station_wait_for_car(struct station *station);

#endif
