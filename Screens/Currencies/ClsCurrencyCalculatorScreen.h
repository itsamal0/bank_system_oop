#pragma once

#include <iostream>
#include "..\ClsScreen.h"
#include "..\..\Core\ClsCurrency.h"
#include "..\..\Lib\ClsInputValidate.h"

using namespace std;

class ClsCurrencyCalculatorScreen : protected ClsScreen {

private:
    static float _readAmount() {
        cout << "\nEnter Amount to Exchange: ";
        float amount = ClsInputValidate::readNumber<float>();
        return amount;
    }

    static ClsCurrency _getCurrency(string message) {
        string currencyCode;
        cout << message;
        currencyCode = ClsInputValidate::readString();

        while (!ClsCurrency::isCurrencyExist(currencyCode)) {
            cout << "\nCurrency is not found, choose another one: ";
            currencyCode = ClsInputValidate::readString();
        }

        return ClsCurrency::findByCode(currencyCode);
    }

    static void _printCurrencyCard(ClsCurrency currency, string title = "Currency Card:") {
        cout << "\n" << title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry        : " << currency.country();
        cout << "\nCode           : " << currency.currencyCode();
        cout << "\nName           : " << currency.currencyName();
        cout << "\nRate(1$) =     : " << currency.rate();
        cout << "_____________________________\n";
    }

    static void _printCalculationsResults(float amount, ClsCurrency currencyFrom, ClsCurrency currencyTo) {
        _printCurrencyCard(currencyFrom, "Convert From:");

        float amountInUSD = amount / currencyFrom.rate();

        cout << "\n" << amount << " " << currencyFrom.currencyCode()
            << " = " << amountInUSD << " USD\n";

        if (currencyTo.currencyCode() != "USD") {
            cout << "\nConverting from USD to:\n";
            _printCurrencyCard(currencyTo, "To:");

            float finalResult = currencyFrom.convertTo(amount, currencyTo);

            cout << amount << " " << currencyFrom.currencyCode()
                << " = " << finalResult << " " << currencyTo.currencyCode();
        }
    }

public:
    static void showCurrencyCalculatorScreen() {
        char continueCalculating = 'y';

        while (continueCalculating == 'y' || continueCalculating == 'Y') {
            system("cls");
            _drawScreenHeader("\tCurrency Calculator Screen");

            ClsCurrency currencyFrom = _getCurrency("\nPlease Enter Currency1 Code: ");
            ClsCurrency currencyTo = _getCurrency("\nPlease Enter Currency2 Code: ");
            float amount = _readAmount();

            _printCalculationsResults(amount, currencyFrom, currencyTo);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> continueCalculating;
        }
    }
};