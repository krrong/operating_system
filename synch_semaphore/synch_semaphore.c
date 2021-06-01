#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#define ITER 1000
void *thread_increment(void *arg);
void *thread_decrement(void *arg);
int x;
sem_t s;
sem_t fill;
sem_t empty;
int main(){
        pthread_t tid1, tid2;
	sem_init(&s, 0, 1);
        sem_init(&fill, 0, 0);
	sem_init(&empty, 0, 30);
	pthread_create(&tid1, NULL, thread_increment, NULL);
        pthread_create(&tid2, NULL, thread_decrement, NULL);

        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        if(x != 0)
                printf("BOOM! counter = %d\n",x);
        else
                printf("OK counter = %d\n", x);
}

void *thread_increment(void *arg){
        int i, val;
        for(int i=0; i<ITER; i++){
		//---------------------------cs------------------------
		sem_wait(&empty);
		sem_wait(&s);
                val = x;
                printf("%u : %d\n", (unsigned int)pthread_self(), val);
                x = val + 1;
		sem_post(&s);
		sem_post(&fill);
		//-----------------------------------------------------
        }
        return NULL;
}

void *thread_decrement(void *arg){
        int i, val;
        for(i=0; i<ITER; i++){
		//---------------------------cs------------------------
		sem_wait(&fill);
		sem_wait(&s);
                val = x;
                printf("%u : %d\n", (unsigned int)pthread_self(), val);
                x = val - 1;
		sem_post(&s);
		sem_post(&empty);
		//-----------------------------------------------------
        }
        return NULL;
}

