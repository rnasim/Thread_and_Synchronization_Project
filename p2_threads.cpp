#include "p2_threads.h"
#include "utils.h"


extern pthread_mutex_t Mutex;
extern struct timeval t_global_start;
extern Restroom stall;

using namespace std; 
/*
void *threadfunc(void *parm)
{

	int status;
	printf(" [Thread] Start\n");

	printf(" [Thread] Locks\n");
	status = pthread_mutex_lock(&mutex);

    printf(" [Thread] Blocked\n");
    status = pthread_cond_wait(&cond, &mutex);

	printf(" [Thread] Starts again.\n");
	for (int i=0; i<3; i++) {
		printf(" [Thread] Complete thread after (%d) seconds\n", (3-i));
		usleep(MSEC(1000));
	}

	printf(" [Thread] Unlocks\n");
	status = pthread_mutex_unlock(&mutex);
	printf(" [Thread] Complete\n");
}
*/
void *create(void *parm)
{
  int total =  2*stall.get_input();
  int num_men = stall.get_input(), num_women = num_men;
  

  
  srand(time(NULL));
  struct timeval current_time;

  for(int i=0; i<total; i++)
  {
	//create a new person to push into the waiting list  
	Person p;
	
	//assign gender
  if(num_men == 0 ){
    p.set_gender(1);
  }else if(num_women == 0 ){
    p.set_gender(0);
  }else{
    p.set_gender(rand()%2);
  }
  
 	p.set_order(i+1); // set their order
  int time = (rand()%10) + 3;
  if(time > 10 ){
    int t =  time-10;
    time -= t;
  }
	p.set_time(time); //assign a random time btw 3 to 10 ms
  
	
  if(p.get_gender() == 1)
	{	// women if 1 and counter of women is not 0 and always set to women if already created all the men
		num_women--;
	}else {
		num_men--;
	}

  //lock the thread
  

	pthread_mutex_lock(&Mutex);
	
	stall.waiting_list.push_back(p);//push the person down the waiting_list vector
  
	/*if(p.get_gender() == 0){
    printf("%d person (Man) was created. \n", i);
  }else{
    printf("%d person (Woman) was created. \n", i);
  }*/

	pthread_mutex_unlock(&Mutex);
	
	//you must wait for a random time interval (between 1 ms – 5 ms) 
	//until you can send the next person to the restroom

	usleep(MSEC((rand()%5+1))); // wait 1-5 ms to send
	//p.complete();
  }
  //printf("Create thread finished \n \n \n");
  pthread_exit(0);//end thread
  
}


void *exit_Restroom(void *parm)
{
  int total =  2*stall.get_input();

  
  struct timeval current_time;
  
  while(total != 0 ){
	
	for(int i = 0; i < stall.inside_list.size(); i++){
		
		if(stall.inside_list[i].ready_to_leave()){
			pthread_mutex_lock(&Mutex);
			gettimeofday(&current_time, NULL);
			
			if(stall.inside_list[i].get_gender() == 0 ){
				//a man is ready_to_leave
				cout << "[" << get_elasped_time(t_global_start, current_time) << " ms]";
        stall.remove_person(i);//remove the person at i from the inside_list        
				//stall.man_leaves(stall.inside_list[i]);
				
        //stall.inside_list.erase(inside_list.begin()+i);//remove the element at i
        total--;
				i--;//previous person in the list
			}else{
				cout << "[" << get_elasped_time(t_global_start, current_time) << " ms]";
				//stall.woman_leaves(stall.inside_list[i]);
				stall.remove_person(i);//remove the person at i from the inside_list
				total--;
				i--;//previous person in the list
			}
      
      //cout << "Queue has "<< stall.waiting_list.size() << endl;
      //cout << "Inside restroom " << stall.inside_list.size() << endl;
			//cout<< "Total is " << total << endl;
      //cout << "Size is " << stall.inside_list.size() << endl;
      pthread_mutex_unlock(&Mutex);
		}
    
		//pthread_mutex_unlock(&Mutex);
   
	}
  
  
  }
  //printf("ExitRestroom thread finished \n \n \n");
  pthread_exit(0);//end thread
}

void *moveInside(void *parm)
{
  
  int total =  2*stall.get_input();
  int already_moved = 0;
  int count = 0;
  struct timeval current_time;
  srand(time(NULL));
  
  while(already_moved != total){
    if(stall.waiting_list.size() != 0){//if the waiting list is not empty
      
      pthread_mutex_lock(&Mutex);
      gettimeofday(&current_time, NULL);
      
      if(stall.waiting_list[0].get_gender() == 0){
        if(stall.getStatus() != WOMENPRESENT){
          cout << "["<< get_elasped_time(t_global_start, current_time)<< "ms]";
          stall.man_wants_to_enter(stall.waiting_list[0]);
          count++;
          
          cout << "["<< get_elasped_time(t_global_start, current_time)<< "ms]";
          cout << "[Restroom] (Man) goes into the restroom, State is ";
          stall.statusChange(stall.waiting_list[0]);
          stall.print_status();
          stall.waiting_list.erase(stall.waiting_list.begin()); //remove the person from the top
          already_moved++;
        }
        
                                                     
      }else{
         if(stall.getStatus() != MENPRESENT){
          cout << "["<< get_elasped_time(t_global_start, current_time)<< "ms]";
          stall.woman_wants_to_enter(stall.waiting_list[0]);
          count++;
          cout << "["<< get_elasped_time(t_global_start, current_time)<< "ms]";
			    cout << "[Restroom] (Women) goes into the restroom, State is ";
          stall.statusChange(stall.waiting_list[0]);
          stall.print_status();
          stall.waiting_list.erase(stall.waiting_list.begin()); //remove the person from the top
          already_moved++;
       }
        //cout << "Counter is " << count << endl << endl;
      }
      
      //cout << "Counter is " << count << endl << endl;
      pthread_mutex_unlock(&Mutex);
    }
  }
  
  //printf("Thread move finished \n \n \n");
  pthread_exit(0);
}