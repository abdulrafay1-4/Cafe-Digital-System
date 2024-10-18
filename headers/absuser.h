#include"header.h"
#include"login.h"
#include"stock.h"
#include"onlineorders.h"
#include"notifcation.h"

#ifndef absuser_H
#define absuser_H

class absuser {
public:
    absuser() {}

    virtual void randomDecrease() = 0;
    virtual bool authenticateUser() = 0;

    // Stock Functions
    virtual void displayStock() const = 0;
    virtual void sortSearch() = 0;
    virtual bool searchItem(const char*) = 0;

    // Orders Functions
    virtual bool orderFood() = 0;
    virtual int seeOrders() = 0;
    virtual void deliverOrder(int) = 0;

    // Employee Functions
    virtual void calculateTotal(int) = 0;
    virtual void seeItemSales() = 0;

    //Admin Functions
    virtual void addResponse(int, string) = 0;
    virtual bool addItem(const char*, int, double) = 0;
    virtual bool removeItem(const char*) = 0;
    virtual bool addRole(string, int, string, string) = 0;
    virtual bool removeRole(string, int) = 0;
    virtual void updateStock(int, int) = 0;
    virtual void updateRole(string, int) = 0;
    virtual void displayUsers(string) = 0;

    virtual void seePoints() = 0;

    // Online Orders Functions
    virtual int seeOnlineOrders() = 0;
    virtual void giveOnlineOrder(int&) = 0;
    virtual void giveOnlineOrder() = 0;

    // Complaints Functions
    virtual int seeComplaints() = 0;
    virtual void removeComplaint(int) = 0;
    virtual void updateComplaintStatus(int, string) = 0;
    virtual void giveComplaint(int, string) = 0;

    // Notification Functions
    virtual void seeNotifications() = 0;
    virtual void addNotification(int, string) = 0;
    virtual bool checkLowStock() = 0;
};    

#endif