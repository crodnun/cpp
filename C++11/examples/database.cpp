/*
	Description provided by Magdalena Cieniewicz:

	Write a small program in C++ (keep this as simple as possible and provide us with working sourcecode compileable in gcc) 
	which will allow user to:

	1) add a product to a database - kept in .txt file;
	2) remove a product from a database - kept in .txt file;
	3) search for a product based on it's price or name or date added - also kept in .txt file;
	4) view entire product info after providing it's name;
	5) sort products based on their price, name, date added;

	6) Implement a function which will allow user (ask first, input later) 
	to start adding products from this database (kept in .txt file) to an imaginary cart (kep in .txt file) - 
	AND ESTIMATE TOTAL PRIZE FOR CHECKOUT AFTER ADDING PRODUCTS TO DABATASE OR ERASING FEW OF THEM
*/

/******************************* INCLUDES ************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iomanip>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

/******************************* TYPES ***************************************/

//
// Product object: it has a name, a price and timestamp (date it was added)
// 
typedef struct
{
	string name; 
	double price; 
	time_t date;
} Product;


/******************************* GLOBAL VARIABLES *****************************/

// Current database
std::list<Product> database;

// Current cart
std::list<Product> cart;

// Database file name for persistence
// for simplicity we assume that it is at current directory
const char productsDatabasePath[] = "database.txt";

// cart file name for persistence
// for simplicity we assume that it is at current directory
const char cartPath[] = "cart.txt";

/******************************* PROTOTYPES       *****************************/

/******************************* LOCAL FUNCTIONS  *****************************/

//
// Converts timestamp into string and returns it
//
string time2Str(time_t timestamp)
{
	struct tm* tm = localtime(&timestamp);
	char buffer[32]; // temporal buffer
	strftime(buffer, 32, "%Y-%m-%d_%H:%M:%S", tm);
	string result = buffer;

	return result;
}

//
// Converts string date into time_t
//
time_t strToTime(string& date)
{
	int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;

    if (sscanf(date.c_str(), "%4d-%2d-%2d_%2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) {
		struct tm tm = {0};
		tm.tm_year = year - 1900; /* years since 1900 */
		tm.tm_mon = month - 1;
		tm.tm_mday = day;
		tm.tm_hour = hour;
		tm.tm_min = min;
		tm.tm_sec = min;

		return mktime(&tm);
    }

    return 0;
}

//
// Convert date string into time_t value to sort the products by date
// in a portable way (compatible with linux & windows)
// Store result obtained when success into output timestamp field
//
bool validateDate(string& date, time_t* timestamp)
{
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;

	*timestamp = strToTime(date);

	if(*timestamp)
    	return true;
     
    return false;
}

//
// Callback invoked when there is a fatal error in the program
// we show error and exit(-1)
//
void fatalError(string& message)
{
	cout << message << endl;
	exit(-1);
}

//
// This function validates a line read from database file
// Basic validation: number of fields and formats
// When success stores the line info into output product
//
bool validateLine(string& line, Product& outProduct)
{
	string nameField;
	string priceField;
	string dateField;
	string extra;

    // Parse line info
	std::stringstream ss(line);

	ss >> nameField >> priceField >> dateField >> extra;

	// Validate info: basic checkings
	// - Only 3 fields expected
	// - Price is a valid number and > 0
	// - We have a valid date 
	if(nameField.length() && priceField.length() && atof(priceField.c_str())  &&
	   dateField.length() && !extra.length() && validateDate(dateField, &outProduct.date)) 
    {
    	// valid store the fields pending in product (date already stored by validateDate())
    	outProduct.name = nameField;
    	outProduct.price = atof(priceField.c_str());

    	return true;
	} 

	return false;
}

//
// This function reads database (.txt) file or creates a new file
// when none defined.
// The information read is stored into a list of Products
//
void initDB()
{
	ifstream databaseFile(productsDatabasePath, fstream::in | fstream::out | fstream::app);
	string msg;

	if (databaseFile.is_open())
	{
		// Read any information previously stored
		// Each line is a product
		string lineRead;

		// Clean products list and cart
		database.clear();

		while (getline(databaseFile, lineRead))
		{
			//cout << "Line read :" << lineRead << endl;  // debugging

			// Create a new product using info read
			Product dbProduct;

			// Validate line fields first
			if(validateLine(lineRead, dbProduct)) {
				// We can insert product into memory list
				database.push_back(dbProduct);

				//cout << "Product read: " << dbProduct.name << " " << dbProduct.price << " " << time2Str(dbProduct.date) << endl; // debugging

			} else {
				msg = "ERROR: Invalid database line: [" + lineRead + "] (corrupted?)";
				fatalError(msg);
			}
		}

		databaseFile.close();
	}
	else
	{
		// Fatal error => exit
		msg = "ERROR: Unable to open/create file " + string(productsDatabasePath);
		fatalError(msg);
	}
}

//
// This function reads cart (.txt) file or creates one
// The information read is stored into a list of Products
//
void initCart()
{
	ifstream cartFile(cartPath, fstream::in | fstream::out | fstream::app);
	string msg;

	if (cartFile.is_open())
	{
		// Read any information previously stored
		// Each line is a product
		string lineRead;

		// Clean products list and cart
		cart.clear();

		while (getline(cartFile, lineRead))
		{
			//cout << "Line read :" << lineRead << endl;  // debugging

			// Create a new product using info read
			Product dbProduct;

			// Validate line fields first
			if(validateLine(lineRead, dbProduct)) {
				// We can insert product into memory list
				cart.push_back(dbProduct);

				//cout << "Product read: " << dbProduct.name << " " << dbProduct.price << " " << time2Str(dbProduct.date) << endl; // debugging

			} else {
				msg = "ERROR: Invalid cart line: [" + lineRead + "] (corrupted?)";
				fatalError(msg);
			}
		}

		cartFile.close();
	}
	else
	{
		// Fatal error => exit
		msg = "ERROR: Unable to open/create file " + string(cartPath);
		fatalError(msg);
	}
}

//
// displays the content of a list of products
//
void displayProductsList(std::list<Product>& products)
{
	std::list<Product>::iterator it;
	int id = 0;

	cout << endl;
	cout << endl;

    cout << "ID    " << "NAME      " << "PRICE     " << "DATE    " << endl;
    cout  << "----------------------------------------------------"  << endl;
	for (it = products.begin(); it != products.end(); ++it){
		cout << id++ << "    " << it->name << "      " << it->price << "     " << time2Str(it->date) << endl;
	}

	cout << endl;
	cout << endl;
}

//
// displays the DB content
//
void displayDB()
{
	displayProductsList(database);
}

//
// Function to add a new product into DB
//
void addProductToDB()
{
	Product newProduct;
	cout << endl << "Enter name: ";
	cin >> newProduct.name;
	cout << endl << "Enter price: ";
	cin >> newProduct.price;
	// Date is auto-generated
	newProduct.date = time(NULL);

	// Insert it in DB
	database.push_back(newProduct);

	cout << "Product succesfully inserted in DB: " << newProduct.name << " " << newProduct.price << " " << time2Str(newProduct.date) << endl;
}

//
// Function to remove a product from DB
//
void removeProductFromDB()
{
	displayDB();

	cout << endl << "Enter the ID of the product you want to remove: ";	
	int id;
	cin >> id;

	if((id >= 0) && (id < database.size())) {
		std::list<Product>::iterator it = database.begin();
		advance(it, id);
		database.erase(it);
	} else {
		cout << "ERROR: Invalid ID" << endl;	
	}
}

//
// Search a product using a given criteria
//
void showProductInfo()
{
	std::list<Product>::iterator it;
	string userValue;
	time_t userDate;

	cout << " ----------  Search product ---------" << endl;
	cout << "1  - By name" << endl;
	cout << "2  - By price" << endl;
	cout << "3  - By date" << endl;

	cout << "Select an option: " << endl;
	int option;
	cin >> option;

	switch(option) {
		case 1:
			cout << endl << "Enter name: ";
			cin >> userValue;
			it = find_if(database.begin(), database.end(), [userValue] (const Product& s) { return s.name == userValue; });
			if(it != database.end()) {
				cout << endl << "Product info: " << it->name << " " << it->price << " " << time2Str(it->date) << endl << endl;
			} else {
				cout << "WARNING: Product not found for name " << userValue << endl;
			}
			break;
		case 2:
			cout << endl << "Enter price: ";
			cin >> userValue;
			it = find_if(database.begin(), database.end(), [userValue] (const Product& s) { return s.price == atof(userValue.c_str()); });
			if(it != database.end()) {
				cout << endl << "Product info: " << it->name << " " << it->price << " " << time2Str(it->date) << endl << endl;
			} else {
				cout << "WARNING: Product not found for price " << userValue << endl;
			}
			break;
		case 3:
			cout << endl << "Enter date (Format %Y-%m-%d_%H:%M:%S): ";
			cin >> userValue;
			userDate = strToTime(userValue);
			if(userDate) {
				it = find_if(database.begin(), database.end(), [userDate] (const Product& s) { return s.date == userDate; });
				if(it != database.end()) {
					cout << endl << "Product info: " << it->name << " " << it->price << " " << time2Str(it->date) << endl << endl;
				} else {
					cout << "WARNING: Product not found for date " << userValue << endl;
				}
			} else {
				cout << "ERROR: Invalid date value " << userValue << " (search aborted)" << endl;
			}
			break;
		default:  // show menu again
			cout << "ERROR: Invalid option " << option << " (search aborted)" << endl;
			break;
	}
}

//
// Sort products using a given criteria
//
void sortProducts()
{
	std::list<Product>::iterator it;
	// Initialize the temporal list with the content of the database to do the sort there
	std::list<Product> temporalList(database); 
	string userValue;
	time_t userDate;

	cout << " ----------  Sort products ---------" << endl;
	cout << "1  - By name" << endl;
	cout << "2  - By price" << endl;
	cout << "3  - By date" << endl;

	cout << "Select an option: " << endl;
	int option;
	cin >> option;

	switch(option) {
		case 1: // sort by name
			temporalList.sort( []( const Product &a, const Product &b ) { return a.name < b.name; } );
			displayProductsList(temporalList);
			break;
		case 2: // sort by price
			temporalList.sort( []( const Product &a, const Product &b ) { return a.price < b.price; } );
			displayProductsList(temporalList);
			break;
		case 3: // sort by date
			temporalList.sort( []( const Product &a, const Product &b ) { return a.date < b.date; } );
			displayProductsList(temporalList);
			break;
		default:  // show menu again
			cout << "ERROR: Invalid option " << option << " (sort aborted)" << endl;
			break;
	}
}

//
// displays the cart content
//
void displayCart()
{
	std::list<Product>::iterator it;
	int totalPrice = 0;
	int id = 0;

	cout << endl;
	cout << endl;

	cout << "Current cart content" << endl;
	cout  << "----------------------------------------------------"  << endl;
    cout << "ID    " << "NAME      " << "PRICE     " << "DATE    " << endl;
    cout  << "----------------------------------------------------"  << endl;
	for (it = cart.begin(); it != cart.end(); ++it){
		cout << id++ << "    " << it->name << "      " << it->price << "     " << time2Str(it->date) << endl;
		totalPrice += it->price;
	}
	cout  << "----------------------------------------------------"  << endl;
    cout << "TOTAL: " << totalPrice << endl;
    cout  << "----------------------------------------------------"  << endl;

	cout << endl;
	cout << endl;
}

//
// Function to add a new product into cart
//
void addProductToCart()
{
	// Display DB and 
	displayDB();

	cout << endl << "Enter the ID of the product you want to add to cart: ";	
	int id;
	cin >> id;

	if((id >= 0) && (id < database.size())) {
		std::list<Product>::iterator it = database.begin();
		advance(it, id);
		// Insert it in the cart
		cart.push_back(*it);

		cout << "Product succesfully added to cart: " << it->name << " " << it->price << " " << time2Str(it->date) << endl;
	} else {
		cout << "ERROR: Invalid product ID (not inserted in cart)" << endl;	
	}
}

//
// Function to remove a product from cart
//
void removeProductFromCart()
{
	displayCart();

	cout << endl << "Enter the ID of the product you want to remove from cart: ";	
	int id;
	cin >> id;

	if((id >= 0) && (id < cart.size())) {
		std::list<Product>::iterator it = cart.begin();
		advance(it, id);
		cart.erase(it);
	} else {
		cout << "ERROR: Invalid cart product ID" << endl;	
	}
}


//
// displays the options available to the user
//
void showMainMenu()
{
	bool end = false;

	while(!end) {
		cout << " ----------  Database management ---------" << endl;
		cout << "1  - Display database" << endl;
		cout << "2  - Add product to database" << endl;
		cout << "3  - Remove product from database" << endl;
		cout << "4  - Search product" << endl;
		cout << "5  - Sort products" << endl;
		cout << "6  - Add product to cart" << endl;
		cout << "7  - Remove product from cart" << endl;
		cout << "8  - Display cart" << endl;
		cout << "10 - Exit" << endl;

		cout << "Select an option: " << endl;
		int option;
		cin >> option;

		switch(option) {
			case 1:
				displayDB();
				break;
			case 2:
				addProductToDB();
				break;
			case 3:
				removeProductFromDB();
				break;
			case 4:
				showProductInfo();
				break;
			case 5:
				sortProducts();
				break;
			case 6:
				addProductToCart();
				break;
			case 7:
				removeProductFromCart();
				break;
			case 8:
				displayCart();
				break;
			case 10:
				end = true;
				break;
			default:  // show menu again
				break;
		}

		// clear input
		std::cin.clear();
		fflush(stdin);
	}
}

//
// stores the DB content into file
//
void saveDB()
{
	std::list<Product>::iterator it;
	string msg;

	ofstream databaseFile(productsDatabasePath, fstream::in | fstream::out | fstream::trunc);

	if (databaseFile.is_open())
	{
		// Save products into file
		for (it = database.begin(); it != database.end(); ++it){
			databaseFile << it->name << "      " << it->price << "     " << time2Str(it->date) << endl;
		}

		databaseFile.close();
	}
	else
	{
		// Fatal error => exit
		msg = "ERROR: Unable to save file " + string(productsDatabasePath);
		fatalError(msg);
	}
}

//
// stores the Cart content into file
//
void saveCart()
{
	std::list<Product>::iterator it;
	string msg;

	ofstream cartFile(cartPath, fstream::in | fstream::out | fstream::trunc);

	if (cartFile.is_open())
	{
		// Save products into file
		for (it = cart.begin(); it != cart.end(); ++it){
			cartFile << it->name << "      " << it->price << "     " << time2Str(it->date) << endl;
		}

		cartFile.close();
	}
	else
	{
		// Fatal error => exit
		msg = "ERROR: Unable to save file " + string(cartPath);
		fatalError(msg);
	}
}


/******************************* MAIN  *****************************/

//
// Main program function
//
int main(int argc, char** argv)
{
	// Algorithm:
    // 1) Load or create the database file and cart file
	// 2) Show menu for database & cart management


	// 1-1) Load or create empty database file
	initDB();

	// 1-2) load also previous cart content from file
	initCart();


	// 2) Show menu with options
	showMainMenu();


	// 3) Save DB for next round
	saveDB();

	// 4) Save current cart
	saveCart();

	return 0;
}