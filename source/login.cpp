#include"login.h"
#include"menu.h"

login::login(int ID, string uName, string pass)
{
    if(ID == 0)
    {
       return; 
    }
    else {
    userID = ID;
    userName = uName;
    password = pass;
    }
}

bool login::authenticateLogin(string user, string loginFile)
{
    ifstream iF(loginFile, ios::binary | ios::in);
    if (!iF.is_open())
    {
        cout << "File not found" << endl;
        exit(0);
    }
    else
    {
        login L1;
        
        while(iF.read(reinterpret_cast<char*>(&L1), sizeof(L1)))
        {
            decryptPassword(L1.password);
            if(L1.userID == userID && L1.userName == userName && L1.password == password)
            {
                iF.close();
                return true;
            }
        }
        return false;
    }
    return false;
}

bool login::duplicateIDcheck(int ID, string file)
{
    ifstream iF(file);
    if(!iF) 
    {
        cout << "Unable to open file";
        return false; // or handle error in another appropriate way
    }

    int tempID;
    string restOfLine;
    while(iF >> tempID) 
    {
        getline(iF, restOfLine); // Read the rest of the line

        if(tempID == ID)
        {
            iF.close();
            return true;
        }
    }
    return false;
}

bool login::addUser(string user, int ID, string uName, string pass)
{
    string filename;
    if(user == "admin")
    {
        filename = "adminlogins.dat";
    }
    else if(user == "employee")
    {
        filename = "employeelogins.dat";
    }
    else if(user == "customer")
    {
        filename = "customerlogins.dat";
    }
    else
    {
        cout << "Invalid Role" << endl;
        return false;
    }

    bool dup = duplicateIDcheck(ID, filename);

    if(dup) 
    {
        cout << "ID already exists" << endl;
        return false;
    }

    encryptPassword(pass);
    login L(ID, uName, pass);

    //Update the file with the new credentials
    ofstream wF(filename, ios::binary | ios::app);
    wF.write(reinterpret_cast<char*>(&L), sizeof(L));
    wF.close();
   
    return true;    
}

bool login::removeUser(string role, int ID)
{
    string filename;
    if(role == "admin")
    {
        filename = "adminlogins.dat";
    }
    else if(role == "employee")
    {
        filename = "employeelogins.dat";
    }
    else if(role == "customer")
    {
        filename = "customerlogins.dat";
    }
    else
    {
        cout << "Invalid Role" << endl;
        return false;
    }

	int rows = 0;
	ifstream iF(filename, ios::binary);

	if(!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		login s; // Create a temporary object
		while(iF.read(reinterpret_cast<char *>(&s), sizeof(s))) // Read into the temporary object
		{
			rows++;
		}
	}
	iF.close();

	login *u = new login[rows + 1];

    iF.open(filename, ios::binary);
	for (int i = 0; i < rows; i++)
	{
        iF.read(reinterpret_cast<char*>(&u[i]), sizeof(login));
	}
    iF.close();

    int j = 0;
    bool found = false;
    while(!found && j < rows)
    {
        if(u[j].userID == ID)
        {
            found = true;
            break;
        }
        else
            j++;
    }

    if(found)
    {
        cout<<"here";
        ofstream wF(filename, ios::binary);
        for(int i = 0; i < rows; i++)
        {
            if(i != j)
            {
                wF.write(reinterpret_cast<char *>(&u[i]), sizeof(login));
            }
        }
        return true;
    }
    else
    {
        cout << "User not found" << endl;
        return false;
    }
    return false;
}

void login::updateUser(string role, int ID)
{
    string filename;
    if(role == "admin")
    {
        filename = "adminlogins.dat";
    }
    else if(role == "employee")
    {
        filename = "employeelogins.dat";
    }
    else if(role == "customer")
    {
        filename = "customerlogins.dat";
    }
    else
    {
        cout << "Invalid Role" << endl;
        return;
    }

	int rows = 0;
	ifstream iF(filename, ios::binary);

	if(!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		login s; // Create a temporary object
		while(iF.read(reinterpret_cast<char *>(&s), sizeof(s))) // Read into the temporary object
		{
			rows++;
		}
	}
	iF.close();

	login *u = new login[rows + 1];

    iF.open(filename, ios::binary);
	for (int i = 0; i < rows; i++)
	{
        iF.read(reinterpret_cast<char*>(&u[i]), sizeof(login));
	}
    iF.close();

    int j = 0;
    bool found = false;
    while(!found && j < rows)
    {
        if(u[j].userID == ID)
        {
            found = true;
            break;
        }
        else
            j++;
    }

    if(found)
    {
        cout << "\nEnter new User ID: ";
        cin >> u[j].userID;
        if(duplicateIDcheck(u[j].userID, filename))
        {
            cout << "ID already exists" << endl;
            return;
        }
        cout << "Enter new User Name: ";
        cin >> u[j].userName;
        cout << "Enter new Password: ";
        cin >> u[j].password;

        encryptPassword(u[j].password);

        ofstream wF(filename, ios::binary);
        for(int i = 0; i < rows; i++)
        {
            wF.write(reinterpret_cast<char *>(&u[i]), sizeof(login));
        }
    }
    else
    {
        cout << "User not found" << endl;
    }

}

void login::encryptPassword(string & pass)
{
    for(int i = 0; i < pass.length(); i++)
    {
        pass[i] = pass[i] + 2;
    }
}

void login::decryptPassword(string & password)
{
    for(int i = 0; i < password.length(); i++)
    {
        password[i] = password[i] - 2;
    }
}

void login::display()
{
    cout << "User ID: " << userID << endl;
    cout << "User Name: " << userName << endl;

    decryptPassword(password);
    cout << "Password: " << password << endl;
}

void login::seeUsers(string role) const
{
    string filename;
    if(role == "admin")
    {
        filename = "adminlogins.dat";
    }
    else if(role == "employee")
    {
        filename = "employeelogins.dat";
    }
    else if(role == "customer")
    {
        filename = "customerlogins.dat";
    }
    else
    {
        cout << "Invalid Role" << endl;
        return;
    }

	int rows = 0;
	ifstream iF(filename, ios::binary);

	if(!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		login s; // Create a temporary object
		while(iF.read(reinterpret_cast<char *>(&s), sizeof(s))) // Read into the temporary object
		{
			rows++;
		}
	}
	iF.close();

	login *u = new login[rows + 1];

    iF.open(filename, ios::binary);
	for (int i = 0; i < rows; i++)
	{
        iF.read(reinterpret_cast<char*>(&u[i]), sizeof(login));
        cout<<"\nUser ID: "<<u[i].userID<<endl;
        cout<<"User Name: "<<u[i].userName<<endl;
        cout<<"Password: "<<u[i].password<<endl<<endl;
	}
    iF.close();
}

void readLoginFile(const char filename[], int& rows)
{
        ifstream iF(filename);

        if(!iF.is_open())
        {
            cout << "File not found" << endl;
            exit(0);
        }
        else
        {
            char header[40];
            iF.close();

            ifstream iF(filename);
            iF.getline(header, 40);
            char temp[40];

            while(iF.getline(temp,40,'\n'))
            {
                rows++;
            }
            iF.close();
        }        
}

login::~login()
{
}