#pragma once
#include <iostream>
#include "..\ClsScreen.h"
#include "..\..\Core\ClsCurrency.h"
#include "..\..\Lib\ClsInputValidate.h"
using namespace std;

class ClsUpdateCurrencyRateScreen : protected ClsScreen {

private:
    static float _readRate() {
        cout << "\nEnter New Rate: ";
        float newRate = ClsInputValidate::readNumber<float>();
        return newRate;
    }

    static void _printCurrency(ClsCurrency currency) {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << currency.country();
        cout << "\nCode       : " << currency.currencyCode();
        cout << "\nName       : " << currency.currencyName();
        cout << "\nRate(1$) = : " << currency.rate();
        cout << "\n_____________________________\n";
    }

public:
    static void showUpdateCurrencyRateScreen() {
        _drawScreenHeader("\tUpdate Currency Screen");

        string currencyCode = "";
        cout << "\nPlease Enter Currency Code: ";
        currencyCode = ClsInputValidate::readString();

        while (!ClsCurrency::isCurrencyExist(currencyCode)) {
            cout << "\nCurrency is not found, choose another one: ";
            currencyCode = ClsInputValidate::readString();
        }

        ClsCurrency currency = ClsCurrency::findByCode(currencyCode);
        _printCurrency(currency);

        cout << "\nAre you sure you want to update the rate of this Currency y/n? ";

        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            currency.updateRate(_readRate());

            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _printCurrency(currency);
        }
    }
};