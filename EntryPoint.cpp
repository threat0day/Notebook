#include <stdlib.h>
#include <clocale>
#include "userinterface.h"

//Entry point to application
int main(int argc, char **argv)
{
    //Set russian locale to display Cyrillic alphabet 
    setlocale(LC_CTYPE, "rus");

    
    auto noteManager = new NoteManager();
    //Create and fill table data
    noteManager->InitData();
    delete noteManager;

    auto ui = new UserInterface();
    //Show user interface menu
    ui->PrintMenu();

    return 0;
}
