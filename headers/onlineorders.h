#include"header.h"
#include"stock.h"
#include "orders.h"

#ifndef onlineOrders_H
#define onlineOrders_H

class onlineOrders : public orders
{
public:
    onlineOrders();
    onlineOrders(int, char*, int, double);
    void addOrder(int&);
    void removeOrder(char[]);

    bool scheduleOrder(int, char[], int, double);

    friend int operator<<(ostream&, onlineOrders&);
};


#endif