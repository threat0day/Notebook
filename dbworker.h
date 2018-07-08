#include "dbconnector.h"
#include "entity.h"

using namespace std;

/*
  interface which allow encapsulate work with database provaider 
*/
class IDBWorker
{
public:
  IDBWorker() {}
  virtual void AddUser(User *user) = 0;
  virtual void AddUserHobby(int userId, int hobbyId) = 0;
  virtual void AddHobby(string name) = 0;
  virtual User *GetUser(string param) = 0;
  virtual User *GetUserBySurname(string surname) = 0;
  virtual void InitData()=0;
};

/*
  implement interface IDBWorker
*/
class DBWorkerMySQL : public IDBWorker
{
public:
  virtual void AddUser(User *user);
  virtual void AddUserHobby(int userId, int hobbyId);
  virtual void AddHobby(string name);
  virtual User *GetUser(string param);
  virtual User *GetUserBySurname(string surname);
  virtual void InitData();
  DBWorkerMySQL();
  ~DBWorkerMySQL();

private:
  ConnectionString _connectionString;
  MYSQL _connection;
  Hobby *GetUserHobby(int id);
  void CreateTable();
};
