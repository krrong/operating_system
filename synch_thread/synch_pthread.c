#include <pthread.h>
#include <stdio.h>
#define ITER 1000
#define MAX 30
void *thread_increment(void *arg);
void *thread_decrement(void *arg);
int x;

pthread_mutex_t m; //mutual exclusion variable
pthread_cond_t fill;	//condition variable
pthread_cond_t empty; //condition variable
int main(){
        pthread_t tid1, tid2;
	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&fill, NULL);
	pthread_cond_init(&empty, NULL);
        pthread_create(&tid1, NULL, thread_increment, NULL);
        pthread_create(&tid2, NULL, thread_decrement, NULL);

        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        if(x != 0)
                printf("BOOM! counter = %d\n",x);
        else
                printf("OK counter = %d\n", x);

	pthread_mutex_destroy(&m);
}

void *thread_increment(void *arg){
        int i, val;
        for(int i=0; i<ITER; i++){
		//--------------------cs-------------------------------
		pthread_mutex_lock(&m);	//mutual exclusion
		while(x == MAX){
			pthread_cond_wait(&empty, &m);
		}
		val = x;
                printf("%u : %d\n", (unsigned int)pthread_self(), val);
                x = val + 1;
		pthread_cond_signal(&fill);
		pthread_mutex_unlock(&m); //mutual exclusion
		//-----------------------------------------------------
        }
        return NULL;
}

void *thread_decrement(void *arg){
        int i, val;
        for(i=0; i<ITER; i++){
		//-------------------cs-------------------------------
		pthread_mutex_lock(&m);	//mutual exclusion
		while(x == 0){
			pthread_cond_wait(&fill, &m);
		}
		val = x;
                printf("%u : %d\n", (unsigned int)pthread_self(), val);
                x = val - 1;
		pthread_cond_signal(&empty);
		pthread_mutex_unlock(&m); //mutual exclusion
		//----------------------------------------------------
        }
        return NULL;
}

