#include "lowstocknotification.h"

lowStockNotification::lowStockNotification(int nID, string mes, const char *iName, int qt, double p) : notification(nID, mes)
{
    strcpy(itemName, iName);
    quantity = qt;
    price = p;
    stk = new stock;
}

bool lowStockNotification::checkThreshold(char item[])
{
    int rows = stk->getObjects();

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

    int ind = s->findItem(item);

    if(s[ind].getQuantity() < 15)
    {
        threshold = true;
    }
    else
    {
        threshold = false;
    }

    delete[] s;
    return threshold;
}

void lowStockNotification::displayLowStockNotification()
{  
    int rows = stk->getObjects();
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
		if(s[i].getQuantity() == 0)
		{
			threshold = true;
			if(strlen(s[i].getItemName()) > 7)
				cout << "\033[33m" << s[i].getItemName() << "\t\t" << s[i].getQuantity() << "\t" << s[i].getPrice() << "\t" << s[i].getQuantity() * s[i].getPrice() << "\033[0m" << endl;
			else
				cout << "\033[33m" << s[i].getItemName() << "\t\t\t" << s[i].getQuantity() << "\t" << s[i].getPrice() << "\t" << s[i].getQuantity() * s[i].getPrice() <<  "\033[0m" << endl;
        
		}
        else if(s[i].getQuantity() < 15 && s[i].getQuantity() > 0)
        {
            threshold = true;

			if(strlen(s[i].getItemName()) > 7)
				cout << "\033[31m" << s[i].getItemName() << "\t\t" << s[i].getQuantity() << "\t" << s[i].getPrice() << "\t" << s[i].getQuantity() * s[i].getPrice() << "\033[0m" << endl;
			else
				cout << "\033[31m" << s[i].getItemName() << "\t\t\t" << s[i].getQuantity() << "\t" << s[i].getPrice() << "\t" << s[i].getQuantity() * s[i].getPrice() <<  "\033[0m" << endl;
        }
		else
		{
        	if(strlen(s[i].getItemName()) > 7)
				cout << s[i].getItemName() << "\t\t" << s[i].getQuantity() << "\t" << s[i].getPrice() << "\t" << s[i].getQuantity() * s[i].getPrice() << endl;
			else
				cout << s[i].getItemName() << "\t\t\t" << s[i].getQuantity() << "\t" << s[i].getPrice() << "\t" << s[i].getQuantity() * s[i].getPrice() << endl;			
		}
    }
    if(threshold)
    {
        orderStock();
    }
    else
    {
        cout << "No items in low stock\n";
    }

    delete[] s;
}

void lowStockNotification::orderStock()
{
    int rows = stk->getObjects();

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
    	
    char choice;
    char order[18];

        if(threshold)
		{
		 do
	  	 {	
			//usse order le jb tk wo dena chahta hai

			cout<<"\n\tDo you want to order any one of these items? (Y/N) \n";
	  	 	cin>>choice;
	  	 	cin.ignore();
	  	 	if(choice == 'Y' || choice == 'y')
	  	 	{
	  	 		cout<<"\tEnter the item you want to order : ";
	  	 		cin.getline(order,18,'\n');
	  	 		int index = s->findItem(order);
                if(index != -1)
        	 	{
        	 		cout<<"\tEnter the quantity you want to order : ";
        	 		int q;
        	 		cin>>q;
                    int newQuan = q + s[index].getQuantity();
        	 		if(newQuan > 0 && newQuan < 999)
        	 		{
        	 			stk->updateQuantity(newQuan, index);
        	 			cout<<"\tOrder placed successfully\n";
        	 		}
        	 		else
        	 		{
        	 			cout<<"\tInvalid quantity\n";
        	 		}
        	 	}
        	 		else
        	 		{
        	 			cout<<"\tItem not found\n";
        	 		}
	  	 	}
	  	 	else if(choice == 'n' || choice =='N')
	  	 	    return;
	  	 	else	{
                cout<<"Enter a valid choice \n";
                exit(1);
			}
	  	 }while(choice == 'Y' || choice == 'y');
		}
}

lowStockNotification::~lowStockNotification()
{
    delete stk;
}
