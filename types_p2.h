#ifndef __TYPES_P2_H
#define __TYPES_P2_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <assert.h>

#define EMPTY        0
#define WOMENPRESENT 1
#define MENPRESENT   2
using namespace std;

class Person
{

	int gender; // 0: male 1: female
	std::string str_gender;
	struct timeval t_create;
	struct timeval t_start;
	struct timeval t_end;
	long time_to_stay_ms;


	unsigned long order;
	unsigned long use_order;

public:
	Person();

	void set_gender(int data);
	int get_gender(void);

	void set_order(unsigned long data);
	unsigned long get_order(void);

	void set_use_order(unsigned long data);
	unsigned long get_use_order(void);

	void set_time(long data);
	unsigned long get_time(void);
	int ready_to_leave(void);

	void start(void);
	void complete(void);
	
	
	
};


// Class for the restroom
// You may need to add more class member variables and functions
class Restroom {
	int status;
	int num;
	int numOfMen;
	int numOfWomen;
	int total;
	int change_status;


	// You need to define the data structure to
    // save the information of people using the restroom
	// You can probebly use Standard Template Library (STL) vector


public:
	Restroom(){
		status = EMPTY;
		numOfMen = 0;
		numOfWomen = 0;
		total = 0;
		change_status = 0;
	}
	
	vector<Person> waiting_list;
	vector<Person> inside_list;
	
	void set_input(int num);
  int get_input(void);

 
  
	// You need to use this function to print the Restroom's status
	void print_status(void);
	void setStatus(int data); //setting status
	int getStatus(void); // getting status

	


	// Call by reference
	// This is just an example. You can implement any function you need
	void add_person(Person& p);
	void remove_person(int i);
	void statusChange(Person& p); // changing status
	

	
	//print functions
	void woman_wants_to_enter(Person& p);
	void man_wants_to_enter(Person& p);
	void woman_leaves(Person& p);
	void man_leaves(Person& p);




};










#endif
