#include "members.h"

void members::add_member(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::cout << "Enter the name of the member : ";
	std::cin >> name;
	std::cout << "Enter phone no. : ";
	std::cin >> phn;
	std::cout << "Enter address (in 3 lines)" << std::endl;
	std::cin >> addr_line1;
	std::cin >> addr_line2;
	std::cin >> addr_city;
	std::cout << "Enter the name of the state : " ;
	std::cin >> addr_state;

	std::stringstream sql;
	sql << "INSERT INTO members(name, addr_line1, addr_line2, addr_city, addr_state, phn, beg_date, end_date) \
        VALUES ('" << name << "','" << addr_line1 << "','" << addr_line2 << "','" << addr_city << "','" << addr_state << "'," \
        << phn << ", CURRENT_DATE, CURRENT_DATE + interval '1 year'" <<");";
    
    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();
	// std::cout<< sql.str() <<std::endl;
}

void members::refresh(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::stringstream sql;
    sql << "UPDATE members SET valid = 'invalid' WHERE end_date <= CURRENT_DATE;";
    
    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();
}

void members::search_member(std::unique_ptr<pqxx::connection> &Postgres)
{
    std::cout << "Enter member id : ";
	std::cin >> id;
	std::stringstream sql;
	sql << "SELECT * FROM members WHERE id  = " << id << ";";
    
    pqxx::nontransaction N(*Postgres);
    pqxx::result r( N.exec(sql));
    N.commit();
	if (r.size() != 0)
	{
		std::cout << "Member Details" << std::endl ;
		std::cout << "Name : " << r[0][1].c_str() << std::endl;
		std::cout << "Address : " << r[0][2].c_str() << " " << r[0][3].c_str() << " " << r[0][4].c_str() << std::endl;
		std::cout << "State : " << r[0][5].c_str() << std::endl;
		std::cout << "Contact no. : " << r[0][6] << std::endl;
		std::cout << "Membership begin date : " << r[0][7].c_str() << std::endl;
		std::cout << "Membership end date  : " << r[0][8].c_str() << std::endl;
		std::cout << "Membership Status : " << r[0][9].c_str() << std::endl;
	}
	else
	{
		std::cout << "No Member Found!!" << std::endl;
	}
}