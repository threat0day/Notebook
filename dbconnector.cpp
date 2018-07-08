#include "dbconnector.h"
//constructor 
DBConnector::DBConnector(ConnectionString connectionString)
{
    this->_connectionString = connectionString;
}
/*
    This method return MYSQL connection if succses connect to database
*/
MYSQL DBConnector::GetConnection()
{
    //mysql connection 
    MYSQL mysql;
    //initilization
    mysql_init(&mysql);

    //try connect to database
    if (!mysql_real_connect(&mysql, this->_connectionString.host.c_str(), this->_connectionString.user.c_str(), this->_connectionString.password.c_str(), this->_connectionString.dataBase.c_str(), 0, NULL, 0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
                mysql_error(&mysql));
    }
    //set encoding 
    mysql_set_character_set(&mysql, "utf8");
    mysql_character_set_name(&mysql);

    return mysql;
}
