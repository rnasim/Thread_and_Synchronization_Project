#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include "types_p2.h"
#include "p2_threads.h"
#include "utils.h"


pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
struct timeval t_global_start;
Restroom stall;

using namespace std;
int main(int argc, char** argv)
{
	// This is to set the global start time
	gettimeofday(&t_global_start, NULL);
  int input;

	pthread_t       tid[2];//create 3 threads
	int             status = 0;
	int             work = 0;

  if(argc == 2)
  {
    input = atoi(argv[1]);
  }else{
    cout << "[ERROR] Expecting 1 argument, but got (X)." << endl;
    cout << "[USAGE] p2_exec <input>";
    return 0;
  }
	stall.set_input(input);//set the input
 
	// Example code for sleep and class usage
	/*Person p1;
	p1.set_order(1);

	usleep(MSEC(200));
	p1.start();


	usleep(MSEC(150));
	p1.complete();*/
	///////////////////////////////////////////

  //thread function create for creating the new Persons 
	if(pthread_create(&tid[0], NULL, create, NULL)) {
		fprintf(stderr, "Error creating thread\n");		
	}
 //Thread function Appoint for appoint the person to the Restroom
 	if(pthread_create(&tid[1], NULL, moveInside, NULL)) {
		fprintf(stderr, "Error creating thread\n");		
	}
 //Thread function remove to remove Person after done using Restroom
 	if(pthread_create(&tid[2], NULL, exit_Restroom, NULL)) {
		fprintf(stderr, "Error creating thread\n");		
	}
 
	/*usleep(MSEC(10));

	for (int i=0; i<5; i++) {
		printf("Wake up thread after (%d) seconds\n", (5-i));
		usleep(MSEC(1000));
	}

	printf("Wake up thread\n");
	status = pthread_cond_signal(&cond);
	
*/

	/* wait for the second thread to finish */
  for(int i=0; i<3; i++)
  {
	  if(pthread_join(tid[i], NULL)) {
		  fprintf(stderr, "Error joining thread\n");	
	  }
  }
	return 0;


}

