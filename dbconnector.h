#include <stdlib.h>
#include <string>
#include <mysql/mysql.h>
#include "connectionstring.h"
using namespace std;

/*
  This class need for create connection database
*/
class DBConnector
{
  public:
    DBConnector(ConnectionString connectionString);
    MYSQL GetConnection();

  private:
  //stores connection string 
    ConnectionString _connectionString;
};
