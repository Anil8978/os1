#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#ifndef MIN
#define MIN(_x,_y) ((_x) < (_y)) ? (_x) : (_y)
#endif

volatile int load_train_returned = 0;

volatile int threads_completed = 0;
struct station {
  int waiting_passengers; // in station waiting passengers
  int seated_passengers; // in train passengers 
  pthread_mutex_t lock;
  pthread_cond_t train_arrived;
  pthread_cond_t passengers_seated;
  pthread_cond_t train_full;
};

struct load_train_args {
	struct station *station;
	int free_seats;
};

void station_init(struct station *station);
void station_load_train(struct station *station, int count);
void station_wait_for_train(struct station *station);
void station_on_board(struct station *station);

/**
  Initializes all the mutexes and condition-variables.
*/
void station_init(struct station *station)
{
  station->waiting_passengers = 0;
  station->seated_passengers = 0;
  pthread_mutex_init(&(station->lock), NULL);
  pthread_cond_init(&(station->train_arrived), NULL);
  pthread_cond_init(&(station->passengers_seated), NULL);
  pthread_cond_init(&(station->train_full), NULL);
}

