#include"header.h"
#include"user.h"
#include"complaints.h"
#include"offlineorders.h"

class customer : public user
{
private:
    int customerID;
    static int points;

    offlineOrders *O;
    complaints *comp;
public:
    customer(int = 0, string = "", string = "", complaints* = NULL, offlineOrders* = NULL);

    bool orderFood();
    void giveOnlineOrder();
    void giveComplaint(int, string);
    void seeNotifications();
    
    void storePoints();
    void readPoints();

    //Adds a complaint of customer to the complaints list
    void operator+(const complaints &);

    void seePoints();

    int getPoints() const;
    int getCustomerID() const;
    ~customer();
};