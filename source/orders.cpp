#include"offlineorders.h"
#include"stock.h"
#include"header.h"
#include"orders.h"

orders::orders() : stock()
{
	orderID = 0;
	strcpy(item, "");
	quantity = 0;
	price = 0;
}

orders::orders(int id, char iN[], int qt, double p) : stock(iN, qt, p)
{
	orderID = id;
	strcpy(item, iN);
	quantity = qt;
	price = p;
}

void orders::storeSales(char item[])
{
    ifstream iF("itemsales.txt", ios::in);
    string line;
    bool found = false;
    int rows = 0;

    while(getline(iF, line))
    {
        rows++;
    }

    char **items = new char*[rows];
    int *p = new int[rows];

	for(int i = 0; i < rows; i++)
	{
		items[i] = new char[18];
	}

    iF.close();

    iF.open("itemsales.txt", ios::in);
    if(!iF)
    {
        cout << "File not found\n";
        exit(0);
    }
    else
    {
        for(int i = 0; i < rows; i++)
        {
			iF.getline(items[i], 18, ' ');
            iF>>p[i];
			if(strcmp(items[i], item) == 0)
			{
				p[i] += 1;
				found = true;
			}
        }
    }

    iF.close();


    if(found)
    {
        ofstream oF("itemsales.txt", ios::out);
        if(!oF)
        {
            cout << "File not found\n";
            exit(0);
        }
        else
        {
            for(int i = 0; i < rows; i++)
            {
                oF<<items[i]<<" "<<p[i]<<endl;
            }
        }
        oF.close();
    }
    else
    {
        ofstream oF("itemsales.txt", ios::app);
        if(!oF)
        {
            cout << "File not found\n";
            exit(0);
        }
        else
        {
			oF<<item<<" "<<1<<endl;
        }
        oF.close();
    }	
}

void orders::displaySales() const
{
	ifstream iF("itemsales.txt", ios::in);
	if(!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		char item[18];
		int p;
		cout<<"\n\t\033[035m -------------------------------\033[0m\n";
		cout<<"\t\033[035m| \033[0mItems"<<"\t\tSales "<<"\t\t\033[035m|\033[0m\n";
		cout<<"\t\033[035m -------------------------------\033[0m\n";
		while(iF>>item>>p)
		{
			if(strlen(item) >= 5)
				cout<<"\t\033[035m|  \033[0m"<<item<<"\t   "<<p<<"\033[035m\t\t|\033[0m"<<endl;
			else
				cout<<"\t\033[035m|  \033[0m"<<item<<"\t\t   "<<p<<"\033[035m\t\t|\033[0m"<<endl;
		}
	}
	iF.close();
	cout<<"\t\033[035m -------------------------------\033[0m\n";
}

int orders::getNoOfOrders(char filename[])
{
	int objs = 0;
	ifstream iF(filename, ios::binary);

	if(!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		orders O; // Create a temporary stock object
		while (iF.read(reinterpret_cast<char *>(&O), sizeof(O))) // Read into the temporary object
		{
			if(O.item[0] != '\0')
				objs++;
		}
	}
	iF.close();
	return objs;	
}

bool orders::takeOrder(char order[], int quan, char filename[])
{
	int rows = getObjects();
	stock *s = new stock[rows];
	ifstream iF("stocks.dat", ios::binary);
	if (!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		for(int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
	}
	iF.close();	

	
	int ind = 0;
	while(ind<rows)
	{
		if(strcmp(s[ind].getItemName(), order) == 0)
		{
			break;
		}
		else
			ind++;
	}

    if(!searchStock(order))
    {
		return false;
    }
   else
		{
			//jb quantity valid ho
			if(quan>0)	{
		
				int newQuan = s[ind].getQuantity() - quan;

				if(newQuan<0 || newQuan>999)
				{
					return false;
				}

                updateQuantity(newQuan, ind);
            }      

			return true;
        }
		return false;
}

void orders::removeOrder(char filename[])
{	
	int rows = getNoOfOrders(filename);
	orders *s = new orders[rows];
	ifstream iF(filename, ios::binary);
	if(!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		for(int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(orders));
		}
	}
	iF.close();	

	int ID;
	cout<<"Enter the OrderID you want to remove: ";
	cin>>ID;
	cin.ignore();

	bool find = false;
	int j = 0;
	while(!find && j<rows)
	{
		if(s[j].orderID == ID)
		{
			find = true;
		}
		else
			j++;
	}

	if(find)
	{
		s[j].item[0] = '\0';
		s[j].quantity = 0;
		s[j].price = 0;
		s[j].orderID = 0;

		ofstream oF(filename, ios::binary);
		for(int i = 0; i < rows; i++)
		{
			if(i != j)
				oF.write(reinterpret_cast<char *>(&s[i]), sizeof(orders));
		}
		oF.close();
	}
	else
		cout<<"Order not found\n";
}

bool orders::duplicateIDCheck(int id, char filename[])
{
	int rows = getObjects();
	orders *s = new orders[rows];
	ifstream iF(filename, ios::binary);
	if (!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(orders));
		}
	}
	iF.close();    

	//finding if entered id matches in file
	bool find = true;	
    int j = 0;
	while(find && j<rows)
	{
		if(s[j].orderID == id)
		{
			find = false;
		}
		else
		j++;
	}

			//jab match kre to true return
			if(!find)
			return true;    
    return false;
}