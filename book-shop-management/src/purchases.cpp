#include "purchases.h"
#include <ctime>
#include <iomanip>
#include <sstream>


void purchases::new_ord(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::cout << "Enter the book Id : ";
    std::cin >> book_id;
    std::cout << "Enter Supplier Id : ";
    std::cin >> sup_id;
    std::cout << "Enter the Quantity : ";
    std::cin >> qty;
    std::cout << "Estimated expected Delivery (in days) : ";
    std::cin >> eta;

    std::stringstream sql;
    sql << "INSERT INTO purchases (book_id, sup_id, qty, dt_ordered, eta) VALUES ( \
        " << book_id << "," << sup_id << "," << qty << ", CURRENT_DATE," << eta << ");";
    
    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();
}

void purchases::mark_reciv(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::cout << "Enter the order id for order received : ";
    std::cin >> ord_id;
    std::stringstream sql;
    sql << "UPDATE purchases SET received = 'T' WHERE ord_id = " << ord_id << ";";

    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();
    std::cout << "received Marked successfully";
}

void purchases::mar_cancel(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::cout << "Enter the order id for order cancelled : ";
    std::cin >> ord_id;
    std::stringstream sql;
    sql << "UPDATE purchases SET received = 'C' WHERE ord_id = " << ord_id << ";";

    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();
    std::cout << "Cancelled Marked successfully";
}

void purchases::view(std::unique_ptr<pqxx::connection> &Postgres)
{
    int c;

    std::cout << "Select an Option" << std::endl;
    std::cout << "1. View orders not Received" << std::endl;
    std::cout << "2. View orders Cancelled" << std::endl;
    std::cout << "3. View orders Received" << std::endl;
    std::cout << "Enter Your choice : ";
    std::cin >> c;
    if (c == 1)
        received = 'F';
    else if (c == 2)
        received = 'C';
    else if (c == 3)
        received = 'T';
    else
        return;

    std::stringstream sql;
    sql << "SELECT * FROM purchases WHERE received = '" << received << "';";
    pqxx::nontransaction N(*Postgres);
    pqxx::result r( N.exec(sql));
    N.commit();

    if (c == 1)
        std::cout << std::endl << "Orders not received are" << std::endl;
    else if (c == 2)
        std::cout << std::endl << "Orders Cancelled are" << std::endl;
    else if (c == 3)
        std::cout << std::endl << "Orders received are" << std::endl;

    for (pqxx::result::const_iterator purchase = r.begin(); purchase != r.end(); ++purchase) 
    {
        std::cout << "------------------------------------ \n";
        std::cout << "Order Id : " << purchase[0].as<int>() << std::endl;
        std::cout << "Book Id : " << purchase[1].as<int>() << std::endl;
        std::cout << "Supplier Id :" << purchase[2].as<int>() << std::endl ;
        std::cout << "Quantity : " << purchase[3].as<int>() << std::endl;

        std::string order_date = purchase[4].as<std::string>();
        std::cout << "Date Ordered : " << order_date << std::endl;
        
        struct tm date_time = {};
        std::istringstream ss(order_date);
        ss >> std::get_time( &date_time, "%Y-%m-%d");
        date_time.tm_mday = date_time.tm_mday + purchase[5].as<int>();
        time_t t = mktime(&date_time);
        char buf[16];
        std::strftime(buf,16,"%Y-%m-%d",&date_time);

        std::cout << "Estimated Delivery date : " << buf<< std::endl;
    }
    std::cout <<std::endl;
}