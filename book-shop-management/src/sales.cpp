#include "sales.h"

void sales::add(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::cout << "Enter Member id :";
	std::cin >> member_id;
	std::cout << "Enter the book id : ";
	std::cin  >> book_id;
	std::cout << "Enter the quantity : ";
	std::cin  >> qty;

	std::stringstream sql;
	sql << "SELECT price*" << qty << " FROM books WHERE id = " << book_id << ";";
    
    pqxx::nontransaction N(*Postgres);
    pqxx::result r( N.exec(sql));
    N.commit();

	if (r.size() != 0)
	{
		amount = r[0][0].as<int>();
		std::cout << "The bill amount : " << amount << std::endl;
	}
	else
	{
		std::cout << "Book Id invalid!!" << std::endl;
		return;
	}

	sql.str("");
	sql << "INSERT INTO sales(member_id, book_id, qty, amount, date_s) \
		VALUES (" << member_id << "," << book_id << "," << qty << "," << amount << ",CURRENT_DATE);";
    
	pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();
}

void sales::find_total_sales(std::unique_ptr<pqxx::connection> &Postgres)
{
	std::stringstream sql;
    sql << "SELECT sum(amount) FROM sales WHERE date_part('year', date_s) = date_part('year', CURRENT_DATE);";
    
    pqxx::nontransaction N(*Postgres);
    pqxx::result r( N.exec(sql));
    N.commit();
	if (r.size() != 0)
	{
		std::cout << "Total sales this year : " << r[0][0] << std::endl;
	}
}