#include "books.h"

void books::add(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::cout << "Enter the name of the book : " ;
    std::cin >> name;
    std::cout << "Enter the name of the author : ";
    std::cin >> auth;
    std::cout << "Enter the Price : ";
    std::cin >> price;
    std::cout << "Enter the Qty Recived : ";
    std::cin >> qty;
    std::stringstream sql;
    sql << "INSERT INTO books(name,auth,price, qty) \
            VALUES('" << name << "','" << auth << "'," << price << "," << qty << ");";

    std::cout<<sql.str()<<std::endl;

    /* Create a transactional object. */
    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();
}

void books::update_price(std::unique_ptr<pqxx::connection> &Postgres)
{
    char choice;
    std::cout << "Enter the id of the book for update in price : ";
    std::cin >> id;
    std::stringstream sql;
    sql << "SELECT name,price FROM books WHERE id = " << id << ";";

    pqxx::nontransaction N(*Postgres);
    pqxx::result r( N.exec(sql));
    N.commit();

    if(r.size() == 1)
    {
        std::cout << "The Name of the book is : " << r[0][0].c_str() << std::endl ;
        std::cout << "The current price of the book is : " << r[0][1].c_str() << std::endl;
        std::cout << "Do you Want to Update the Price [y/n] : " ;
        std::cin >> choice;
        if (choice == 121 || choice == 89)
        {
            std::cout << "Enter the new price : ";
            std::cin >> price;

            sql << "UPDATE books SET price = " << price << " WHERE id = " << id << ";";

            pqxx::work W(*Postgres);
            W.exec(sql.str());
            W.commit();
        }
        else
        {
            std::cout << "No changes Made!!";
        }
    }
    else
    {
        std::cout << "No Book found!!!";
    }
}

void books::search(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::cout << "Enter book id for details : ";
    std::cin >> id;
    std::stringstream sql;
    sql << "SELECT * from books WHERE id = " << id << ";";
    
    pqxx::nontransaction N(*Postgres);
    pqxx::result r( N.exec(sql));
    N.commit();
    if(r.size() != 0)
    {
        std::cout << "------------------------------------ \n";
        std::cout << "The Details of Book Id " << r[0][0] << std::endl;
        std::cout << "The Name of the book is : " << r[0][1].c_str() << std::endl ;
        std::cout << "THE Author is " << r[0][2].c_str() << std::endl;
        std::cout << "The Price of the book is : " << r[0][3] << std::endl ;
        std::cout << "The inventory count is " << r[0][4] << std::endl;
    }
    else
    {
        std::cout << "No record Found" << std::endl;
    }
}

void books::update(std::unique_ptr<pqxx::connection> &Postgres)
{
    int b_id[100], qty[100], i = 0, max;
    std::stringstream sql;
    sql << "SELECT book_id,qty FROM purchases WHERE recieves = 'T' and inv IS NULL;";

    pqxx::nontransaction N(*Postgres);
    pqxx::result r( N.exec(sql));
    N.commit();

    sql << "UPDATE purchases set inv = 1 WHERE recieves = 'T' and inv IS NULL;";
    
    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();

    for (pqxx::result::const_iterator purchase = r.begin(); purchase != r.end(); ++purchase) 
    {
        b_id[i] = purchase[0].as<int>();
        qty[i] = purchase[1].as<int>();
        i++;
    }
    max = i;
    for(i = 0; i <= max; i++)
    {
        sql.str("");
        sql << "UPDATE books set qty = " << qty[i] << " WHERE id = " << b_id[i] << ";";
        W.exec(sql.str());
        W.commit();
    }
    std::cout << "The orders recieved have been updated.";
}

void books::display(std::unique_ptr<pqxx::connection> &Postgres)
{
    int i = 0;
    std::stringstream sql;
    sql << "SELECT * from books;";

    pqxx::nontransaction N(*Postgres);
    /* Execute SQL query */
    pqxx::result R( N.exec(sql));
    N.commit();
    /* List down all the records */
    for (pqxx::result::const_iterator book = R.begin(); book != R.end(); ++book) 
    {
        std::cout << "------------------------------------ \n";
        std::cout << "id = " << book[0].as<int>() << std::endl;
        std::cout << "name = " << book[1].as<std::string>() << std::endl;
        std::cout << "auth = " << book[2].as<std::string>() << std::endl;
        std::cout << "price = " << book[3].as<float>() << std::endl;
        std::cout << "Quantity = " << book[4].as<int>() << std::endl;
    }
}