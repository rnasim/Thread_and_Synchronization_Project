#include "types_p2.h"
#include "utils.h"
using namespace std;

void Person::set_gender(int data) { gender = data; }
int Person::get_gender(void)      { return gender; }

void Person::set_order(unsigned long data) { order = data; }
unsigned long Person::get_order(void)      { return order; }

void Person::set_use_order(unsigned long data) { use_order = data; }
unsigned long Person::get_use_order(void)      { return use_order; }

void Person::set_time(long data) { time_to_stay_ms = data; }
unsigned long Person::get_time(void) { return time_to_stay_ms;}

int Person::ready_to_leave(void) {
	struct timeval t_curr;
	gettimeofday(&t_curr, NULL);

	if (get_elasped_time(t_start, t_curr) >= time_to_stay_ms) { return 1; }
	else { return 0; }
}

void Person::start(void) {
	gettimeofday(&t_start, NULL);
	printf("(%lu)th person enters the restroom: \n", order);
	printf(" - (%lu) milliseconds after the creation\n", get_elasped_time(t_create, t_start));
}

void Person::complete(void) {
	gettimeofday(&t_end, NULL);
	printf("(%lu)th person comes out of the restroom: \n", order);
	printf(" - (%lu) milliseconds after the creation\n", get_elasped_time(t_create, t_end));
	printf(" - (%lu) milliseconds after using the restroom\n", get_elasped_time(t_start, t_end));
}


Person::Person() {
	gettimeofday(&t_create, NULL);
}
void Restroom::set_input(int data) { num = data; }
int Restroom::get_input(void)      { return num; }

void Restroom::setStatus(int data) { status = data;}//setting status
int Restroom::getStatus(void) { return status;}  // getting status

// You need to use this function to print the Restroom's status
void Restroom::print_status(void) {
	
	if(status == 0 || inside_list.size() == 0){
		cout << "(Empty): Total: "<< total << " (Men: "<< numOfMen << ", Women: "<< numOfWomen << ")" << endl;
	}else if(status == 1){
		cout << "(WomanPresent): Total: "<< total << " (Men: "<< numOfMen << ", Women: "<< numOfWomen << ")" << endl;
	}else{
		cout << "(MenPresent): Total: "<< total << " (Men: "<< numOfMen << ", Women: "<< numOfWomen << ")" << endl;
	}
}


// Call by reference
// This is just an example. You can implement any function you need
void Restroom::add_person(Person& p) {
	
	inside_list.push_back(p); //enter the person in the inside_list vector
  
	int length = inside_list.size()-1;
	inside_list[length].start();//call the start function to start the gettimeofday()@last index of the vector
	
	//increment to the men/women counter accordingly
	if(p.get_gender() == 0){
		numOfMen++;
		total++;
    
		//statusChange(p);
    
    
	}else{
		numOfWomen++;
		total++;
    
		//statusChange(p);
   
    
	} 
	
}

void Restroom::remove_person( int i)
{
	if(inside_list[i].get_gender() == 0){
  	
		statusChange(inside_list[i]); //change the status for the person in the list
		numOfMen--;
		total--;
    //I needed to create temp variables so I can erase the person before I call 
    //man_leaves(). If I dont do it it will get stuck at the last person when he/she leaves the Restroom
    inside_list.erase(inside_list.begin()+i);
    Person tmp = inside_list[i];
    man_leaves(tmp);
    
    /*if(inside_list[i].get_gender() == 0){
      man_leaves(inside_list[i]);
    }else{
      man_leaves(inside_list[i]);
    }
    
		inside_list.erase(inside_list.begin()+i);//remove the element at i*/
	}else{
		
		statusChange(inside_list[i]); //change the status for the person in the list
		numOfWomen--;
		total--;
    
    inside_list.erase(inside_list.begin()+i);
    Person tmp = inside_list[i];
    man_leaves(tmp);
		
	}
  if(inside_list.size() == 0)	{ 
			setStatus(0);
	}
}



void Restroom::statusChange(Person& p) // changing status
{
  int tmp = status;
  
	if(inside_list.size() == 0 ){
   status = 0;
  }else{
    if(p.get_gender() == 0){
     status = MENPRESENT; 
    }else{ 
      status = WOMENPRESENT;
    } // 1 is female 0 is male
  }

	change_status = (tmp == status) ? 0 : 1;
}

void Restroom::man_wants_to_enter(Person& p)
{
  if(status ==  EMPTY && p.get_gender() == 0)
  {
    cout << "[Queue] Send (Man) into the restroom (Stay " << p.get_time() << "ms), Status: ";
    print_status();
    add_person(waiting_list[0]);
    
    //waiting_list.erase(waiting_list.begin());
  }else if(status == MENPRESENT && p.get_gender() == 0){
    cout << "[Queue] Send (Man) into the restroom (Stay " << p.get_time() << "ms), Status:";
    print_status();
    add_person(waiting_list[0]);
    
    //waiting_list.erase(waiting_list.begin());
    
  }/*else{
    cout << "Cannot Enter : WomenPresent! \n";
  }*/
	
}

void Restroom::woman_wants_to_enter(Person& p)
{	
  if(status ==  EMPTY&& p.get_gender() == 1)
  {
    cout << "[Queue] Send (Woman) into the restroom (Stay " << p.get_time() << "ms), Status: ";
    print_status();
    add_person(waiting_list[0]);
    
  }else if(status == WOMENPRESENT&& p.get_gender() == 1){
  
    cout << "[Queue] Send (Woman) into the restroom (Stay " << p.get_time() << "ms), Status:";
    print_status();
    add_person(waiting_list[0]);
    
  }/*else{
  
    cout << "Cannot Enter : MenPresent! \n";
  }*/
  
	
}



void Restroom::woman_leaves(Person& p)
{
		
	if(change_status == 1){
		cout<< "[Restroom] (Woman) left the restroom. Status is changed, Status is ";
    print_status();
    
     
	}else{
		cout <<  "[Restroom] (Woman) left the restroom. Status is ";
   
   
    print_status();
    //cout << "Inside list size is " << inside_list.size()<< endl; 
     
	}
}

void Restroom::man_leaves(Person& p)
{   
	
  	
	if(change_status == 1){
		cout<< "[Restroom] (Man) left the restroom. Status is changed, Status is ";
    print_status();
    
     
	}else{
		cout <<  "[Restroom] (Man) left the restroom. Status is ";
    //print_status();
    
    print_status();
    //cout << "Inside list size is " << inside_list.size()<< endl;
     
	}
}


