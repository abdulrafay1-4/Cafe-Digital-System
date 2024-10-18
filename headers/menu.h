#include"header.h"

class menu  {
public:

void getCredentials(int &, string &, string &);
void setRole(string &);
void setRoleC(string &, char &);
void setChoice(int &);
void getupdateChoice(int &);

void takeOrder(char [], int &);

void setItemDetails(string &, int &, double &);
void getComplaintDetails(int &, string &);

void getNotificationDetails(int&, string&);

void displayMenu();

void displayAdminMenu();
void displayEmployeeMenu();
void displayCustomerMenu();

};