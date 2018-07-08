#include <stdlib.h>
#include <string>
#include <array>
#include "dbworker.h"
using namespace std;
class NoteManager
{
  public:
    NoteManager();
    ~NoteManager();
    bool AddUser(User *user);
    bool AddUserHobby(int userId, int hobbyId);
    void AddHobby(string name);
    User *GetUser(string param);
    User *GetUserBySurname(string surname);
    void InitData();

  private:
    IDBWorker *_worker;
};
