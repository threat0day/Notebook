#include "notemanager.h"

/*
   This class is designed to interact with the user
*/
class UserInterface
{
  public:
    UserInterface();
    ~UserInterface();

    void PrintMenu();
    void ShowUser();
    void FindUserBySurname();
    void AddUser();

  private:
    NoteManager *_noteManager;
    void PrintUser(User *user);
};
