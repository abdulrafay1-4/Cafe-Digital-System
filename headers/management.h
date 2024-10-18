#include"header.h"
#include"user.h"
#include"stock.h"
#include"complaints.h"
#include"lowstocknotification.h"

class management : public user
{
private:
    int managerID;

    complaints *cL;
    lowStockNotification *lSN;
public:
    management(int = 0, string = "", string = "", complaints * = NULL, lowStockNotification * = NULL);

    bool addItem(const char *,int,double);
    bool removeItem(const char *);

    int seeComplaints();
    void removeComplaint(int);
    void updateComplaintStatus(int, string);
    void addResponse(int, string);

    void seeNotifications();
    void addNotification(int, string);

    bool searchItem(const char *);
    void updateStock(int, int);
    void displayStock() const;
    void sortSearch();

    bool checkLowStock();

    void seeBestSellerEmployee();
    
    //Remove complaints of customer
    void operator-(const complaints &);

    //Add user
    bool operator+(const user &);

    //see online orders
    

    ~management();
};
