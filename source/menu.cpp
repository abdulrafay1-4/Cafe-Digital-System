#include"header.h"
#include"menu.h"

void menu::getCredentials(int &ID, string &name, string &password)
{
    cout << "\n\t\t╔════════════════════════╗" << endl;
    cout << "\t\t║          LOGIN         ║" << endl;
    cout << "\t\t╚════════════════════════╝" << endl;

    cout << "\n\t\t╔════════════════════════╗" << endl;
    cout << "\t\t║ ID: ";
    cin >> ID;
    cout << "\t\t╚════════════════════════╝" << endl;
    cout << "\t\t   ";

    cout << "\n\t\t╔════════════════════════╗" << endl;
    cout << "\t\t║ Username: " ;
    cin >> name;
    cout << "\t\t╚════════════════════════╝" << endl;
    cout << "\t\t   ";
    cout << "\n\t\t╔════════════════════════╗" << endl;
    cout << "\t\t║ Password: ";
    cin >> password;
    cout << "\t\t╚════════════════════════╝" << endl;
    cout << "\t\t   ";    
}

void menu::setRole(string &role)
{
    cout<<"\n\t\tEnter your role:";
    cin>>role;
    if(role == "1")
    {
        role = "admin";
    }
    else if(role == "2")
    {
        role = "employee";
    }
    else if(role == "3" || role == "4" || role == "staff" || role == "faculty" || role == "student")
    {
        role = "customer";
    }
}
void menu::setRoleC(string &role, char &crole)
{
    if(role == "admin")
    {
        crole = 'A';
    }
    else if(role == "employee")
    {
        crole = 'E';
    }
    else if(role == "customer")
    {
        crole = 'C';
    }
    else
    {
        cout<<"Invalid role"<<endl;
    }
}
void menu::setChoice(int &choice)
{
    cout<<"\n\nEnter your choice: ";
    cin>>choice;
}

void menu::setItemDetails(string &name, int &quantity, double &price)
{
    cout<<"\n\tEnter the name of the item: ";
    cin>>name;
    cout<<"\tEnter the quantity: ";
    cin>>quantity;
    cout<<"\tEnter the price: ";
    cin>>price;
}

void menu::getComplaintDetails(int &cID, string &status)
{
    cout<<"\n\tEnter the complaint ID you want to update: ";
	cin>>cID;
    cin.ignore();
	cout<<"\tEnter the status/response of the complaint: ";
	getline(cin, status);    
}

void menu::getNotificationDetails(int &notificationID, string&message)
{
    cout<<"\n\tEnter the notification ID: ";
    cin>>notificationID;
    cin.ignore();
    cout<<"\tEnter the message: ";
    getline(cin, message);
}

void menu::displayMenu()
{
    cout << "\t\t  ______       _______        _________     _______          \n";
    cout << "\t\t /      \\     |   _   |      |             |       |              \n";
    cout << "\t\t|             |  |_|  |      |             |    ___|         \n";
    cout << "\t\t|             |       |      |_____        |   |___          \n";
    cout << "\t\t|             |       |      |             |    ___|          \n";
    cout << "\t\t|             |   _   |      |             |   |___       \n";
    cout << "\t\t \\_____/      |__| |__|      |             |_______|                \n";
    cout << "\n\n";
    cout << "\t\t ____        _____          ______      _____       _____      _______     _\n";
    cout << "\t\t|    \\      |_   _|       /            |_   _|     |_   _|    |       |   | |\n";
    cout << "\t\t|     \\       | |        /               | |         | |      |   _   |   | |\n";
    cout << "\t\t|      \\      | |       /                | |         | |      |  |_|  |   | |\n";
    cout << "\t\t|       \\     | |      /                 | |         | |      |       |   | |\n";
    cout << "\t\t|       /     | |      \\      ____       | |         | |      |       |   | |\n";
    cout << "\t\t|      /      | |       \\    |   |       | |         | |      |       |   | |\n";
    cout << "\t\t|     /       | |        \\       |       | |         | |      |   _   |   | |________\n";
    cout << "\t\t|____/      |_____|       \\______|     |_____|       |_|      |__| |__|   |__________|\n";

    cout << "\n\n";

        std::cout << "\t\t   _______      _      _      _______         _____    _______         _        _\n";
    std::cout << "\t\t  |       |    | |    | |    |       |      |_   _|   |       |       | \\     /| |\n";
    std::cout << "\t\t  |  _____|    | |    | |    |  _____|        | |     |    ___|       | |\\   / | |\n";
    std::cout << "\t\t  | |_____      \\_\\  /_/     | |_____         | |     |   |___        | |  \\/  | |\n";
    std::cout << "\t\t  |_____  |       | |        |_____  |        | |     |    ___|       | |      | |\n";
    std::cout << "\t\t   _____| |       | |         _____| |        | |     |   |___        | |      | |\n";
    std::cout << "\t\t  |_______|       |_|        |_______|        | |     |_______|       |_|      |_|\n";

    cout<<"\n\n\n\033[34m\t\t ---------------------------------------\033[0m\n";
    cout<<"\033[36m\t\t|"<<"\t\033[0m Type Your Choice"<<"\033[36m\t\t|\033[0m\n";
    cout<<"\033[36m\t\t|"<<"\t\033[0m        "<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t\t|"<<"\t\033[0m        "<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t\t|"<<"\t\033[0m1. admin"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t\t|"<<"\t\033[0m2. employee"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t\t|"<<"\t\033[0m3. student"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t\t|"<<"\t\033[0m4. staff/faculty"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t\t|"<<"\t\033[0m5. exit"<<"\033[36m\t\t\t\t|\033[0m"<<endl;
    cout<<"\033[34m\t\t ---------------------------------------\033[0m\n\n";
}

void menu::getupdateChoice(int &choice)
{
    cout<<"\n1. Update price\n2. Update quantity\n\tEnter your choice: ";
    cin>>choice;
}

void menu::takeOrder(char item[], int &quantity)
{
    cout<<"\n\tEnter the item name: ";
    cin>>item;
    cout<<"\tEnter the quantity: ";
    cin>>quantity;

}

void menu::displayAdminMenu()
{
    cout<<"\n\n\033[34m\t ---------------------------------------\033[0m\n";
    cout<<"\033[36m\t|"<<"\t\033[0m1. Logout"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m2. Manage User"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m3. See Stock"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m4. Add Item in Stock"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m5. Remove Item from Stock"<<"\033[36m\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m6. Search Stock"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m7. Sort and See Stock"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m8. Update Stock"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m9. See Online Orders"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m10. See Complaints"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m11. Handle Notifications"<<"\033[36m\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m12. See Best Seller Employee"<<"\033[36m\t|\033[0m\n";
    cout<<"\033[34m\t ---------------------------------------\033[0m\n\n";
}

void menu::displayEmployeeMenu()
{
    cout<<"\n\n\033[34m\t ---------------------------------------\033[0m\n";
    cout<<"\033[36m\t|"<<"\t\033[0m1. Logout"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m2. Take Order"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m3. Deliver Order"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m4. See Orders"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m5. Sort and See Stock"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m6. Calculate Sum"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m7. Calculate Average"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m8. See Item Sales"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m9. Search Stock"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[34m\t ---------------------------------------\033[0m\n\n";
}

void menu::displayCustomerMenu()
{
    cout<<"\n\n\033[34m\t ---------------------------------------\033[0m\n";
    cout<<"\033[36m\t|"<<"\t\033[0m1. Logout"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m2. Order Online"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m3. Give Order"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m4. Give Complaint"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m5. See Notifications"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m6. Sort and See Stock"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m7. Search Stock"<<"\033[36m\t\t\t|\033[0m"<<endl;
    cout<<"\033[36m\t|"<<"\t\033[0m8. See Your Points"<<"\033[36m\t\t|\033[0m"<<endl;
    cout<<"\033[34m\t ---------------------------------------\033[0m\n\n";    
}