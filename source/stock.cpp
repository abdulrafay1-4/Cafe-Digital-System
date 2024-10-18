
#include"header.h"
#include"stock.h"
#include"menu.h"

stock::stock()
{
	itemName[0] = '\0';
	quantity = 0;
	price = 0.0;
	total_price = 0.0;
}

stock::stock(char *iN, int qt, double p)
{
	strcpy(itemName, iN);
	quantity = qt;
	price = p;
	total_price = qt * p;
}

int stock::getObjects()
{
	int objs = 0;
	ifstream iF("stocks.dat", ios::binary);

	if (!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		stock s; // Create a temporary stock object
		while (iF.read(reinterpret_cast<char *>(&s), sizeof(s))) // Read into the temporary object
		{
			if(s.itemName[0] != '\0')
				objs++;
		}
	}
	iF.close();
	return objs;
}

void stock::setItemDetails(const char * i, int q, double p)
{
	strcpy(itemName, i);
	quantity = q;
	price = p;
	total_price = q * p;
}

void stock::addItem(const char *item, int quan, double price)
{
	int rows = getObjects();;

	stock *s = new stock[rows + 1];
	ifstream iF("stocks.dat", ios::binary);
	if (!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
	}
	iF.close();


	int j = 0;
	bool found = false;
	while(j<rows)
	{
		if(strcmp(s[j].itemName, item) == 0)
		{
			found = true;
			break;
		}
		j++;
	}

	if(quan<0 || price<0 || quan>=1000)
	{
		cout<<"Invalid quantity or price\n";
		return;
	}

	if(found)
	{
		cout<<"Item already exists in stock\n";
		return;
	}

	strcpy(s[rows].itemName, item);
	s[rows].quantity = quan;
	s[rows].price = price;
	s[rows].total_price = quan * price;
	
	//Update the file with the new stock
	ofstream wF("stocks.dat", ios::binary | ios::app);
	if (!wF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		
		wF.write(reinterpret_cast<char *>(&s[rows]), sizeof(s[rows]));
	}
	wF.close();
	delete[] s;
}

void stock::updateStock(int value, int index)
{
	int rows = getObjects();
	if (value == 1)
	{
		double price;
		cout << "Enter the updated price: ";
		cin >> price;

		if (price <= 0)
		{
			cout << "Invalid price\n";
			return;
		}
		stock *s = new stock[rows];

		ifstream iF("stocks.dat", ios::binary);
		if (!iF)
		{
			cout << "File not found\n";
			exit(0);
		}
		else
		{
			for (int i = 0; i < rows; i++)
			{
				iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
			}
		}

		s[index].price = price;
		s[index].total_price = s[index].quantity * price;

		ofstream wF("stocks.dat", ios::binary);
		for (int i = 0; i < rows; i++)
		{
			wF.write(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
		wF.close();
	}
	else if (value == 2)
	{
		double quan;
		cout << "Enter the updated quantity: ";
		cin >> quan;

		if (quan < 0)
		{
			cout << "Invalid quantity\n";
			return;
		}

		stock *s = new stock[rows];

		ifstream iF("stocks.dat", ios::binary);
		if (!iF)
		{
			cout << "File not found\n";
			exit(0);
		}
		else
		{
			for (int i = 0; i < rows; i++)
			{
				iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
			}
		}

		s[index].quantity = quan;
		s[index].total_price = s[index].price * quan;

		ofstream wF("stocks.dat", ios::binary);
		for (int i = 0; i < rows; i++)
		{
			wF.write(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
		wF.close();
	}
	else
	{
		cout << "Invalid choice\n";
	}
}

int stock::checkPrice(const char * item)
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
		for (int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
	}
	iF.close();

	for(int i = 0;i<rows;i++)
	{
		if(strcmp(s[i].itemName,item) == 0)
		{
			cout<<"Item exists in stock\n";
			cout<<"\n\tItem: "<<s[i].itemName<<"\n\tQuantity: "<<s[i].quantity<<"\n\tPrice: "<<s[i].price<<"\n\tTotal Price: "<<s[i].total_price<<endl;
			return s[i].price;
		}
	}

	cout<<"Item does not exist in stock\n";
	exit(0);	
}

void stock::updateQuantity(int newQuan, int ind)
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
		for (int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
	}
	iF.close();

	s[ind].quantity = newQuan;
	s[ind].total_price = newQuan * s[ind].price;

	ofstream wF("stocks.dat", ios::binary);
	for (int i = 0; i < rows; i++)
	{
		wF.write(reinterpret_cast<char *>(&s[i]), sizeof(stock));
	}	
}

void stock::calculateTotal(int value)
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
		for (int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
	}
	iF.close();

	int choice;
	if(value == 1)
	{
		double sum = 0;
		cout<<"What sum you want to calculate\n1. Sum of Price\n2. Sum of Quantity\nEnter your choice: ";
		cin>>choice;

		if(choice == 1)
		{
			for(int i = 0;i<rows;i++)
			{
				sum += s[i].price;
			}
			cout<<"Sum of price: "<<sum<<endl;
		}
		else if(choice == 2)
		{
			for(int i = 0;i<rows;i++)
			{
				sum += s[i].quantity;
			}
			cout<<"Sum of quantity: "<<sum<<endl;
		}
		else
		{
			cout<<"Invalid choice\n";
		}
	}
	else if(value == 2)
	{
		double sum = 0;
		cout<<"What average you want to calculate\n1. Average of Price\n2. Average of Quantity\nEnter your choice: ";
		cin>>choice;

		if(choice == 1)
		{
			for(int i = 0;i<rows;i++)
			{
				sum += s[i].price;
			}
			cout<<"Avg of price: "<<sum/double(rows)<<endl;
		}
		else if(choice == 2)
		{
			for(int i = 0;i<rows;i++)
			{
				sum += s[i].quantity;
			}
			cout<<"Avg of Quantity: "<<sum/double(rows)<<endl;
		}
		else
		{
			cout<<"Invalid choice\n";
		}		
	}
}

void stock::randomQuanDecrease()
{
	srand(time(NULL));
	
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
		for (int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
	}
	iF.close();
		
		//har quantity ko random number se decrease kr rhe
		for(int d = 0;d<rows;d++)
		{
			int decrease = rand() % 15;
			int check = s[d].quantity - decrease;
			//check kr rhe decrease k baad negative na hojaye
			if(check <= 0)
			{
				continue;
			}
			else
				s[d].quantity -= decrease;
		}

	ofstream wF("stocks.dat",ios::binary);
	
	for(int i = 0;i<rows;i++)
		wF.write(reinterpret_cast<char*>(&s[i]),sizeof(stock));

}

void stock::removeItem(const char *item)
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
		for (int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
	}
	iF.close();

	int ind = 0;

	for(int i = 0;i<rows;i++)
	{
		if(strcmp(s[i].itemName, item) == 0)
		{
			ind = i;
			break;
		}	
	}

	ofstream wF("stocks.dat", ios::binary);
	for(int i = 0;i<rows;i++)
	{
		if(ind != i)
			wF.write(reinterpret_cast<char *>(&s[i]), sizeof(stock));
	}
}

stock::operator int()
{
	return quantity;
}

bool stock::searchStock(const char* itemN)
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
		for (int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
	}
	iF.close();

	for(int i = 0;i<rows;i++)
	{
		if(strcmp(s[i].itemName,itemN) == 0)
		{
			cout<<"\033[031m\n\tItem: \033[0m"<<s[i].itemName<<"\033[031m\n\tQuantity: \033[0m"<<s[i].quantity<<"\033[031m\n\tPrice: \033[0m"<<s[i].price<<"\033[031m\n\tTotal Price: \033[0m"<<s[i].total_price<<endl;
			return true;
		}
	}

	return false;
}

int stock::findItem(char orderItem[])
{
	int rows = getObjects();
	stock *s = new stock[rows];
	ifstream iF("stocks.dat", ios::binary);
	if(!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
	}
	iF.close();

	int ind = 0;
	for(;ind<rows;ind++)
	{
		if(strcmp(s[ind].itemName,orderItem) == 0)
		{
			return ind;
		}
	}
	return ind;
}

void stock::sortStock()
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
		for (int i = 0; i < rows; i++)
		{
			iF.read(reinterpret_cast<char *>(&s[i]), sizeof(stock));
		}
	}
	iF.close();	

	int sort;
	cout<<"How do you want to sort the stock?\n";
	cout<<"1. Sort by item name\n";
	cout<<"2. Sort by quantity\n";
	cout<<"3. Sort by price\n";
	cin>>sort;

	if(sort == 1)	{
		for(int i = 0;i<rows;i++)
		{
			for(int j = 0;j<rows-1;j++)
			{
				if(strcmp(s[j].itemName,s[j+1].itemName) > 0)
				{
					stock temp = s[j];
					s[j] = s[j+1];
					s[j+1] = temp;
				}
			}
		}
	}
	else if(sort == 2)
	{
		for(int i = 0;i<rows;i++)
		{
			for(int j = 0;j<rows-1;j++)
			{
				if(s[j].quantity > s[j+1].quantity)
				{
					stock temp = s[j];
					s[j] = s[j+1];
					s[j+1] = temp;
				}
			}
		}	
	}
	else if(sort == 3)
	{
		for(int i = 0;i<rows;i++)
		{
			for(int j = 0;j<rows-1;j++)
			{
				if(s[j].price > s[j+1].price)
				{
					stock temp = s[j];
					s[j] = s[j+1];
					s[j+1] = temp;
				}
			}
		}	
	}
	else
	{
		cout<<"Invalid choice\n";
	}

	ofstream wF("stocks.dat", ios::binary);
	for(int i = 0;i<rows;i++)
	{
		wF.write(reinterpret_cast<char *>(&s[i]), sizeof(stock));
	}	

}

stock::~stock()
{
}

const char *stock::getItemName() const
{
    return itemName;
}

int stock::getQuantity() const
{	
    return quantity;
}

double stock::getPrice() const
{
    return price;
}

ostream &operator<<(ostream &out, stock &S)
{
	int objs = S.getObjects();
	out<<"\n\t\033[35m ---------------------------------------------------\033[0m\n";
	out << "\t\033[35m|\033[0m Order Item\t     Quantity\tPrice\tTotal Price \033[35m|\033[0m\n";
	out<<"\t\033[35m ---------------------------------------------------\033[0m\n";
	ifstream iF("stocks.dat", ios::binary);
	
	stock s;
	if (!iF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		while (iF.read(reinterpret_cast<char *>(&s), sizeof(stock)))
		{
			if(s.itemName[0] != '\0')	{
				if (strlen(s.itemName) >= 6)
				{
					if(s.quantity == 0)
						out << "\t\033[33m| " << s.itemName << "\t\t" << s.quantity << "\t" << s.price << "\t" << s.quantity * s.price << "\033[035m\t    |\033[0m" << endl;
					else if(s.quantity < 15)
						out << "\t\033[31m| " << s.itemName << "\t\t" << s.quantity << "\t" << s.price << "\t" << s.quantity * s.price << "\033[035m\t    |\033[0m" << endl;
					else
						out << "\033[035m\t| \033[0m" << s.itemName << "\t\t" << s.quantity << "\t" << s.price << "\t" << s.quantity * s.price << "\033[035m\t    |\033[0m" << endl;
				}
				else{
					if(s.quantity == 0)
						out << "\t\033[33m| " << s.itemName << "\t\t\t" << s.quantity << "\t" << s.price << "\t" << s.quantity * s.price << "\033[035m\t    |\033[0m" << endl;
					else if(s.quantity < 15)
						out << "\t\033[31m| " << s.itemName << "\t\t\t" << s.quantity << "\t" << s.price << "\t" << s.quantity * s.price << "\033[035m\t    |\033[0m" << endl;
					else
						out << "\033[035m\t| \033[0m" << s.itemName << "\t\t\t" << s.quantity << "\t" << s.price << "\t" << s.quantity * s.price << "\033[035m\t    |\033[0m" << endl; 
				}
			}
		}
	}
	out<<"\033[35m\t ---------------------------------------------------\n\033[0m";
	iF.close();
	return out;
}