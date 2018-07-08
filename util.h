#include <string>
#include <iostream>
/*
   This method checks, a string is number, return true if all char is digit, not working if digit negative
*/
bool is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}
/*
   This method write to log
*/
void WriteLog(std::string mess)
{
    std::cout << mess << std::endl;
}
