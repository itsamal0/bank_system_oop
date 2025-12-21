#include <iostream>
#include "ClsCurrency.h"
using namespace std;

void printCurrencyCard(ClsCurrency currency) {
    cout << "\nCurrency Card:\n";
    cout << "_____________________________\n";
    cout << "\nCountry    : " << currency.country();
    cout << "\nCode       : " << currency.currencyCode();
    cout << "\nName       : " << currency.currencyName();
    cout << "\nRate(1$) = : " << currency.rate();
    cout << "\n_____________________________\n";
}

int main() {
    ClsCurrency currency1 = ClsCurrency::findByCode("jod");

    if (currency1.isEmpty()) {
        cout << "\nCurrency Is Not Found!\n";
    } 
    else {
        printCurrencyCard(currency1);
    }

    ClsCurrency currency2 = ClsCurrency::findByCountry("Egypt");

    if (currency2.isEmpty()) {
        cout << "\nCurrency Is Not Found!\n";
    } 
    else {
        printCurrencyCard(currency2);
    }

    cout << "\nCurrency1 after updating Rate:\n";
    currency1.updateRate(0.75);
    printCurrencyCard(currency1);

    system("pause>0");
    return 0;
}