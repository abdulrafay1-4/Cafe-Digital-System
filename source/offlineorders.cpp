#include"header.h"
#include"stock.h"
#include"orders.h"
#include"offlineorders.h"
#include "offlineorders.h"

offlineOrders::offlineOrders() : orders()
{
}

offlineOrders::offlineOrders(int i, char *iN, int q, double p) : orders(i, iN, q, p)
{
}

void offlineOrders::addOrder(int &points)
{	
    char order[100][18],choice;	
	int quan[100],total_price[100];
    int totalOrderPrice = 0;
    int i = 0,orderID;
    bool duplicate;
	bool check = false;

	//clearing the buffer stream before getline function
	cin.ignore();
	do
	{	
		//Taking input about user's order		
		cout<<"What do you want to order ? ";
		cin.getline(order[i],18,'\n');
						
		cout<<"\nHow much quantity of the item do you want ? \n";
		cin>>quan[i];
		cin.ignore();					
		cout<<"Your Order: \nItem: "<<order[i]<<" Quantity: "<<quan[i]<<endl;
		char file[] = "orders.dat";				
		bool notAvailable = takeOrder(order[i], quan[i], file);
		if(!notAvailable)	{
			cout<<"The item is not available in Cafe Stock OR The quantity is invalid \n";
			cout<<"Do you want to order anything else ? (Y/N)";
			cin>>choice;
			cin.ignore();		
        }
		//when item exists	
		else
		{	
			check = true;
			//ye loop tb tk chle ga jb tk user eik new OrderID na daly
			do
			{
				cout<<"Enter the ID assigned to the Order: ";		
				cin>>orderID;	
				cin.ignore();
				
				char filename[] = "orders.dat";
				//passing in function that order is being taken live and the orderID
				duplicate = duplicateIDCheck(orderID, filename);
							
				//jab orderID pehle se exist krti hai
				if(duplicate)
					cout<<"That OrderID already exists \n";

				//jab exist nhi krti to order orders.txt mai store hojata
				else if(!duplicate)	{
					int ind = findItem(order[i]);
					storeOrder(orderID,order[i],quan[i],checkPrice(order[i]));
					storeSales(order[i]);
					break;
				}
			}while(duplicate);

							
		    //asking customer if he wants to order more
			cout<<"Do you want to order anything else ?";
			cin>>choice;
			cin.ignore();

			//current order ko or uski quantity ko eik dosre array or variable mai rkha or
			//function mai pass krke current order ki total price variable mai store krli
			char orderItem[18];
			strcpy(orderItem,order[i]);
		    int orderQuan = quan[i];

			int ind = findItem(orderItem);
			total_price[i] = checkPrice(orderItem) * quan[i];

			//jab wo eik or order krna chahta to i increment krke array k next index pr chle gye
			if(choice == 'y' || choice == 'Y')
				i++;
			}	
	}while(choice =='Y' || choice =='y');

	if(cin.fail())
		exit(1);


	/*loop mai 0th index se jitne orders howe(i ki value) tb tk increment kiya
	or sary orders display kraye, sath har order ki total_price order ki total price
	mai store krdi or Order ki Total Price display kra di*/


	if(check)	{
			//customer ko transcript generate kra kr show kra di
		cout<<"\nThank you for purchasing through Cafe Digital System \n";
		for(int k = 0;k<=i;k++)
		{
			cout<<"\033[031mItem: \033[0m"<<order[k]<<"\033[031m Quantity: \033[0m"<<quan[k]<<"\033[031m Total Price: \033[0m"<<total_price[k]<<endl;
			totalOrderPrice += total_price[k];
		}
			if(points > 1000)
			{
				char rp;
				cout<<"\n\tYou can earn 10% discount on your order\n";
				cout<<"\n\tDo you want to redeem your points ? (Y/N)";
				cin>>rp;
				if(rp == 'Y' || rp == 'y')
				{
					cout<<"\n\tTotal Price after discount : "<<totalOrderPrice - (totalOrderPrice * 0.1)<<endl;
					points -= 1000;
				}else
					cout<<"\n\tTotal Price of Order : "<<totalOrderPrice<<endl;	
			}
			else
				cout<<"Not Enough Points for Discount\n";
				cout<<"\n\tTotal Price of Order : "<<totalOrderPrice<<endl;
	}
}

void offlineOrders::storeOrder(int orderID, char order[], int quan, double price)
{
	//storing the order in file
	ofstream wF("orders.dat", ios::binary | ios::app);
	if(!wF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		offlineOrders S;
		S.orderID = orderID;
		strcpy(S.item,order);
		S.quantity = quan;
		S.price = price;
		wF.write(reinterpret_cast<char *>(&S), sizeof(orders));
	}
}

void offlineOrders::removeOrder(char filename[])
{
	orders::removeOrder(filename);
}

int operator<<(ostream &out, offlineOrders & o)
{
	char filename[] = "orders.dat";
	int rows = o.getNoOfOrders(filename);
	offlineOrders s;

	ifstream iF("orders.dat", ios::binary);
	out<<"\n\t\033[35m -----------------------------------------------------------\033[0m\n";
	out << "\t\033[35m|\033[0m Order ID    Order Item     Quantity   Price\tTotal Price \033[35m|\033[0m\n";
	out<<"\t\033[35m -----------------------------------------------------------\033[0m\n";
	for(int i = 0; i < rows; i++)
	{
		while(iF.read(reinterpret_cast<char *>(&s), sizeof(orders)))
		{
			if(s.item[0] != '\0')
			{
				if(strlen(s.item) >= 6)
					out << "\033[035m\t| \033[0m  " << s.orderID << "   \t"<< s.item << "\t\t" << s.quantity << "\t" << s.price << "\t" << s.quantity * s.price << "\033[035m\t    |\033[0m" << endl;
				else
					out << "\033[035m\t| \033[0m  " << s.orderID << "   \t"<< s.item << "\t\t" << s.quantity << "\t" << s.price << "\t" << s.quantity * s.price << "\033[035m\t    |\033[0m" << endl;
			}
		}
	}
	iF.close();
	cout<<"\033[35m\t -----------------------------------------------------------\n\033[0m";

	return rows;
}
