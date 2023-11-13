#include <iostream>
#include <math.h>
#include <string.h>
#include <array>

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

bool login() {
    bool loggedIn;
        
    // Map example

    // #include <iostream>
    // #include <map>

    // using namespace std;

    // int main() {
    // //initialising the map
    // map <string, string> mmap;

    // //inserting some values
    // mmap.insert({"jontysUsername", "jontysPassword"});
    // mmap.insert({"joshsUserName", "joshsPassword"});
    // mmap.insert({"michaelsUserName", "michaelsPassword"});

    // if (mmap.find("jontysUsername") == whateverthepersonputforthepassword) {
    //     successful login
    // } else {
    //     wrong password
    // }

    // //displaying the contents
    // for (auto itr = mmap.begin(); itr != mmap.end(); ++itr) {
    //     cout << itr->first << ": " << itr->second << endl;
    // }

    // return 0;
    // }

    return loggedIn;
}

  const double STAFF = 0.10;
  const double STUDENT = 0.05;

int main() {
    menu myMenu = menu(menuItem(pizza), menuItem(fries), menuItem(burger), menuItem(pasta), menuItem(salad), menuItem(ramen));
    char menuInput;
    double totalPrice = 0;
    bool invalid = true;
    bool isAddingItems = true;
    char addItem;

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
                cout << "This is not a valid answer" << endl;
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

        cout << "Would you like to apply a discount code? Y/N : ";
        char applyDiscountInput;
        cin >> applyDiscountInput;

        if (toupper(applyDiscountInput) == 'Y'){
            applyDiscount = true;

            cout << "Enter discount code: ";
             cin >> discountCode;      
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
                cout << "Discount applied, thanks! Your new total is $" << totalPrice << ", and you saved $ !" << endl;
             } else if (applyDiscount) { 
                // the discount code is invalid
                cout << "Invalid discount code" << endl;
            
             } else {
                // no discount code was applied
                cout << "No discount code applied, your total is $ " << totalPrice << endl;
             }
        

    return 0;
}