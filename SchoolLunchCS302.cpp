#include <iostream>
#include <math.h>
#include <string.h>
#include <array>
#include <fstream>
#include <cstring>
#include <string>

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

    // Create a text string, which is used to output the text file
    string line;
    string inputUsername = "username";
    string inputPassword = "password";
    bool validUsername = false;
    waitForUsername:
    // Read from the text file
    ifstream dataStream("users.txt");

    cout << "Username: ";
    cin >> inputUsername;
    // Use a while loop together with the getline() function to read the file line by line
    while (getline(dataStream, line)) {
        char* lineChunk = strtok(line.data(), " ");
        validUsername = false;
        while (lineChunk != NULL) {

            if(validUsername) {
                waitForPassword:
                cout << "Password: ";
                cin >> inputPassword;
                if(lineChunk == inputPassword) {
                    cout << "Sign in successful " << endl;
                    dataStream.close();
                    return;
                } else {
                    cout << "Wrong password" << endl;
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
    cout << "Username does not exist" << endl;
    goto waitForUsername;
 
    dataStream.close();
    cout << "wtf bro?";
    return;
};

void newUser() {
    std::ofstream newUserOut;
    string newUserInput, newUserPassword;

    cout << "Please input your new username: ";
    cin >> newUserInput;

    newUserOut.open("users.txt", std::fstream::app);

    if (newUserOut.is_open()) {
    newUserOut << "\n" << newUserInput << " ";

    cout << "Please input your new password: ";
    cin >> newUserPassword;
    newUserOut << newUserPassword;

    newUserOut.close();

    cout << "Successfully created new user" << endl;
    } else {
        cout << "unable to open file, try turning off your antivirus!";
        exit(0);
    };


};

int main() {
    menu myMenu = menu(menuItem(pizza), menuItem(fries), menuItem(burger), menuItem(pasta), menuItem(salad), menuItem(ramen));
    char orderMenuInput;
    char* test;
    string mainMenuInput;
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
    mainLogStart:

    // reads a whole line
    if (!getline(cin, mainMenuInput)) {
        cout << "Error or end-of-file\n";
    };

    test = mainMenuInput.data();
    switch(toupper(*test)) {
        case 'L': 
            login();
            break;
        case 'Q':
            cout << "you are now quitting the programme..."
                << endl
                << "goodbye";

                return -1;
        case 'N':
            newUser();
            break;
        default :
            cout << "this is not a valid answer" 
                << endl
                << "your choice: ";

            goto mainLogStart;
            break;
    };

        while(isAddingItems) {
            std::cout << "Enter the Item letter to order\n" 
            << "A.) " << myMenu.pizza->food << endl
            << "B.) " << myMenu.fries->food << endl
            << "C.) " << myMenu.burger->food << endl
            << "D.) " << myMenu.pasta->food << endl
            << "E.) " << myMenu.salad->food << endl
            << "F.) " << myMenu.ramen->food << endl
            << "your choice : ";

            std::cin >> menuInput;

            switch(toupper(menuInput)) {
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
            const double STAFF = 0.10;
            const double STUDENT = 0.05;

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
                        totalPrice *= (1.0 - STAFF);
                    } else if (discountCode == "STUDENT"); {
                        totalPrice *= (1.0 - STUDENT);
                    }
                
                    // display the new total 
                    std::cout << "Discount applied, thanks! Your new total is $" << totalPrice << ", and you saved $ !" << endl;
                } else if (applyDiscount) { 
                    // the discount code is invalid
                    std::cout << "Invalid discount code" << endl;
                
                } else {
                    // no discount code was applied
                    std::cout << "No discount code applied, your total is $ " << totalPrice << endl;
                // payment options 
                cout << "Please select your payment method:" << endl
                << "1. Cash" << endl
                << "2. Debit Card" << endl
                << "3. On Account" << endl
                << "Enter your choice: " ;

                int paymentMethod;
                cin >> paymentMethod;

                switch (paymentMethod) {
                    case 1:
                    cout << "Please Pay $" << discountPrice << "  in cash." << endl;
                    break;
                }

    return 0;
}