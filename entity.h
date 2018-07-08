#include <stdlib.h>
#include <string>
using namespace std;
struct Hobby;
struct User
{
    int id;
    string name;
    string surname;
    string birthday;
    string adress;
    string tel;
    string email;
    string description;
    Hobby *hobby;
    int SIZE_ARRAY = 0;
    User(string name, string surname, string birthday, string adress, string tel, string email, string description)
    {
        this->id = 0;
        this->name = name;
        this->surname = surname;
        this->birthday = birthday;
        this->adress = adress;
        this->tel = tel;
        this->email = email;
        this->description = description;
    }
    User()
    {
    }
};
struct Hobby
{
    int id;
    string name;
    int SIZE_ARRAY = 0;
    Hobby(string name)
    {
        this->id = 0;
        this->name = name;
    }
    Hobby() {}
};
