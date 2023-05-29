#pragma once

#include <iostream>
#include "books_management.h"

class suppliers
{
	int id;				//Primary Key
	std::string name;
	long int phn;
	std::string addr_line1;
	std::string addr_line2;
	std::string addr_city;
	std::string addr_state;
public:
	void add_supplier(std::unique_ptr<pqxx::connection> &Postgres);
	void remove_supplier(std::unique_ptr<pqxx::connection> &Postgres);
	void search_id(std::unique_ptr<pqxx::connection> &Postgres);
};