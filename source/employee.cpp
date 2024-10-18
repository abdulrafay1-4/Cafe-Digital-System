#include"employee.h"
#include"user.h"
#include"orders.h"

int employee::sales = 0;

employee::employee(int ID, string name, string password, offlineOrders* O) : user("employee",ID, name, password),order(O)
{
    employeeID = ID;
}

employee::~employee()
{
    cout<<"Employee Deleted"<<endl;
}

bool employee::orderFood()
{
    int points = 0;
    order->addOrder(points);
    sales++;
    storeSales();
    return true;
}

int employee::seeOrders()
{
    return cout<<*order;
}


void employee::deliverOrder(int choice)
{
    string file;
    if(choice == 1)
    {
        onlineOrders o;
        char filename[] = "onlineorders.dat";
        o.removeOrder(filename);
    }
    else if(choice == 2)
    {
        char filename[100] = "orders.dat";
        order->removeOrder(filename);
    }
}

void employee::seeItemSales()
{
    order->displaySales();
}

int employee::getSales() const
{
    return employee::sales;
}

void employee::storeSales()
{
    ifstream oF("sales.txt", ios::in);
    string line;
    int rows = 0;

    while(getline(oF, line))
    {
        rows++;
    }

    int *eID = new int[rows];
    string *eName = new string[rows];
    int *eSales = new int[rows];

    oF.clear();
    oF.seekg(0, ios::beg);

    for(int i = 0; i < rows; i++)
    {
        oF >> eID[i] >> eName[i] >> eSales[i];
    }

    bool found = false;

    for(int i = 0; i < rows; i++)
    {
        if(eID[i] == getUserID())
        {
            found = true;
            break;
        }
    }
    oF.close();

    if(found)
    {
        ofstream oF2("sales.txt", ios::out);

        for(int i = 0; i < rows; i++)
        {
            if(eID[i] == getUserID())
            {
                eSales[i] += sales;
            }
            oF2 << eID[i] << " " << eName[i] << " " << eSales[i] << endl;
        }
        oF2.close();        
    }
    else
    {
        ofstream oF2("sales.txt", ios::app);
        oF2 << getUserID() << " " << getUserName() << " " << sales << endl;
        oF2.close();
    }

    delete[] eID;
    delete[] eName;
    delete[] eSales;
    sales = 0;
}

void employee::seeSales()
{
    ifstream iF("sales.txt", ios::in);
    if(!iF)
    {
        cout << "File not found\n";
        return;
    }
    else
    {
        string line;
        while(getline(iF, line))
        {
            cout << line << endl;
        }
    }
    iF.close();
}
