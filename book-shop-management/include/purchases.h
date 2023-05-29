#pragma once

#include <iostream>
#include "books_management.h"

class purchases
{
	int ord_id;			//Primary Key
	int book_id;		//FK ref (books)
	int sup_id;			//FK ref (suppliers)
	int qty;
	date dt_ordered;
	int eta;
	char received;		// Check(T or C or F) def (F)
	int inv;
public:
	void new_ord(std::unique_ptr<pqxx::connection> &Postgres);
	void view(std::unique_ptr<pqxx::connection> &Postgres);
	void mar_cancel(std::unique_ptr<pqxx::connection> &Postgres);
	void mark_reciv(std::unique_ptr<pqxx::connection> &Postgres);
};