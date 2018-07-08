#include <stdlib.h>
#include <string>
using namespace std;
//struct which define connection string for mysql server
struct ConnectionString
{
    string host;
    int port;
    string user;
    string password;
    string dataBase;
};
