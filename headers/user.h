#include"header.h"
#include"login.h"
#include"stock.h"
#include"onlineorders.h"
#include"notifcation.h"
#include"absuser.h"

#ifndef user_H
#define user_H

class user : public absuser{
private:
    login L;
    onlineOrders *O;
    notification *N;
    stock *stck;    

    int userID;
    string Role;
    string userName;
    string password;
public:
    user(string = "",int = 0, string = "", string = "", stock * = NULL, onlineOrders * = NULL, notification * = NULL);
    
    void randomDecrease();
    bool authenticateUser();

    // Stock Functions
    void displayStock() const;
    void sortSearch();
    bool searchItem(const char*);

    // Orders Functions
    bool orderFood();
    int seeOrders();
    void deliverOrder(int);

    // Employee Functions
    void calculateTotal(int);
    void seeItemSales();

    //Admin Functions
    void addResponse(int, string);
    bool addItem(const char*, int, double);
    bool removeItem(const char*);
    bool addRole(string, int, string, string);
    bool removeRole(string, int);
    void updateStock(int, int);
    void updateRole(string, int);
    void displayUsers(string);

    void seePoints();

    // Online Orders Functions
    int seeOnlineOrders();
    void giveOnlineOrder();
    void giveOnlineOrder(int&);

    // Complaints Functions
    int seeComplaints();
    void removeComplaint(int);
    void updateComplaintStatus(int, string);
    void giveComplaint(int, string);

    // Notification Functions
    void seeNotifications();
    void addNotification(int, string);
    bool checkLowStock();
    
    //Setters
    void setUserRole(string);
    void setUserName(string);
    void setPassword(string);
    void setUserID(int);

    //Getters
    string getUserRole() const;
    string getUserName() const;
    string getPassword() const;
    int getUserID() const;

};    

#endif