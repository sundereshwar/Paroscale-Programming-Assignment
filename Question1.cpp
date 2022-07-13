#include <iostream>
#include <pthread.h>
#include <queue>
#include <stdlib.h>

#define MAX 10
using namespace std;

// Declaring global variables
int consumerCount = 0;

// Shared queue
queue<int> Q;

// Function declaration of all required functions
void* producer1(void*);
void* producer2(void*);
void* consumer_thread(void*);

// Getting the mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t dataNotProduced =
					PTHREAD_COND_INITIALIZER;
pthread_cond_t dataNotConsumed =
					PTHREAD_COND_INITIALIZER;

void* producer1(void*)
{
	static int producerCount = 0;
	
	// Initialising the seed
	srand(time(NULL));
	
	while (1) {
		// Getting the lock on queue using mutex
		pthread_mutex_lock(&mutex1);

		if (Q.size() < MAX && producerCount < MAX)
		{
			
			// Getting the random number
			int num = rand() % 1000 + 1;
			//cout << "Producer 1: " << num << endl;


			// Pushing the number into queue
			Q.push(num);
            
			producerCount++;

			pthread_cond_broadcast(&dataNotProduced);
		}

		// If queue is full, release the lock and return
		else if (producerCount == MAX) {
			pthread_mutex_unlock(&mutex1);
			return NULL;
		}

		// If some other thread is executing, wait
		else {
			cout << ">> Producer1 is in wait.." << endl;
			pthread_cond_wait(&dataNotConsumed, &mutex1);
		}

		// Get the mutex unlocked
		pthread_mutex_unlock(&mutex1);
	}
}

void* producer2(void*)
{
	static int producerCount = 0;
	
	// Initialising the seed
	srand(time(NULL));
	
	while (1) {
		// Getting the lock on queue using mutex
		pthread_mutex_lock(&mutex1);

		if (Q.size() < MAX && producerCount < MAX)
		{
			
			// Getting the random number
			int num = rand() % 1000 + 1;
			//cout << "Producer 2: " << num << endl;

			// Pushing the number into queue
			Q.push(num);

			producerCount++;

			pthread_cond_broadcast(&dataNotProduced);
		}

		// If queue is full, release the lock and return
		else if (producerCount == MAX) {
			pthread_mutex_unlock(&mutex1);
			return NULL;
		}

		// If some other thread is executing, wait
		else {
			cout << ">> Producer2 is in wait.." << endl;
			pthread_cond_wait(&dataNotConsumed, &mutex1);
		}

		// Get the mutex unlocked
		pthread_mutex_unlock(&mutex1);
	}
}

void* consumer_thread(void*)
{

	while (1) {

		// Getting the lock on queue using mutex
		pthread_mutex_lock(&mutex1);

		// Pop only when queue has at least 1 element
		if (Q.size() > 0) {
			// Get the data from the front of queue
			int data = Q.front();

			cout << "Consumer thread consumed: " << data << endl;

			// Pop the consumed data from queue
			Q.pop();
			pthread_cond_signal(&dataNotConsumed);
		}
		else if (consumerCount == MAX)
		{
			pthread_mutex_unlock(&mutex1);
			return NULL;
		}
		// If some other thread is executing, wait
		else {
			cout << "Consumer is in wait.." << endl;
			pthread_cond_wait(&dataNotProduced, &mutex1);
		}

		// Get the mutex unlocked
		pthread_mutex_unlock(&mutex1);
	}
}

int main()
{
	// Declaring integers used to
	// identify the thread in the system
	pthread_t producerThread1, producerThread2, consumerThread;

	// Function to create a threads
	// (pthread_create() takes 4 arguments)
	int retProducer1 = pthread_create(&producerThread1,
					NULL, producer1, NULL);
	int retProducer2 = pthread_create(&producerThread2,
					NULL, producer2, NULL);
	int retConsumer = pthread_create(&consumerThread,
					NULL, *consumer_thread, NULL);

	// pthread_join suspends execution of the calling
	// thread until the target thread terminates
	if (!retProducer1)
		pthread_join(producerThread1, NULL);
	if (!retProducer2)
		pthread_join(producerThread2, NULL);
	if (!retConsumer)
		pthread_join(consumerThread, NULL);
	
	return 0;
}
