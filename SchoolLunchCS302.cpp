#include <iostream> // standard in most c++ programmes
#include <math.h> // to use math in the programme
#include <string.h> // to manipulate strings
#include <fstream> // read/write to a .txt file
#include <cstring> // another string manipulator
#include <string> // c++ doesn't like strings so it needs a seperate include
#include <iomanip> // setprecision

using namespace std; // ignores using the std library call e.g std::

enum menuItemID {pizza, fries, burger, pasta, salad, ramen}; // enum to identify the objects

class menuItem {
    public:
        string food;
        double price;
    // menu switch case to iderate through everything individually and intialise each objects string and int
        menuItem(menuItemID id) {
            switch(id) {   
                case pizza:
                    food = "Pepperoni Pizza";
                    price = 6.99;
                    break;
                case fries:
                    food = "Fries";
                    price = 3.55;
                    break;
                case burger:
                    food = "Chicken Burger";
                    price = 7.99;
                    break;
                case pasta:
                    food = "Alfredo Pasta";
                    price = 6.55;
                    break;
                case salad:
                    food = "Caesar Salad";
                    price = 5.55;
                    break;
                case ramen:
                    food = "Miso Ramen";
                    price = 4.99;
                    break;
            };
        };
};

class menu {
    public: // pointer class menu for easier handling and printing
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
    int loginFailCount = 0;
    bool validUsername = false;
    waitForUsername:
        // if statement to count failed logins, after 3 attempts it will close the programme
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
    // Use a while loop together with the getline() function to read the file line by line
    while (getline(dataStream, line)) {
        char* lineChunk = strtok(line.data(), " "); // strtok is a delimiter it ignores spaces or " " in .txt file when reading inline.
        validUsername = false;
        while (lineChunk != NULL) {

            // checking if username is valid to proceed to password input
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
                    loginFailCount++;
                    goto waitForPassword;
                };
            };
            // validates username
            string s(lineChunk);
            lineChunk = strtok(NULL, " ");
            if(s == inputUsername) {
                validUsername = true;
            };
        };
    };
    cout << "Username does not exist" << endl;
    loginFailCount++;
    goto waitForUsername;
    // handling case if file closes unexpectedly
    dataStream.close();
    cout << "error 404 not found";
    return;
};

void newUser() {
    std::ofstream newUserOut;
    string newUserInput, newUserPassword;

    cout << "Please input your new username: ";
    cin >> newUserInput;
    // open .txt file to write on
    newUserOut.open("users.txt", std::fstream::app);

    if (newUserOut.is_open()) {
    newUserOut << "\n" << newUserInput << " ";
    // input nesting for password
    cout << "Please input your new password: ";
    cin >> newUserPassword;
    newUserOut << newUserPassword;

    newUserOut.close();

    cout << "Successfully created new user" << endl;
    } else {
        cout << "unable to open file, try turning off your antivirus!"; // if antivirus is on it will not permit you to write on a local .txt file
        exit(0);
    };
};

int main() {
    menu myMenu = menu(menuItem(pizza), menuItem(fries), menuItem(burger), menuItem(pasta), menuItem(salad), menuItem(ramen));
    char orderMenuInput;
    char* mainMenuConvert;
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
    // converts string to char for switch case
    mainMenuConvert = mainMenuInput.data();
    switch(toupper(*mainMenuConvert)) {
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

            goto mainLogStart; // c++ is a linear language so this helps it not be
            break;
    };

        while(isAddingItems) {
            std::cout << "Enter the Item letter to order\n" 
            << "A.) " << myMenu.pizza->food << " $" << myMenu.pizza->price << endl
            << "B.) " << myMenu.fries->food << " $" << myMenu.fries->price << endl
            << "C.) " << myMenu.burger->food << " $" << myMenu.burger->price << endl
            << "D.) " << myMenu.pasta->food << " $" << myMenu.pasta->price << endl
            << "E.) " << myMenu.salad->food << " $" << myMenu.salad->price << endl
            << "F.) " << myMenu.ramen->food << " $" << myMenu.ramen->price << endl
            << "your choice : ";

            std::cin >> orderMenuInput;
            // switch case for menu options
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
            // validity for input option
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
                
                end:;
            };

        };

        std::cout << "Thanks for your order!" 
            << endl 
            <<"your total to pay is $" 
            << totalPrice 
            << endl;
        

            bool applyDiscount = false;
            string discountCode;
            double discountPrice = 0;
            const double STAFF = 0.9;
            const double STUDENT = 0.95;

            std::cout << "Would you like to apply a discount code? Y/N : ";
            char applyDiscountInput;
            std::cin >> applyDiscountInput;

            if (toupper(applyDiscountInput) == 'Y'){
                applyDiscount = true;

                std::cout << "Enter discount code: ";
                std::cin >> discountCode;      
                };

                // Check if the discount code is vaild
                if (applyDiscount && (discountCode == "STAFF" || discountCode == "STUDENT")) {
                    //Apply the appropriate discount
                    if (discountCode == "STAFF") {
                        discountPrice = totalPrice * STAFF;
                    } else if (discountCode == "STUDENT") {
                        discountPrice = totalPrice * STUDENT;
                    };
                
                    // display the new total 
                    std::cout << "Discount applied, thanks! Your new total is $" 
                            << fixed
                            << setprecision(2)
                            << discountPrice
                            << ", and you saved $" 
                            << totalPrice - discountPrice
                            << "!"
                            << endl;
                } else if (applyDiscount) { 
                    // the discount code is invalid
                    std::cout << "Invalid discount code" << endl;
                
                } else {
                    // no discount code was applied
                    std::cout << "No discount code applied, your total is $ " << totalPrice << endl;
                };
                // payment options 
                cout << "Please select your payment method:" << endl
                << "1. Cash" << endl
                << "2. Debit Card" << endl
                << "3. On Account" << endl
                << "Enter your choice: " ;
                
                int paymentMethod = 0;
                cin >> paymentMethod;

                switch (paymentMethod) {
                    case 1:
                        cout << "Please Pay $" << fixed << setprecision(1) << discountPrice << "0  in cash." << endl;
                        break;
                    case 2:
                        cout << "Please Pay $" << fixed << setprecision(2) << discountPrice << "  Debit Card." << endl;
                        break;
                    case 3:
                        cout << "Please Pay $" << fixed << setprecision(2) << discountPrice << "  On Account." << endl;
                        break;
                    default:
                        cout << "that choice is invalid!";
                        return 0;
                };

    return 0;
};