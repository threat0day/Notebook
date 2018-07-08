#include "dbworker.h"
#include "util.h"
#include <cstring>
#include <array>
using namespace std;

//constructor
DBWorkerMySQL::DBWorkerMySQL()
{
    //initilianization _connection string, port default 3306
    this->_connectionString.dataBase = "notebook";
    this->_connectionString.host = "192.168.0.2";
    this->_connectionString.password = "1234";
    this->_connectionString.user = "mihail";

    DBConnector *connector = new DBConnector(_connectionString);
    //get connection
    this->_connection = connector->GetConnection();
}
//insert hobby to database
void DBWorkerMySQL::AddHobby(string name)
{
    string query = "INSERT into hobby(name) values('" + name + "')";
    mysql_query(&_connection, query.c_str());
}
//Create table from database
void DBWorkerMySQL::CreateTable()
{
    string query = "SET NAMES 'utf8';"
                   "USE notebook;"
                   "DROP TABLE IF EXISTS user_hobby;"
                   "DROP TABLE IF EXISTS user,hobby;";
    mysql_query(&_connection, query.c_str());
    query = "CREATE TABLE notebook.hobby ("
            "id int(11) NOT NULL AUTO_INCREMENT,"
            "name varchar(255) DEFAULT NULL,"
            "PRIMARY KEY (id))";
    mysql_query(&_connection, query.c_str());
    query = "CREATE TABLE notebook.user ("
            "id int(11) NOT NULL AUTO_INCREMENT,"
            "name varchar(45) NOT NULL,"
            "surname varchar(45) NOT NULL,"
            "birthday date NOT NULL,"
            "adress varchar(300) NOT NULL,"
            "tel varchar(45) DEFAULT NULL,"
            "email varchar(45) DEFAULT NULL,"
            "description varchar(255) DEFAULT NULL,"
            "PRIMARY KEY (id)"
            ")";
    mysql_query(&_connection, query.c_str());
    query = "CREATE TABLE notebook.user_hobby ("
            "id int(11) AUTO_INCREMENT,"
            "id_user int(11) NOT NULL,"
            "id_hobby int(11) NOT NULL,"
            "PRIMARY KEY (id),"
            "FOREIGN KEY (id_user) REFERENCES user (id),"
            "FOREIGN KEY (id_hobby) REFERENCES hobby (id)"
            ") ENGINE = INNODB CHARACTER SET = UTF8;";
    mysql_query(&_connection, query.c_str());
}
//fill data from table
void DBWorkerMySQL::InitData()
{
    this->CreateTable();
    array<string, 10> hobby = {"плавание",
                               "футбол",
                               "программирование",
                               "самбо",
                               "вышивание крестиком",
                               "лепка",
                               "велосипед",
                               "кино",
                               "путешествия",
                               "театр"};

    for (auto x : hobby)
        this->AddHobby(x);

    array<User *, 10> users =
        {
            (new User("Иван", "Алексеев", "6,2,1993", "Новосибирск, Ленина 15", "89089561957", "ivan@mail.ru", "-")),
            (new User("Ольга", "Труев", "7,2,1993", "Кемерово, Кирова 57", "89089561957", "ivan@mail.ru", "-")),
            (new User("Алексей", "Колышев", "8,2,1993", "Москва, Ленина 55", "89089561957", "ivan@mail.ru", "-")),
            (new User("Петр", "Девятов", "6,2,1994", "Кемерово, Кирова 56", "89089561957", "ivan@mail.ru", "-")),
            (new User("Кирил", "Летов", "6,2,1995", "Москва, Ленина 59", "89089561957", "ivan@mail.ru", "-")),
            (new User("Федр", "Антонов", "6,2,1996", "Кемерово, Кирова 50", "89089561957", "ivan@mail.ru", "-")),
            (new User("Ксеноморф", "Чужой", "6,3,1993", "Новосибирск, Ленина 51", "89089561957", "ivan@mail.ru", "-")),
            (new User("Ксения", "Алексеева", "6,4,1993", "Кемерово, Кирова 5", "89089561957", "ivan@mail.ru", "-")),
            (new User("Гильвентоний", "Водородов", "6,5,1993", "Новосибирск, Ленина 5", "89089561957", "ivan@mail.ru", "-")),
            (new User("Марс", "Киров", "6,6,1993", "Москва, Кирова 53", "89089561957", "ivan@mail.ru", "-")),
        };
    for (auto x : users)
        this->AddUser(x);

    for (int i(1); i <= 10; i++)
        this->AddUserHobby(i, i);
}
//This method input user to database
 void DBWorkerMySQL::AddUser(User *user)
{
    string query = "INSERT INTO user(name , surname , birthday , adress , tel , email , description) "
                   "VALUES ('" +
                   user->name + "' , '" + user->surname + "', STR_TO_DATE('" + user->birthday + "', '%d,%m,%Y'), "
                                                                                                "'" +
                   user->adress + "', '" + user->tel + "', '" + user->email + "', '" + user->description + "')";
    try
    {
        mysql_query(&_connection, query.c_str());
    }
    catch (std::exception ex)
    {
        WriteLog(string("%s", ex.what()));
    }
}
//This method input user hobby to database
void DBWorkerMySQL::AddUserHobby(int userId, int hobbyId)
{
    string query = "INSERT into user_hobby(id_user,id_hobby) values(" + to_string(userId) + "," + to_string(hobbyId) + ")";
    mysql_query(&_connection, query.c_str());
}
/*
   This method return pointer to array User.
   input: 'all' or digit from 1 to 10
   return:*User
*/
User *DBWorkerMySQL::GetUser(string param)
{
    //store result of query
    MYSQL_RES *res;
    //store one row data result
    MYSQL_ROW row;
    std::string query;
    //get result
    res = mysql_store_result(&_connection);

    //check input param
    if (param.compare("all") == 0)
        query = "SELECT * from user";
    else if (is_number(param))
        if (atoi(param.c_str()) > 10)
        {
            printf("id must be < 10\n");
            return NULL;
        }
        else
            query = "SELECT * from user u where u.id=" + param;
    else
    {
        printf("wrong id");
        return NULL;
    }
    //exec query
    mysql_query(&_connection, query.c_str());
    res = mysql_store_result(&_connection);

    // get the number of the rows
    int userCount = res->row_count;
    //array users
    User *users = new User[userCount];
    int i = 0;
    while ((row = mysql_fetch_row(res)))
    {
        users[i] = *(new User());
        users[i].id = stoi(row[0]);
        users[i].name = row[1];
        users[i].surname = row[2];
        users[i].birthday = row[3];
        users[i].adress = row[4];
        users[i].tel = row[5];
        users[i].email = row[6];
        users[i].description = row[7];
        users[i].hobby = this->GetUserHobby(users[i].id);
        i++;
    }
    //init size array
    users[0].SIZE_ARRAY = userCount;
    if (userCount == 0)
        WriteLog(string("id not found from database"));
    //free result
    mysql_free_result(res);
    return users;
}

/*
   This method return  User by surname
   input: surname user
   return:*User
*/
User *DBWorkerMySQL::GetUserBySurname(string surname)
{
    //store result of query
    MYSQL_RES *res;
    //store one row data result
    MYSQL_ROW row;

    std::string query = "SELECT * from user u where u.surname='" + surname + "'";
    //get result 
    res = mysql_store_result(&_connection);

    mysql_query(&_connection, query.c_str());
    res = mysql_store_result(&_connection);

    // get the number of the rows
    int userCount = res->row_count;
    User *users = new User[userCount];
    int i = 0;
    while ((row = mysql_fetch_row(res)))
    {
        users[i] = *(new User());
        users[i].id = stoi(row[0]);
        users[i].name = row[1];
        users[i].surname = row[2];
        users[i].birthday = row[3];
        users[i].adress = row[4];
        users[i].tel = row[5];
        users[i].email = row[6];
        users[i].description = row[7];
        users[i].hobby = this->GetUserHobby(users[i].id);
        i++;
    }
    users[0].SIZE_ARRAY = userCount;
    mysql_free_result(res);
    if (userCount == 0)
    {
        WriteLog(string("user not found"));
        return NULL;
    }

    return users;
}
/*
   This method return hobby user
   input: id user
   return:*Hobby
*/
Hobby *DBWorkerMySQL::GetUserHobby(int id)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    std::string query = "SELECT h.id, h.name FROM user_hobby uh LEFT JOIN user u ON u.id=uh.id_user LEFT JOIN hobby h ON h.id=uh.id_hobby WHERE u.id=" + to_string(id);
    res = mysql_store_result(&_connection);

    mysql_query(&_connection, query.c_str());
    res = mysql_store_result(&_connection);

    // get the number of the rows
    int hobbyCount = res->row_count;
    Hobby *hobbies = new Hobby[hobbyCount];
    int i = 0;
    while ((row = mysql_fetch_row(res)))
    {
        hobbies[i] = *(new Hobby());
        hobbies[i].id = stoi(row[0]);
        hobbies[i].name = row[1];
        i++;
    }
    hobbies[0].SIZE_ARRAY = hobbyCount;

    mysql_free_result(res);
    return hobbies;
}

//destructor
DBWorkerMySQL::~DBWorkerMySQL()
{
    delete &_connection;
}
