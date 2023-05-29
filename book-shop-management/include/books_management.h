#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <memory>

#define HOST "127.0.0.1"
#define USER "postgres"
#define PASSWORD "mypassword"
#define DATABASE "books_management"
#define PORT 5432

typedef struct
{
	int date;
	int month;
	int year;
}date;
