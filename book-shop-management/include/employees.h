#pragma once

#include <iostream>
#include "books_management.h"

class employees
{
	int id;				//Primary Key
	std::string name;
	std::string addr_line1;
	std::string addr_line2;
	std::string addr_city;
	std::string addr_state;
	long int phn;
	date date_of_joining;
	long int salary;
	std::string mgr_status;	//check(T or F) def f
public:
	void add_emp();
	void search_emp();
	void assign_mgr_stat();
	void display();
	void update_sal();
};