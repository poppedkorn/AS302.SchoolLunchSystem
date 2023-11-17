#include <iostream>
#include <math.h>
#include <string.h>
#include <array>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>

using namespace std;

enum menuItemID {pizza, fries, burger, pasta, salad, ramen};

class menuItem {
    public:
        string food;
        double price;

        menuItem(menuItemID id) {
            switch(id) {   
                case pizza:
                    food = "Pepperoni Pizza";
                    price = 6.99;
                    break;
                case fries:
                    food = "Fries";
                    price = 3.50;
                    break;
                case burger:
                    food = "Chicken Burger";
                    price = 7.99;
                    break;
                case pasta:
                    food = "Alfredo Pasta";
                    price = 6.50;
                    break;
                case salad:
                    food = "Caesar Salad";
                    price = 5.50;
                    break;
                case ramen:
                    food = "Miso Ramen";
                    price = 4.99;
                    break;
            };
        };
};

class menu {
    public: 
        menuItem* pizza;
        menuItem* fries;
        menuItem* burger;
        menuItem* pasta;
        menuItem* salad;
        menuItem* ramen;

        menu(menuItem pi, menuItem f, menuItem b, menuItem pa, menuItem s, menuItem r) {
            pizza = &pi;
            fries = &f;
            burger = &b;
            pasta = &pa;
            salad = &s;
            ramen = &r;
        };
};

void login() {
    // text string, which is used to output the text file
    string line;
    string inputUsername = "username";
    string inputPassword = "password";
    int loginFailCount = 0;
    bool validUsername = false;
    waitForUsername:
    if (loginFailCount == 3) {
        cout << "you have entered the username/password wrong too many times, the programme is now quitting..."
            << endl
            << "goodbye!";

            exit(0);
    };
    // Read from the text file
    ifstream dataStream("users.txt");

    cout << "Username: ";
    cin >> inputUsername;
    // while loop used together with the getline() function to read the file line by line
    while (getline(dataStream, line)) {
        char* lineChunk = strtok(line.data(), " ");
        validUsername = false;
        while (lineChunk != NULL) {
            // checking validity of username to go into the password input
            if(validUsername) {
                waitForPassword:
                cout << "Password: ";
                cin >> inputPassword;
                // the strtok value and input value of the password check if they match
                if(lineChunk == inputPassword) {
                    cout << "Sign in successful " << endl;
                    dataStream.close();
                    return;
                } else {
                    cout << "Wrong password" << endl;
                    loginFailCount++;
                    goto waitForPassword;
                };
            };
            
            string s(lineChunk);
            lineChunk = strtok(NULL, " ");
            if(s == inputUsername) {
                validUsername = true;
            };
        };
    };
    // failsafe handling for uncommon cases of breaking out of the while loop
    cout << "Username does not exist" << endl;
    loginFailCount++;
    goto waitForUsername; // goto is a cheat way of dealing with a broken loop
 
    dataStream.close();
    cout << "error 404. file not found";
    return;
};

void newUser() {

};

int main() {
    menu myMenu = menu(menuItem(pizza), menuItem(fries), menuItem(burger), menuItem(pasta), menuItem(salad), menuItem(ramen));
    char orderMenuInput;
    char mainMenuInput;
    double totalPrice = 0;
    bool invalid = true;
    bool isAddingItems = true;
    char addItem;


    cout << "hello, welcome to the school lunch ordering system!"
        << endl
        << "to login to a previous user press L"
        << endl
        << "to create a new user press N"
        << endl
        << "to quit the programme press Q"
        << endl
        << "your choice: ";
    cin >> mainMenuInput;

    switch(toupper(mainMenuInput)) {
        case 'L': 
            login();
            break;
        case 'Q':
            cout << "you are now quitting the programme..."
                << endl
                << "goodbye";

                return -1;
        case 'N':
            // newUser();
            break;
    }
    // login();

        while(isAddingItems) {
            std::cout << "Enter the Item letter to order\n" 
            << "A.) " << myMenu.pizza->food << endl
            << "B.) " << myMenu.fries->food << endl
            << "C.) " << myMenu.burger->food << endl
            << "D.) " << myMenu.pasta->food << endl
            << "E.) " << myMenu.salad->food << endl
            << "F.) " << myMenu.ramen->food << endl
            << "your choice : ";

            std::cin >> orderMenuInput;

            switch(toupper(orderMenuInput)) {
                case 'A':
                    totalPrice = totalPrice + myMenu.pizza->price;
                    break;
                case 'B':
                    totalPrice = totalPrice + myMenu.fries->price;
                    break;
                case 'C':
                    totalPrice = totalPrice + myMenu.burger->price;
                    break;
                case 'D':
                    totalPrice = totalPrice + myMenu.pasta->price;
                    break;
                case 'E':
                    totalPrice = totalPrice + myMenu.salad->price;
                    break;
                case 'F':
                    totalPrice = totalPrice + myMenu.ramen->price;
                    break;
                default:
                    std::cout << "This is not a valid answer! " << endl;
            };

            invalid = true;
            while(invalid) {
                std::cout << "Your total to pay is $" 
                    << totalPrice 
                    << endl
                    << "Would you like to add another item? Y/N :";

                std::cin >> addItem; 

                if (addItem == ('Y' | 'y')) {
                    invalid = false;
                    goto end;
                } else if (addItem == ('N' | 'n')) {
                    invalid = false;
                    isAddingItems = false;
                } else {
                    std::cout << "This is not a valid answer" << endl;
                };
                
                end: NULL;
            };

        };

        std::cout << "Thanks for your order!" 
            << endl 
            <<"your total to pay is $" 
            << totalPrice 
            << endl;
        
            bool applyDiscount = false;
            string discountCode;
            const double STAFF = 0.9;
            const double STUDENT = 0.95;
            double discountPrice = 0;

            std::cout << "Would you like to apply a discount code? Y/N : ";
            char applyDiscountInput;
            std::cin >> applyDiscountInput;

            if (toupper(applyDiscountInput) == 'Y'){
                applyDiscount = true;

                std::cout << "Enter discount code: ";
                std::cin >> discountCode;     
                }

                // Check if the discount code is vaild
                if (applyDiscount && (discountCode == "STAFF" || discountCode == "STUDENT")) {
                    //Apply the appropriate discount
                    if (discountCode == "STAFF") {
                        discountPrice = totalPrice * STAFF;
                    } if (discountCode == "STUDENT"); {
                        discountPrice = totalPrice * STUDENT;
                    }

                    // display the new total 
                    double priceDifference = totalPrice - discountPrice;
                    std::cout << "Discount applied, thanks! Your new total is $" 
                            << discountPrice 
                            << ", and you saved $" 
                            << priceDifference  
                            << endl;
                } else if (applyDiscount) { 
                    // the discount code is invalid
                    std::cout << "Invalid discount code" << endl;
                
                } else {
                    // no discount code was applied
                    std::cout << "No discount code applied, your total is $" << totalPrice << endl;
                }

    return 0;
}