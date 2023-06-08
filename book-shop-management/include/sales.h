#pragma once

#include <iostream>
#include "books_management.h"

class sales
{
	int invoice_id;		//Primary key
 	int member_id;		//FK ref member(id)
	int book_id;		//FK ref books(id)
	int qty;
	int amount;
	date date_s;
public:
	void add(std::unique_ptr<pqxx::connection> &Postgres);
	void find_total_sales(std::unique_ptr<pqxx::connection> &Postgres);
};