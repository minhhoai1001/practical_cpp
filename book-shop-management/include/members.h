#pragma once

#include <iostream>
#include "books_management.h"

class members
{
    int id;				//Primary Key
	std::string name;
	std::string addr_line1;
	std::string addr_line2;
	std::string addr_city;
	std::string addr_state;
	long int phn;
	date beg_date;
	date end_date;
	std::string valid;
public:
	void add_member(std::unique_ptr<pqxx::connection> &Postgres);
	void refresh(std::unique_ptr<pqxx::connection> &Postgres);
	void search_member(std::unique_ptr<pqxx::connection> &Postgres);
};