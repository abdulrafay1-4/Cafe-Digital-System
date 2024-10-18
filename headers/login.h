#include"header.h"

#ifndef login_H
#define login_H

class login
{
private:
    int userID;
    string userName;
    string password;
public:

    //Constructors
    login(int = 0, string = "", string = "");

    //Utility Functions
    bool authenticateLogin(string, string);
    bool duplicateIDcheck(int, string);
    bool addUser(string, int, string, string);
    bool removeUser(string, int);
    void updateUser(string, int);

    void encryptPassword(string&);
    void decryptPassword(string&);

    void display();
    void seeUsers(string) const;

    ~login();
};
void readLoginFile(const char filename[], int& rows);
#endif