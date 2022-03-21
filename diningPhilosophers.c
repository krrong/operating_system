#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM 5
sem_t forks[NUM];


void pickup_fork(int philosopher_num){
	sem_wait(&forks[philosopher_num % NUM]);
}

void return_fork(int philosopher_num){
	sem_post(&forks[philosopher_num % NUM]);
}

void *philosopher(void *arg){
	int philosopher_num;
	philosopher_num = (int) arg;

	// pickup left fork
	pickup_fork(philosopher_num);
	printf("philosopher %d picks up the fork %d.\n", philosopher_num, philosopher_num);

	// pickup right fork
	pickup_fork(philosopher_num + 1);
	printf("philosopher %d picks up the fork %d.\n", philosopher_num, (philosopher_num + 1) % NUM);

	eating(philosopher_num);

	// putdown right fork
	return_fork(philosopher_num + 1);
	printf("philosopher %d put down the fork %d.\n", philosopher_num, (philosopher_num + 1) % NUM);

	// putdown left fork
	return_fork(philosopher_num);
	printf("philosopher %d put down the fork %d.\n", philosopher_num, philosopher_num);
	
	thinking(philosopher_num);

	return NULL;
}

void thinking(int philosopher_num){
	printf("%d is thinking\n", philosopher_num);
}

void eating(int philosopher_num){
	printf("%d is eating\n", philosopher_num);
}

int main(){
	pthread_t threads[NUM];
	
	for(int i=0; i<NUM; i++){
		sem_init(&forks[i], 0, 1);
	}

	for(int i=0; i<NUM; i++){
		pthread_create(&threads[i], NULL, philosopher, (void*)i);
	}
	
	
	for(int i=0; i<NUM; i++){
		pthread_join(threads[i], NULL);
	}


	printf("NO DEADLOCK\n");

	return 0;
}
