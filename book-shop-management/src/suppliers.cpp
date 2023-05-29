#include "suppliers.h"

void suppliers::add_supplier(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::cout << "Enter the Supplier Name : ";
    std::cin >> name;
    std::cout << "Enter Phone no. : ";
    std::cin >> phn;
    std::cout << "Enter the address (in 3 lines) : ";
    std::cin >> addr_line1;
    std::cin >> addr_line2;
    std::cin >> addr_city;
    std::cout << "Enter State : ";
    std::cin >> addr_state;

    std::stringstream sql;
    sql << "INSERT INTO suppliers(name, phn, addr_line1, addr_line2, addr_city, addr_state) \
        VALUES('" << name << "'," << phn << ",'" << addr_line1 << "','" << addr_line2 << "','" << addr_city << "','" << addr_state << "');";

    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();
}

void suppliers::remove_supplier(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::cout << "Enter the supplier id to remove the Supplier : ";
    std::cin >>  id;
    std::stringstream sql;
    sql << "DELETE FROM suppliers WHERE id = " << id << ";";
    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();
    std::cout << "Supplier Removed.";
}

void suppliers::search_id(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::cout << "Enter the supplier id to find the Supplier details : ";
    std::cin >>  id;
    std::stringstream sql;
    sql << "SELECT * FROM suppliers WHERE id = " << id << ";";
    
    pqxx::nontransaction N(*Postgres);
    pqxx::result r( N.exec(sql));
    N.commit();
    if(r.size() != 0)
    {
        std::cout << "Details of Supplier Id : " << r[0][0] << std::endl;
        std::cout << "Name : " << r[0][1] << std::endl;
        std::cout << "Phone no. : " << r[0][2] << std::endl;
        std::cout << "Address Line 1 : " << r[0][3] << std::endl;
        std::cout << "Address Line 2 : " << r[0][4] << std::endl;
        std::cout << "City : " << r[0][5] << std::endl;
        std::cout << "State : " << r[0][6] << std::endl;
    }
    else
    {
        std::cout << "No Supplier Found!!";
    }
}
