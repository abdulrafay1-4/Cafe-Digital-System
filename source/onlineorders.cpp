#include"header.h"
#include"stock.h"
#include"orders.h"
#include"onlineorders.h"

onlineOrders::onlineOrders() : orders()
{
}

onlineOrders::onlineOrders(int i, char *iN, int q, double p) : orders(i, iN, q, p)
{
}

void onlineOrders::addOrder(int &points)
{	
    char order[100][18],choice;	
	int quan[100],total_price[100];
    int totalOrderPrice = 0;
    int i = 0,orderID;
    bool duplicate;

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
		char file[] = "onlineorders.dat";				
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
			//ye loop tb tk chle ga jb tk user eik new OrderID na daly
			do
			{
				cout<<"Enter the ID assigned to the Order: ";		
				cin>>orderID;	
				cin.ignore();
				
				char filename[] = "onlineorders.dat";
				//passing in function that order is being taken live and the orderID
				duplicate = duplicateIDCheck(orderID, filename);
							
				//jab orderID pehle se exist krti hai
				if(duplicate)
					cout<<"That OrderID already exists \n";

				//jab exist nhi krti to order orders.txt mai store hojata
				else if(!duplicate)	{
					int ind = findItem(order[i]);
					double p = checkPrice(order[i]);
					if(points > 1000)
					{
						char rp;
						cout<<"\033[031mYou have enough points to get a discount of 10% \033[0m\n";
						cout<<"\033[031mDo you want to redeem your points ? (Y/N) : \033[0m";
						cin>>rp;
						if(rp == 'Y' || rp == 'y')
						{
							p = p - (p * 0.1);
							points -= 1000;
						}
						else
							cout<<"You have chosen not to redeem your points \n";
					}
					else
						cout<<"You do not have enough points to redeem \n";
					scheduleOrder(orderID,order[i],quan[i],p);
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

	//customer ko transcript generate kra kr show kra di
	cout<<"\nThank you for purchasing through Cafe Digital System \n";
}

void onlineOrders::removeOrder(char filename[])
{
	orders::removeOrder(filename);
}

bool onlineOrders::scheduleOrder(int ID, char order[], int quan, double p)
{
		//storing the order in file
	ofstream wF("onlineorders.dat", ios::binary | ios::app);
	if(!wF)
	{
		cout << "File not found\n";
		exit(0);
	}
	else
	{
		onlineOrders S;
		S.orderID = ID;
		strcpy(S.item,order);
		S.quantity = quan;
		S.price = p;
		wF.write(reinterpret_cast<char *>(&S), sizeof(orders));
	}
    return false;
}

int operator<<(ostream& out, onlineOrders& O)
{
	srand(time(0));

	char filename[] = "onlineorders.dat";
	int rows = O.getNoOfOrders(filename);
	onlineOrders s;

	ifstream iF("onlineorders.dat", ios::binary);
	out<<"\n\t\033[35m ---------------------------------------------------------------------------\033[0m\n";
	out << "\t\033[35m|\033[0m Order ID    Order Item     Quantity   Price\tTotal Price    Time   \t    \033[35m|\033[0m\n";
	out<<"\t\033[35m ---------------------------------------------------------------------------\033[0m\n";
	for(int i = 0; i < rows; i++)
	{
		while(iF.read(reinterpret_cast<char *>(&s), sizeof(orders)))
		{
		int hours = rand() % 24;
        int minutes = rand() % 60;
        int seconds = rand() % 60;

        // Construct the time string in the desired format
        string currentTime = to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
			if(s.item[0] != '\0')
			{
				if(strlen(s.item) >= 6 && currentTime.length() < 8)
					out << "\033[035m\t| \033[0m  " << s.orderID << "   \t"<< s.item << "\t\t" << s.quantity << "\t " << s.price << "\t  " << s.quantity * s.price << "\t    " << currentTime << "\033[035m\t    |\033[0m" << endl;
				else if(strlen(s.item) < 6 && currentTime.length() < 8)
					out << "\033[035m\t| \033[0m  " << s.orderID << "   \t"<< s.item << "\t\t" << s.quantity << "\t " << s.price << "\t  " << s.quantity * s.price << "\t    " << currentTime << "\033[035m\t    |\033[0m" << endl;
				else if(strlen(s.item) >= 6 && currentTime.length() >= 8)
					out << "\033[035m\t| \033[0m  " << s.orderID << "   \t"<< s.item << "\t\t" << s.quantity << "\t " << s.price << "\t  " << s.quantity * s.price << "\t    " << currentTime << "\033[035m\t    |\033[0m" << endl;
				else if(strlen(s.item) < 6 && currentTime.length() >= 8)
					out << "\033[035m\t| \033[0m  " << s.orderID << "   \t"<< s.item << "\t\t" << s.quantity << "\t " << s.price << "\t  " << s.quantity * s.price << "\t    " << currentTime << "\033[035m\t    |\033[0m" << endl;	
			}
		}
	}
	iF.close();
	cout<<"\t\033[35m ----------------------------------------------------------------------------\033[0m\n";

	return rows;
}