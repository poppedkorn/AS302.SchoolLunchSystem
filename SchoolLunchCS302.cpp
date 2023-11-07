#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;

struct menu {
    public:
        string food;
        double price;
};

int main() {
    menu pizza, fries, burger, pasta, salad, ramen;
        pizza.food = "Pepperoni Pizza";
        pizza.price = 6.99;
        fries.food = "Fries";
        fries.price = 2.50;
        burger.food = "Chicken Burger";
        burger.price = 7.99;
        pasta.food = "Alfredo Pasta";
        pasta.price = 6.50;
        salad.food = "Ceasar Salad";
        salad.price = 5.50;
        ramen.food = "Miso Ramen";
        ramen.price = 4.99;
    char menuInput;
    double totalPrice = 0;
    bool isValid = false;
    char addItem;


    while(true) {
        cout << "Enter the Item letter to order\n" 
        << "A.) " << pizza.food << endl
        << "B.) " << fries.food << endl
        << "C.) " << burger.food << endl
        << "D.) " << pasta.food << endl
        << "E.) " << salad.food << endl
        << "F.) " << ramen.food << endl
        << "your choice : ";

        cin >> menuInput;

        switch(toupper(menuInput)) {
            case 'A':
                totalPrice = totalPrice + pizza.price;
                break;
            case 'B':
                totalPrice = totalPrice + fries.price;
                break;
            case 'C':
                totalPrice = totalPrice + burger.price;
                break;
            case 'D':
                totalPrice = totalPrice + pasta.price;
                break;
            case 'E':
                totalPrice = totalPrice + salad.price;
                break;
            case 'F':
                totalPrice = totalPrice + ramen.price;
                break;
            default:
                cout << "this is not a valid answer! ";

        };

        cout << "your total to pay is $" 
            << totalPrice 
            << endl
            << "would you like to add another item? Y/N :";

        cin >> addItem; 

        if (addItem = 'Y') {
            continue;
        } else if (addItem = 'N') {
            break;
        } else {
            cout << "this is not a valid answer";
        };
    };

    return 0;
}