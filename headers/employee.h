#include"header.h"
#include"user.h"
#include"offlineorders.h"

class employee : public user
{
private:
    int employeeID;
    static int sales;

    offlineOrders *order;

public:
    employee(int = 0, string = "", string = "", offlineOrders* = NULL);
    ~employee();

    bool orderFood();
    int seeOrders();
    void deliverOrder(int);

    void seeItemSales();

    int getSales() const;
    void storeSales();
    void seeSales();
};