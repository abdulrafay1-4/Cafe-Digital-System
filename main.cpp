#include"employee.h"
#include"management.h"
#include"customer.h"
#include"user.h"
#include"menu.h"
#include"orders.h"
#include"stock.h"
#include"offlineorders.h"
#include"onlineorders.h"
#include"lowstocknotification.h"
#include"notifcation.h"
#include"complaints.h"

int main()
{
	//label to go back to the main menu after logging out
	//Objects are declared for sharing in aggregation
	label:
	int count = 3;
	stock S;
	offlineOrders O;
	onlineOrders oN;
	notification N;
	complaints C;
	lowStockNotification lN;

	char file[] = "onlineorders.dat";
	int choice;
	absuser *U[4];
	menu M;
	int userID;
	string username, password, role;	
	M.displayMenu();

	//when user selects to exit
	M.setRole(role);
	if(role == "exit" || role == "5")
	{
		cout<<"Exiting..."<<endl;
		for (int i = 0; i < 2; ++i) 
		{
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
		system("clear");
		cout<<"\n\n\033[031m\tTHANK YOU FOR USING CAFE DIGITAL SYSTEM\033[0m\n\n";
		exit(0);
	}

	//Ask user for his credentials 3 times
	do
	{
		M.getCredentials(userID,username,password);

		cout<<"Retreiving data from the database..."<<endl;
		for (int i = 0; i < 2; ++i) 
		{
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
		
		U[0] = new user(role, userID, username, password, &S, &oN, &N);
		
		if(count<=0)
		{
			cout<<"\n\n\033[031m\t!!INVALID!!\n\nYou have exceeded the number of tries\033[0m\n\n";
			exit(0);
		}

		if(!U[0]->authenticateUser())
		{
			cout<<"WRONG CREDENTIALS FOR : "<<role<<"\n\n";
			for (int i = 0; i < 10; ++i) 
			{
				this_thread::sleep_for(chrono::milliseconds(100));
			}
			system("clear");
			count--;
			cout<<"\033[033m TRY AGAIN !!! \n\nTRIES LEFT: "<<count<<" \033[0m";
		}	
	} while (count>0 && !U[0]->authenticateUser());
	
	if(count<=0)
	{
		cout<<"\n\n\033[031m\t!!INVALID!!\n\nYou have exceeded the number of tries\033[0m\n\n";
		exit(0);
	}

	management A(userID, username, password, &C, &lN);
	employee E(userID, username, password, &O);
	customer c(userID, username, password, &C, &O);

	char c_role;
	M.setRoleC(role, c_role);

	switch(c_role)
	{
		//when user is admin
		case 'A':
			U[1] = new management(userID, username, password, &C, &lN);
			
			if(U[0]->authenticateUser())
			{
				cout << "\n\t\033[033mWELCOME ADMIN\033[0m" << endl;
				for (int i = 0; i < 2; ++i) 
				{
					this_thread::sleep_for(chrono::milliseconds(1000));
				}		
				cout<<"\n\033[031mYour Notifications for today are\033[0m: \n\n";
				U[1]->seeNotifications();
				for (int i = 0; i < 1; ++i) 
				{
					this_thread::sleep_for(chrono::milliseconds(1000));
				}		
				char rp;				
				cout<<"\n\n\033[031mThese are the Online Orders Due Today \033[0m: \n\n";
				if(U[1]->seeOnlineOrders() > 0 )
				{
					cout<<"\n\tDo you want to deliver the orders? (Y/N): ";		
					cin>>rp;
					if(rp == 'Y' || rp == 'y')
					{
						O.removeOrder(file);
					}
				}
				else
					cout<<"\n\033[031mNo Online Orders Due Today\033[0m"<<endl;
				
				cout<<"\n\n\033[031mChecking for Low Stock Items \033[0m: \n\n";
				for (int i = 0; i < 3; ++i) 
				{
					this_thread::sleep_for(chrono::milliseconds(1000));
				}			
				U[1]->checkLowStock();
				for (int i = 0; i < 1; ++i) 
				{
					this_thread::sleep_for(chrono::milliseconds(1000));
				}
			}
			else
			{
				cout<<"Invalid user"<<endl;
				exit(0);
			}
		//loop to ask for his choice again and again	
		do	{
			int choice;
			M.displayAdminMenu();
			M.setChoice(choice);
			switch(choice)
			{
			case 1:{
				cout<<"Logged out"<<endl;
				system("clear");
				U[1]->randomDecrease();
				goto label;
				break;}
			case 2:{
				int resp;
				cout<<"What do you want to do\n1. Add user\n2. Remove User\n3. Update User\n4. See Users\n\n\tEnter your choice: ";
				cin>>resp;
				if(resp == 1)
				{
					int ID;
					string name, password, role;
					M.setRole(role);
					M.getCredentials(ID, name, password);
					U[1]->addRole(role, ID, name, password);
				}
				else if(resp == 2)
				{
					int ID;
					string role;
					M.setRole(role);
					cout<<"\n\tEnter the ID to be removed: ";	cin>>ID;
					U[1]->removeRole(role, ID);
				}
				else if(resp == 3)
				{
					string cRole;
					int cId;
					cout<<"Enter role to be updated: ";	cin>>cRole;
					cout<<"Enter ID to be updated: ";	cin>>cId;
					U[1]->updateRole(cRole, cId);
				}
				else if(resp == 4)
				{
					string cRole;
					cout<<"Enter the role of users you want to see: ";	cin>>cRole;
					U[1]->displayUsers(cRole);
				}
				else
					cout<<"Invalid Choice\n";
				break;}
			case 3:{
				U[1]->displayStock();
				break;}
			case 4:{
				
				string iName;
				int iQuantity;
				double iPrice;
				M.setItemDetails(iName, iQuantity, iPrice);

				if(U[1]->addItem(iName.c_str(), iQuantity, iPrice))
				{
					cout<<"Item added"<<endl;
				}
				else
				{
					cout<<"Item not added"<<endl;
				}
				break;}
			case 5:{
				string iName;
				cout<<"\n\tEnter the name of the item: ";
				cin>>iName;
				const char *iname = iName.c_str();
				if(U[1]->removeItem(iname))
				{
					cout<<"Item removed"<<endl;
				}
				else
				{
					cout<<"Item not removed"<<endl;
				}
			break;}

			case 6:{
				string iName;
				cout<<"\n\tEnter the name of the item: ";
				cin>>iName;
				const char *iname = iName.c_str();
				if(U[1]->searchItem(iname))
				{
					cout<<"Item found"<<endl;
				}
				else
				{
					cout<<"Item not found"<<endl;
				}
			break;}
			case 7:{
				U[1]->sortSearch();
				U[1]->displayStock();
			break;}
			case 8:{
				int choice, index;
				M.getupdateChoice(choice);
				U[1]->displayStock();

				cout<<"\n\tEnter the index of the item you want to update (starting from 0): ";
				cin>>index;

				U[1]->updateStock(choice, index);
				break;}
			
			case 9:{
				char rp;				
				cout<<"\n\n\033[031mThese are the Online Orders Due Today \033[0m: \n\n";
				if(U[1]->seeOnlineOrders() > 0)
				{
					cout<<"\n\tDo you want to deliver the orders? (Y/N): ";		
					cin>>rp;
					if(rp == 'Y' || rp == 'y')
					{
						O.removeOrder(file);
					}
				}
				else
					cout<<"\n\033[031mNo Online Orders Due Today\033[0m"<<endl;
				break;}
			
			case 10:{
				if(U[1]->seeComplaints() <= 0)
				{
					cout<<"No complaints to display"<<endl;
					break;
				}

				cout<<"\nDo you want to handle the complaint(s)? (Y/N): ";
				char response;
				cin>>response;
				if(response == 'Y' || response == 'y')
				{
					cout<<"\n\tWhat do you want to do with the complaint(s)?\n1. Remove the complaint\n2. Update the status of the complaint\n3. Add a Response\nEnter your choice:";
					int resp;
					cin>>resp;
					string status;
					int cID;
					if(resp == 1)	{
						cout<<"\n\n\tEnter complaint ID: ";
						cin>>cID;
						U[1]->removeComplaint(cID);
					}
					else if(resp == 2) {
						M.getComplaintDetails(cID, status);
						U[1]->updateComplaintStatus(cID, status);
					}else if(resp == 3){
						M.getComplaintDetails(cID, status);
						U[1]->addResponse(cID, status);
					}else
						cout<<"Invalid choice"<<endl;

				}
				else
					cout<<"Complaint(s) not responded"<<endl;
				break;}

			case 11:{
				char response;

				cout<<"\nDo you want to add any new notification?\n1. Yes(Y)\n2. No(N)\n\n\tEnter your choice: ";
				cin>>response;
				if(response == 'Y' || response == 'y')
				{
					int nID;
					string message;
					M.getNotificationDetails(nID, message);
					U[1]->addNotification(nID, message);
				}
				else
					cout<<"No new Notification added"<<endl;	
			break;}

			case 12:{
				cout<<"\n\t\033[031mThese are all the employees that have made sales:\033[0m \n\n";
				A.seeBestSellerEmployee();
			break;}

			default:{
				cout<<"Invalid choice"<<endl;
				break;}
		}
		}while(choice != 1);			
			break;

		//when user is employee
		case 'E':
			U[2] = new employee(userID, username, password, &O);
			if(U[0]->authenticateUser())
			{
				cout << "\n\t\033[033mWELCOME EMPLOYEE\033[0m" << endl;
				cout<<"\n\033[033mThese are your notifications for today: \033[0m\n";
				U[2]->seeNotifications();
				for (int i = 0; i < 2; ++i) 
				{
					this_thread::sleep_for(chrono::milliseconds(1000));
				}
				char rp;
				cout<<"\n\n\033[033mThese are the Online Orders Due Today:\033[0m \n";
				if(U[2]->seeOnlineOrders() > 0)
				{
					cout<<"\n\tDo you want to deliver the orders? (Y/N): ";		
					cin>>rp;
					if(rp == 'Y' || rp == 'y')
					{
						O.removeOrder(file);
					}
				}
				else
					cout<<"\n\033[031mNo Online Orders Due Today\033[0m"<<endl;
				for (int i = 0; i < 1; ++i) 
				{
					this_thread::sleep_for(chrono::milliseconds(1000));
				}
			}
			else
				cout<<"Invalid user"<<endl;

			//loop to ask for his choice again and again
			do {
				M.displayEmployeeMenu();
				M.setChoice(choice);
				switch(choice)
				{
					case 1:{
						cout<<"Logged out"<<endl;
						U[2]->randomDecrease();
						system("clear");
						goto label;
						break;}
					case 2:{
						U[2]->displayStock();
						int points = 0;
						U[2]->orderFood();
					break;}	

					case 3:{
						int value;
						cout<<"\nWhich order do you want to deliver?\n\n";
						cout<<"\t1. Online Orders\n";
						cout<<"\t2. Offline Orders\n";
						cout<<"\nResponse: ";
						cin>>value;
						int check = 0;
						if(value == 1)
							check = U[2]->seeOnlineOrders();
						else if(value == 2)
							check = U[2]->seeOrders();
						else
							cout<<"Invalid choice"<<endl;
						if(check > 0)
							U[2]->deliverOrder(value);
						else
							cout<<"No orders to deliver"<<endl;	
						break;}
					case 4:{
						int value;
						cout<<"\nWhich order do you want to see?\n";
						cout<<"\t1. Online Orders\n";
						cout<<"\t2. Offline Orders\n";
						cout<<"\nResponse: ";
						cin>>value;
						if(value == 1)
							U[2]->seeOnlineOrders();
						else if(value == 2)
							U[2]->seeOrders();
					break;}

					case 5:{
						U[2]->sortSearch();
						U[2]->displayStock();
					break;}

					case 6:{
						U[2]->calculateTotal(1);
					break;}
				    
					case 7:{
						U[2]->calculateTotal(2);
					break;}

					case 8:{
						E.seeItemSales();
					break;}

					case 9:{
						char item[18];
						cin.ignore();
						cout<<"Enter the item you want to search:";
						cin.getline(item, 18);
						U[2]->searchItem(item);
					break;}

					default:{
						cout<<"Invalid choice"<<endl;
						break;}
				}
			}while(choice!=1);
			break;
		
		//when user is customer
		case 'C':
			U[3] = new customer(userID, username, password, &C, &O);
			if(U[0]->authenticateUser())
			{
				cout << "\n\t\033[033mWELCOME CUSTOMER\033[0m" << endl;
				cout<<"\n\033[033mNOTIFICATIONS: \033[0m\n";

				U[3]->seeNotifications();
			}
			else
				cout<<"Invalid user"<<endl;
		
		//loop to ask for his choice again and again
		do {
			M.displayCustomerMenu();
			M.setChoice(choice);
			switch(choice)
			{
			case 1:{
				cout<<"Logged out"<<endl;
				U[3]->randomDecrease();
				system("clear");
				goto label;
				break;}
			case 2:{
				U[3]->giveOnlineOrder();
				break;}

			case 3:{
				U[3]->displayStock();
				U[3]->orderFood();
			break;}	

			case 4:{
				int cID;
				string comp;
				cout<<"\n\tEnter the complaint ID: ";
				cin>>cID;
				cin.ignore();
				cout<<"\n\tEnter your complaint: ";
				getline(cin, comp);
				
				U[3]->giveComplaint(cID, comp);
				cout<<"\n\033[033mComplaint Registered\033[0m"<<endl;
				break;}

			case 5:{
				cout<<"These are Notifications for Today\n\n";
				U[3]->seeNotifications();
			break;}
			
			case 6:{
				U[3]->sortSearch();
				U[3]->displayStock();
			break;}

			case 7:{
				char item[18];
				cin.ignore();
				cout<<"Enter the item you want to search:";
				cin.getline(item, 18);
				U[3]->searchItem(item);				
			break;}

			case 8:{
				c.seePoints();
			break;}

			default:{
				cout<<"Invalid Choice\n";
			break;}
			}
		}while(choice != 1);
			break;
		default:
			cout<<"Invalid role"<<endl;
			break;
	}
}