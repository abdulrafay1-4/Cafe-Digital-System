#include"header.h"
#include"user.h"

user::user(string role, int ID, string uName, string pass, stock* s, onlineOrders *ON, notification *n):L(ID, uName, pass), stck(s), O(ON), N(n)
{
    Role = role;
    userID = ID;
    userName = uName;
    password = pass;
}

int user::seeComplaints()
{
    cout << "You do not have the permission to see complaints" << endl;
    return 0;
}

void user::removeComplaint(int)
{
    cout << "You do not have the permission to remove complaints" << endl;
}

void user::updateComplaintStatus(int, string)
{
    cout << "You do not have the permission to update complaints" << endl;
}

void user::giveComplaint(int, string)
{
    cout << "You do not have the permission to give complaints" << endl;
}

void user::addResponse(int, string)
{
    cout << "You do not have the permission to add responses" << endl;
}

bool user::addItem(const char * item, int quan, double price) 
{
    if(Role == "admin")
        stck->addItem(item, quan, price);
    else
        return false;

    return true;
}

bool user::removeItem(const char * item)
{
    if(Role == "admin")
        stck->removeItem(item);
    else
        return false;    
        
        return true;
}

void user::displayStock() const
{
    cout<<*stck;
}

void user::updateStock(int choice, int index)
{
    if(Role == "admin")
        stck->updateStock(choice, index);
    else
        cout<<"You donot have permission to use this functions\n";    
}

void user::updateRole(string role, int ID)
{
    L.updateUser(role, ID);
}

void user::displayUsers(string role)
{
    L.seeUsers(role);
}

void user::seePoints()
{
    cout << "You do not have the permission to see points" << endl;
}

bool user::searchItem(const char * item)
{
    return stck->searchStock(item);
}

void user::sortSearch()
{
    stck->sortStock();
}

int user::seeOnlineOrders()
{
    return cout<<*O;
}

void user::giveOnlineOrder()
{
    cout<<"You do not have the permission to give online orders"<<endl;
}

void user::giveOnlineOrder(int& points)
{
    O->addOrder(points);
}

void user::seeNotifications()
{
    cout<<*N;
}

void user::addNotification(int nID, string mes)
{
    if(Role == "admin")
    {
        N->addNotification(nID, mes);
    }
    else
    {
        cout << "You do not have the permission to add notifications" << endl;
    }
}

bool user::checkLowStock()
{
    cout << "You do not have the permission to check low stock" << endl;
    return false;
}

bool user::addRole(string user, int ID, string uName, string pass)
{
    L.addUser(user, ID, uName, pass);
    return true;
}

bool user::removeRole(string user, int ID)
{
    if(Role == "admin")
    {
        L.removeUser(user, ID);
        return true;
    }
    else
        cout << "You donot have permission to use this function\n";
    return false;
}

bool user::orderFood()
{
    cout << "You do not have the permission to order food" << endl;
    return false;
}

int user::seeOrders()
{
    cout << "You do not have the permission to see orders" << endl;
    return -1;
}

void user::deliverOrder(int dummy)
{
    cout << "You do not have the permission to deliver orders" << endl;
}

void user::calculateTotal(int choice)
{
    stck->calculateTotal(choice);
}

void user::seeItemSales()
{
    cout << "You do not have the permission to see item sales" << endl;
}

void user::randomDecrease()
{
    stck->randomQuanDecrease();    
}

bool user::authenticateUser()
{
    string loginFile;
    if(Role == "admin")
    {
        loginFile = "adminlogins.dat";
    }
    else if(Role == "employee")
    {
        loginFile = "employeelogins.dat";

    }
    else if(Role == "customer")
    {

        loginFile = "customerlogins.dat";
    }
    else
    {
        cout << "Invalid user" << endl;
        return false;
    }    

    return L.authenticateLogin(Role, loginFile);
}

void user::setUserRole(string User)
{
    Role = User;
}

void user::setUserName(string uName)
{
    userName = uName;
}

void user::setPassword(string pass)
{
    password = pass;
}

void user::setUserID(int ID)
{
    userID = ID;
}

string user::getUserRole() const
{
    return Role;
}

string user::getUserName() const
{
    return userName;
}

string user::getPassword() const
{
    return password;
}

int user::getUserID() const
{
    return userID;
}
