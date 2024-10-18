Café Digital System (CDS)

Project Overview:

This project is an implementation of a Café Digital System (CDS) using Object-Oriented Programming (OOP) concepts in C++. The system supports secure login for multiple users, real-time stock management, employee sales tracking, and customer loyalty points. The program also includes file handling, encryption for password storage, and various functionalities to aid café staff and administration.

Key Features:

	1.	Secure Login System:
	•	User login with password encryption.
	•	Role-based access for admin and employees.
	2.	Stock Management:
	•	Add, remove, search, and update stock items.
	•	Notifications for low stock items and auto-purchase suggestions.
	3.	Order Handling:
	•	Employees can take and process customer orders.
	•	Supports both online and offline order tracking.
	4.	Sales Tracking:
	•	Employees’ sales are tracked and stored for performance monitoring.
	5.	Customer Loyalty Points:
	•	Customers earn points on their purchases.
	•	Points can be redeemed for discounts on future orders.
	6.	Complaint System:
	•	Staff and customers can submit and track complaints.
	7.	File Handling:
	•	Save all stock and user credentials securely using text and binary file storage.
	8.	Encryption:
	•	Passwords are securely stored using encryption techniques.

Classes and Modules:

The system is built around several classes that interact to manage different aspects of the café system:

	•	User (Base Class): Manages user roles and login functionality.
	•	Admin: Has additional privileges to manage stock and employees.
	•	Employee: Manages order processing, stock search, and sales tracking.
	•	Customer: Earns points for purchases, which can be redeemed for discounts.
	•	Stock: Handles all stock-related information (e.g., item name, quantity, price).
	•	Notification: Generates alerts for low stock, order updates, etc.

How to Run:

	1.	Clone this repository: git clone https://github.com/yourusername/CDS.git
	2.	Compile the code: g++ -o cafe_system main.cpp <other .cpp files>
	3.	Run the executable: ./cafe_system
Future Improvements:

	•	Implement GUI for better user interaction.
	•	Integrate online payment methods.
	•	Expand notifications for better user experience.
	•	Introduce more detailed sales and points analytics for employees and customers.
