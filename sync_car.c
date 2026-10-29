#include "sync_car.h"

void station_init(struct station *station)
{
	pthread_mutex_init(&station->lock, NULL);
	pthread_cond_init(&station->car_arrived, NULL);
	station->free_seats = 0;
	station->waiting = 0;
	station->boarding = 0;
}

void station_wait_for_car(struct station *station)
{
	pthread_mutex_lock(&station->lock);
	station->waiting++;
	while (station->free_seats == 0)
		pthread_cond_wait(&station->car_arrived, &station->lock);
	station->free_seats--;
	station->waiting--;
	station->boarding++;
	pthread_mutex_unlock(&station->lock);
}
