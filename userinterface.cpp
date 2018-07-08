#include "userinterface.h"
#include <iostream>
#include <array>
#include <string>

using namespace std;

UserInterface::UserInterface()
{
    _noteManager = new NoteManager();
}
/*
    this method show main menu
*/
void UserInterface::PrintMenu()
{
    array<string, 4> menuItems = {"1 - select user/users\n",
                                  "2 - search by surname\n",
                                  "3 - add new user\n",
                                  "4 - exit\n"
                                  "------------------------------------\n"};
    for (auto &x : menuItems)
        cout << x;

    int selectIdItem = 0;
    cin >> selectIdItem;

    switch (selectIdItem)
    {
    case 1:
        this->ShowUser();
        break;
    case 2:
        this->FindUserBySurname();
        break;
    case 3:
        this->AddUser();
        break;
    case 4:
        break;

    default:
        break;
    }
}
/*
    this method is util, which allow print user to bash
*/
void UserInterface::PrintUser(User *user)
{
    cout << "id:" << to_string(user->id) << endl;
    cout << "name:" << user->name << endl;
    cout << "surname:" << user->surname << endl;
    cout << "birthday:" << user->birthday << endl;
    cout << "adress:" << user->adress << endl;
    cout << "tel. number:" << user->tel << endl;
    cout << "email:" << user->email << endl;
    cout << "description:" << user->description << endl;
    if (user->hobby != __null)
    {
        int SIZE_ARRAY_HOBBY = user->hobby[0].SIZE_ARRAY;
        cout << "hobby:" << endl;
        for (int j(0); j < SIZE_ARRAY_HOBBY; j++)
        {
            cout << user->hobby[j].name << ",";
        }
        cout << "\n";
    }
    else
        cout << "no hobby\n";
    cout << "-----------------\n"
         << endl;
}

/*
    this method show found user
*/
void UserInterface::ShowUser()
{
    cout << "input from 1 to 10 or all\n";
    string inputParam = "";
    cin >> inputParam;
    auto users = _noteManager->GetUser(inputParam);
    if (users != __null)
    {
        int SIZE_ARRAY_USERS = users[0].SIZE_ARRAY;
        for (int i(0); i < SIZE_ARRAY_USERS; i++)
            this->PrintUser(&users[i]);
    }
    this->PrintMenu();
}
/*
    this method show interface user, for input new user to database
*/
void UserInterface::AddUser()
{
    User *user = new User();
    cout << "input name:\n";
    cin >> user->name;
    cout << "input surname:\n";
    cin >> user->surname;
    cout << "input birthday by format "
            "%d,%m,%Y"
            ":\n";
    cin >> user->birthday;
    cout << "input adress:\n";
    cin >> user->adress;
    cout << "input tel. number:\n";
    cin >> user->tel;
    cout << "input email:\n";
    cin >> user->email;
    cout << "input description:\n";
    cin >> user->description;
    _noteManager->AddUser(user);
    this->PrintMenu();
}

/*
    this method display user, which will be found by surname user or nothing if not found
*/
void UserInterface::FindUserBySurname()
{
    cout << "input surname:";
    string inputParam = "";
    cin >> inputParam;
    auto user = _noteManager->GetUserBySurname(inputParam);
    if (user)
        this->PrintUser(user);
    this->PrintMenu();
}

//destructor 
UserInterface::~UserInterface()
{
    if (_noteManager)
        delete _noteManager;
}
