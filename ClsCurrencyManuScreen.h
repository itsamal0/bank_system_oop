#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsInputValidate.h"
#include "ClsCurrenciesListScreen.h"
#include <iomanip>
using namespace std;

class ClsCurrencyMenuScreen : protected ClsScreen {

private:
    enum EnCurrenciesMainMenuOptions {
        ListCurrencies = 1, FindCurrency = 2, UpdateCurrencyRate = 3,
        CurrencyCalculator = 4, MainMenu = 5
    };

    static short _readCurrenciesMainMenuOptions() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short choice = ClsInputValidate::readNumberBetween<short>(1, 5, "Enter Number between 1 to 5? ");
        return choice;
    }

    static void _goBackToCurrenciesMenu() {
        cout << "\n\nPress any key to go back to Currencies Menu...";
        system("pause>0");
        showCurrenciesMenu();
    }

    static void _showCurrenciesListScreen() {
        ClsCurrenciesListScreen::showCurrenciesListScreen();
    }

    static void _showFindCurrencyScreen() {
        cout << "\nFind Currency Screen Will Be Here.\n";
    }

    static void _showUpdateCurrencyRateScreen() {
        cout << "\nUpdate Currency Rate Screen Will Be Here.\n";
    }

    static void _showCurrencyCalculatorScreen() {
        cout << "\nCurrency Calculator Screen Will Be Here.\n";
    }

    static void _performCurrenciesMainMenuOptions(EnCurrenciesMainMenuOptions currenciesMainMenuOptions) {
        switch (currenciesMainMenuOptions) {
            case EnCurrenciesMainMenuOptions::ListCurrencies: {
                system("cls");
                _showCurrenciesListScreen();
                _goBackToCurrenciesMenu();
                break;
            }

            case EnCurrenciesMainMenuOptions::FindCurrency: {
                system("cls");
                _showFindCurrencyScreen();
                _goBackToCurrenciesMenu();
                break;
            }

            case EnCurrenciesMainMenuOptions::UpdateCurrencyRate: {
                system("cls");
                _showUpdateCurrencyRateScreen();
                _goBackToCurrenciesMenu();
                break;
            }

            case EnCurrenciesMainMenuOptions::CurrencyCalculator: {
                system("cls");
                _showCurrencyCalculatorScreen();
                _goBackToCurrenciesMenu();
                break;
            }
        }
    }

public:
    static void showCurrenciesMenu() {
        system("cls");
        _drawScreenHeader("    Currency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _performCurrenciesMainMenuOptions((EnCurrenciesMainMenuOptions)_readCurrenciesMainMenuOptions());
    }
};