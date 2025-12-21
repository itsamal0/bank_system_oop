#pragma once
#include <iostream>
#include "..\ClsScreen.h"
#include "..\..\Core\ClsPerson.h"
#include "..\..\Core\ClsBankClient.h"
#include "..\..\Lib\ClsInputValidate.h"

class ClsTransferScreen : protected ClsScreen {

private:
    static void _printClient(ClsBankClient client) {
        cout << "\nClient Card:";
        cout << "\n___________________\n";
        cout << "\nFull Name   : " << client.fullName();
        cout << "\nAcc. Number : " << client.accountNumber();
        cout << "\nBalance     : " << client.getAccountBalance();
        cout << "\n___________________\n";
    }

    static string _readAccountNumber(string message) {
        string accountNumber;
        cout << message;
        accountNumber = ClsInputValidate::readString();
        while (!ClsBankClient::isClientExist(accountNumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            accountNumber = ClsInputValidate::readString();
        }
        return accountNumber;
    }

    static float _readAmount(ClsBankClient sourceClient) {
        float amount;
        cout << "\nEnter Transfer Amount? ";
        amount = ClsInputValidate::readNumber<float>();

        while (amount > sourceClient.getAccountBalance()) {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            amount = ClsInputValidate::readNumber<float>();
        }
        return amount;
    }

public:

    static void showTransferScreen() {
        _drawScreenHeader("\tTransfer Screen");

        ClsBankClient sourceClient = ClsBankClient::find(_readAccountNumber("\nPlease Enter Account Number to Transfer From: "));
        _printClient(sourceClient);

        ClsBankClient destinationClient = ClsBankClient::find(_readAccountNumber("\nPlease Enter Account Number to Transfer To: "));
        _printClient(destinationClient);

        float amount = _readAmount(sourceClient);

        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char answer = 'n';
        cin >> answer;

        if (answer == 'Y' || answer == 'y') {
            if (sourceClient.transfer(amount, destinationClient, CurrentUser.getUserName())) {
                cout << "\nTransfer done successfully\n";
            } 
            else {
                cout << "\nTransfer Failed \n";
            }
        }

        _printClient(sourceClient);
        _printClient(destinationClient);
    }
};