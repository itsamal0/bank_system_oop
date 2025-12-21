#pragma once
#include <iostream>
#include "..\ClsScreen.h"
#include "..\..\Core\ClsBankClient.h"
#include "..\..\Lib\ClsInputValidate.h"

class ClsDepositScreen : protected ClsScreen {
private:
    static void _printClient(ClsBankClient Client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.getFirstName();
        cout << "\nLastName    : " << Client.getLastName();
        cout << "\nFull Name   : " << Client.fullName();
        cout << "\nEmail       : " << Client.getEmail();
        cout << "\nPhone       : " << Client.getPhone();
        cout << "\nAcc. Number : " << Client.accountNumber();
        cout << "\nPassword    : " << Client.getPinCode();
        cout << "\nBalance     : " << Client.getAccountBalance();
        cout << "\n___________________\n";
    }

    static string _readAccountNumber() {
        string accountNumber = "";
        cout << "\nPlease enter accountNumber? ";
        cin >> accountNumber;
        return accountNumber;
    }

public:
    static void showDepositScreen() {
        _drawScreenHeader("\t   Deposit Screen");

        string accountNumber = _readAccountNumber();

        while (!ClsBankClient::isClientExist(accountNumber)) {
            cout << "\nClient with [" << accountNumber << "] does not exist.\n";
            accountNumber = _readAccountNumber();
        }

        ClsBankClient Client1 = ClsBankClient::find(accountNumber);
        _printClient(Client1);

        double amount = 0;
        cout << "\nPlease enter deposit amount? ";
        amount = ClsInputValidate::readNumber<double>();

        cout << "\nAre you sure you want to perform this transaction? ";
        char answer = 'n';
        cin >> answer;

        if (answer == 'Y' || answer == 'y') {
            Client1.deposit(amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance Is: " << Client1.getAccountBalance();

        }

        else
            cout << "\nOperation was cancelled.\n";

    }

};