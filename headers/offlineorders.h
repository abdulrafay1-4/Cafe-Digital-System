#include"header.h"
#include"stock.h"
#include"orders.h"

#ifndef offlineOrders_H
#define offlineOrders_H

class offlineOrders : public orders
{
public:
    offlineOrders();
    offlineOrders(int, char*, int, double);
    
    void addOrder(int&);
    void storeOrder(int, char[], int, double);
    void removeOrder(char []);

    friend int operator<<(ostream &, offlineOrders &);
};

#endif