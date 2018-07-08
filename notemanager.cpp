#include "notemanager.h"
#include <iostream>
//constructor 
NoteManager::NoteManager()
{
    this->_worker = new DBWorkerMySQL();
}
//destructor 
NoteManager::~NoteManager()
{
    //   if (this->_worker)
    //       delete this->_worker;
}

/*
   This method is a wrapper over a method DBWorkerMySQL::AddHobby, which add entity 'hobby' to database
*/
void NoteManager::AddHobby(string name)
{
    this->_worker->AddHobby(name);
}
/*
   This method is a wrapper over a method DBWorkerMySQL::AddUser, which add entity 'user' to database
*/
bool NoteManager::AddUser(User *user)
{
    this->_worker->AddUser(user);
    return true;
}
/*
   This method is a wrapper over a method DBWorkerMySQL::AddUserHobby, which add entity 'user_hobby' to database
*/
bool NoteManager::AddUserHobby(int userId, int hobbyId)
{
    this->_worker->AddUserHobby(userId, hobbyId);
    return true;
}
/*
   This method is a wrapper over a method DBWorkerMySQL::GetUser, which return pointer to array User.
   input: 'all' or digit from 1 to 10
   return:*User
*/
User *NoteManager::GetUser(string param)
{
    return this->_worker->GetUser(param);
}
/*
   This method is a wrapper over a method DBWorkerMySQL::GetUserBySurname, which return  User
   input: surname user
   return:*User
*/
User *NoteManager::GetUserBySurname(string surname)
{
    return this->_worker->GetUserBySurname(surname);
}
/*
   This method is a wrapper over a method DBWorkerMySQL::InitData, which create and fill data table
*/
void NoteManager::InitData()
{
    this->_worker->InitData();
}