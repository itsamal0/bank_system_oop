#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsCurrency.h"
#include "ClsInputValidate.h"
using namespace std;

class ClsFindCurrencyScreen : protected ClsScreen {

private:
    static void _printCurrency(ClsCurrency currency) {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << currency.country();
        cout << "\nCode       : " << currency.currencyCode();
        cout << "\nName       : " << currency.currencyName();
        cout << "\nRate(1$) = : " << currency.rate();
        cout << "\n_____________________________\n";
    }

    static void _showResults(ClsCurrency currency) {
        if (!currency.isEmpty()) {
            cout << "\nCurrency Found :-)\n";
            _printCurrency(currency);
        } else {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }

public:
    static void showFindCurrencyScreen() {
        _drawScreenHeader("\t  Find Currency Screen");

        cout << "\nFind By: [1] Code or [2] Country ? ";
        short answer = ClsInputValidate::readNumberBetween<short>(1, 2, "Please enter 1 or 2: ");

        if (answer == 1) {
            string currencyCode;
            cout << "\nPlease Enter Currency Code: ";
            currencyCode = ClsInputValidate::readString();
            ClsCurrency currency = ClsCurrency::findByCode(currencyCode);
            _showResults(currency);
        } else {
            string country;
            cout << "\nPlease Enter Country Name: ";
            country = ClsInputValidate::readString();
            ClsCurrency currency = ClsCurrency::findByCountry(country);
            _showResults(currency);
        }
    }
};