#include"notifcation.h"
#include"header.h"
#include"stock.h"

#ifndef lowStockNotification_H
#define lowStockNotification_H

class lowStockNotification : public notification {
private:
    char itemName[20];
    int quantity;
    double price;
    bool threshold;
    stock *stk;
public:    
    lowStockNotification(int = 0, string = "", const char* = "", int = 0, double = 0.0);
    
    bool checkThreshold(char[]);
    void displayLowStockNotification();
    void orderStock();

    ~lowStockNotification();
};    

#endif