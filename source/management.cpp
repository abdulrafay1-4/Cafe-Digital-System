#include"management.h"
#include"stock.h"
#include"complaints.h"
#include"menu.h"

management::management(int ID, string userName, string password, complaints *C, lowStockNotification *lN) : user("admin",ID, userName, password), cL(C), lSN(lN)
{
    managerID = ID;
}

bool management::addItem(const char * item, int quan, double price) 
{
    user::addItem(item, quan, price);
    return true;
}

bool management::removeItem(const char * item)
{
    user::removeItem(item);
    return true;
}

void management::displayStock() const
{
    user::displayStock();
}

void management::updateStock(int choice, int index)
{
    user::updateStock(choice, index);
}

bool management::searchItem(const char * item)
{
    return user::searchItem(item);
}

void management::sortSearch()
{
    user::sortSearch();
}

int management::seeComplaints()
{
   return cL->displayComplaints();
}

void management::removeComplaint(int complaintID)
{
    cL->removeComplaint(complaintID);
}

void management::updateComplaintStatus(int cID, string sts)
{
    cL->updateComplaintStatus(cID, sts);
}

void management::addResponse(int cID, string resp)
{
    cL->addResponse(cID, resp);
}

void management::seeNotifications()
{
    user::seeNotifications();
}

void management::addNotification(int nID, string mes)
{
    user::addNotification(nID, mes);
}

bool management::checkLowStock()
{
    lSN->displayLowStockNotification();
    return true;
}

void management::seeBestSellerEmployee()
{
    ifstream f("sales.txt", ios::in);
    string line;
    int rows = 0;

    while(getline(f, line))
    {
        rows++;
    }

    if(rows<=0)
    {
        cout<<"No sales record found"<<endl;
        return;
    }

    int *eID = new int[rows];
    string *eName = new string[rows];
    int *eSales = new int[rows];

    f.clear();
    f.seekg(0, ios::beg);

    for(int i = 0; i < rows; i++)
    {
        f >> eID[i] >> eName[i] >> eSales[i];
    }

    f.close();

    int temp = 0;
    string temp1;

    for(int i = 0; i < rows; i++)
    {
        for(int j = i + 1; j < rows; j++)
        {
            if(eSales[i] < eSales[j])
            {
                temp = eSales[i];
                eSales[i] = eSales[j];
                eSales[j] = temp;

                temp1 = eName[i];
                eName[i] = eName[j];
                eName[j] = temp1;
            }
        }
    }

    cout<<"The best seller employee is: \nName: "<<eName[0] <<"  ID: "<<eID[0]<<endl;
    cout<<"With sales of: "<<eSales[0]<<endl;

    ofstream f2("sales.txt", ios::out);

    for(int i = 0; i < rows; i++)
    {
        f2 << eID[i] << " " << eName[i] << " " << eSales[i] << endl;
    }    
}

void management::operator-(const complaints &C)
{
    cL->removeComplaint(C.getComplaintID());
}

bool management::operator+(const user &u)
{
    user::addRole(u.getUserRole(), u.getUserID(), u.getUserName(), u.getPassword());
    return true;
}

management::~management()
{
}