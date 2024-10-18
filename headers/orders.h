#include"header.h"
#include"stock.h"

#ifndef orders_H
#define orders_H

class orders : public stock
{
protected:
    int orderID;
    char item[18];
    int quantity;
    double price;
public:
    orders();
    orders(int, char[], int, double);
    
    void storeSales(char[]);
    void displaySales() const;

    bool takeOrder(char [], int, char[]);
    virtual void removeOrder(char []);
    bool duplicateIDCheck(int, char[]);

    int getNoOfOrders(char[]);

};

#endif