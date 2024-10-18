#include"customer.h"
#include"user.h"

int customer::points = 0;

customer::customer(int ID, string name, string password, complaints *C, offlineOrders *o) : user("customer", ID, name, password), comp(C), O(o)
{
    customerID = ID;
}

bool customer::orderFood()
{
    readPoints();
    O->addOrder(points);
    points += 100;
    storePoints();

    cout<<"Your Current Points: "<<points<<endl;

    return true;
}

void customer::storePoints()
{
    ifstream iF("customerPoints.txt", ios::in);
    string line;
    bool found = false;
    int rows = 0;

    while(getline(iF, line))
    {
        rows++;
    }

    int *cID = new int[rows];
    int *p = new int[rows];

    iF.close();

    iF.open("customerPoints.txt", ios::in);
    if(!iF)
    {
        cout << "File not found\n";
        exit(0);
    }
    else
    {
        for(int i = 0; i < rows; i++)
        {
            iF>>p[i]>>cID[i];
            if(cID[i] == customerID)
            {
                p[i] = points;
                found = true;
            }
        }
    }

    iF.close();


    if(found)
    {
        ofstream oF("customerPoints.txt", ios::out);
        if(!oF)
        {
            cout << "File not found\n";
            exit(0);
        }
        else
        {
            for(int i = 0; i < rows; i++)
            {
                oF<<p[i]<<" "<<cID[i]<<endl;
            }
        }
        oF.close();
    }
    else
    {
        ofstream oF("customerPoints.txt", ios::app);
        if(!oF)
        {
            cout << "File not found\n";
            exit(0);
        }
        else
        {
            oF<<points<<" "<<customerID<<endl;
        }
        oF.close();
    }
}

void customer::giveOnlineOrder()
{
    readPoints();
    user::giveOnlineOrder(points);
    points += 100;
    storePoints();
    cout<<"Your Current Points: "<<points<<endl;
}

void customer::giveComplaint(int ID, string complaint)
{
    comp->addComplaint(ID, complaint);
}

void customer::seeNotifications()
{
    user::seeNotifications();
}

void customer::operator+(const complaints &C)
{
    comp->addComplaint(C.getComplaintID(), C.getComplaint());
}

void customer::seePoints()
{
    readPoints();
    cout<<"Your Current Points: "<<points<<endl;
}

int customer::getPoints() const
{
    return points;
}

int customer::getCustomerID() const
{
    return customerID;
}

void customer::readPoints()
{
    ifstream iF("customerPoints.txt", ios::in);
    string line;
    bool found = false;
    int rows = 0;

    while(getline(iF, line))
    {
        rows++;
    }

    int *cID = new int[rows];
    int *p = new int[rows];

    iF.close();

    iF.open("customerPoints.txt", ios::in);
    if(!iF)
    {
        cout << "File not found\n";
        exit(0);
    }
    else
    {
        for(int i = 0; i < rows; i++)
        {
            iF>>p[i]>>cID[i];
            
            if(cID[i] == customerID)
            {
                points = p[i];
                found = true;
            }
        }
    }

    iF.close();
}    

customer::~customer()
{
}
