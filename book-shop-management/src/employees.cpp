#include "employees.h"

void employees::add_employees(std::unique_ptr<pqxx::connection> &Postgres)
{
	std::cout << "Enter The details of new employees!! \n";
	std::cout << "Enter The name of the employee : ";
	std::cin >> name;
	std::cout << "Enter the Address (in 3 lines) : " << std::endl;
	std::cin >> addr_line1;
	std::cin >> addr_line2;
	std::cin >> addr_city;
	std::cout << "Enter State : ";
	std::cin >> addr_state;
	std::cout << "Enter phone no.";
	std::cin >> phn;
	std::cout << "Enter the salary : ";
	std::cin >> salary;

	std::stringstream sql;
	sql << "INSERT INTO employees (name, addr_line1, addr_line2, addr_city, addr_state, phn, date_of_joining, salary) \
        VALUES ('" <<name<<"','"<<addr_line1<<"','"<<addr_line2<<"','"<<addr_city<<"','"<<addr_state<<"',"<<phn<< ",CURRENT_DATE,"<<salary<<");";

    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();

	std::cout << "Employee Added Succesfully!" << std::endl;
}

void employees::display(std::unique_ptr<pqxx::connection> &Postgres)
{
	int i = 0;
    std::stringstream sql;
	sql << "SELECT * FROM employees;";

    pqxx::nontransaction N(*Postgres);
    pqxx::result r( N.exec(sql));
    N.commit();
	if(r.size() != 0)
    {
       for (pqxx::result::const_iterator employee = r.begin(); employee != r.end(); ++employee) 
       {
            std::cout << "------------------------------------ \n";
            std::cout << "Employees Details of Emp no." << employee[0].as<int>() << std::endl ;
            std::cout << "Name : " << employee[1].as<std::string>() <<std::endl;
            std::cout << "Address : " << employee[2].as<std::string>() \
                      << " " << employee[3].as<std::string>() << " " << employee[4].as<std::string>() << std::endl;
            std::cout << "State : " << employee[5].as<std::string>() << std::endl;
            std::cout << "Contact no. : " << employee[6].as<long int>() << std::endl;
            std::cout << "Date of Joining: " << employee[7].as<std::string>() << std::endl;
            std::cout << "Salary : " << employee[8].as<int>() << std::endl;
       }
    }
	else
	{
		std::cout << "Employees Not found!" << std::endl;
	}
}

void employees::assign_mgr_stat(std::unique_ptr<pqxx::connection> &Postgres)
{
	std::cout << "Enter Your Id for verification : ";
	std::cin >> id ;
	std::stringstream sql;
	sql << "SELECT mgr_status FROM employees WHERE id  = " << id << ";";

    pqxx::nontransaction N(*Postgres);
    pqxx::result r( N.exec(sql));
    N.commit();

	if (r.size() == 0)
	{
		std::cout << "Employee Not Found!!" << std::endl;
		return;
	}
	else
	{
		mgr_status = r[0][0].c_str();
        std::cout <<"mgr_status: "<<mgr_status<<std::endl;
		if (mgr_status == "T")
		{
			std::cout << "You Do Not have Manager Rights!!!" << std::endl ;
			return;
		}
	}
	std::cout << "Enter the employee id to grant Manager status : ";
	std::cin >> id;
	sql.str("");
	sql << "UPDATE employees SET mgr_status = 'T' WHERE id = " << id << ";";
    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();
	std::cout << "Manager Status granted \n";
}

void employees::search_employees(std::unique_ptr<pqxx::connection> &Postgres)
{
	std::cout << "Enter the id for searching an employee : ";
	std::cin >> id ;
	std::stringstream sql;
	sql << "SELECT * FROM employees WHERE id  = " << id << ";";

    pqxx::nontransaction N(*Postgres);
    pqxx::result r( N.exec(sql));
    N.commit();
	if (r.size() != 0)
	{
		std::cout << "Employees Details" << std::endl ;
		std::cout << "Name : " << r[0][1].c_str() <<std::endl;
		std::cout << "Address : " << r[0][2].c_str() << " " << r[0][3].c_str() << " " << r[0][4].c_str() << std::endl;
		std::cout << "State : " << r[0][5].c_str() << std::endl;
		std::cout << "Contact no. : " << r[0][6] << std::endl;
		std::cout << "Date of Joining: " << r[0][7].c_str() << std::endl;
		std::cout << "Salary : " << r[0][8] << std::endl;
	}
	else
	{
		std::cout << "No Employee Found!!" << std::endl;
	}
}

void employees::update_salary(std::unique_ptr<pqxx::connection> &Postgres)
{
	std::cout << "Enter the id to update the salary of an employee : ";
	std::cin >> id ;
	std::cout << "Enter the updated salary : ";
	std::cin >> salary;
	std::stringstream sql;
	sql << "UPDATE employees SET salary = " << salary << " WHERE id  = " << id << ";";
    
    pqxx::work W(*Postgres);
    W.exec(sql.str());
    W.commit();
	std::cout << "Salary update Successfully \n";
}