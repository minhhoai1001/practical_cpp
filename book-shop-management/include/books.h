#pragma once

#include <iostream>
#include "books_management.h"

class books
{
    int id;            // Primary Key
    std::string name;
    std::string auth;
    int price;
	int qty;
public:
    void add(std::unique_ptr<pqxx::connection> &Postgres);
    void update_price(std::unique_ptr<pqxx::connection> &Postgres);
    void search(std::unique_ptr<pqxx::connection> &Postgres);
    void update(std::unique_ptr<pqxx::connection> &Postgres);
    void display(std::unique_ptr<pqxx::connection> &Postgres);
};