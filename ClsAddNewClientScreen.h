#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsBankClient.h"
#include "ClsInputValidate.h"
#include <iomanip>

class ClsAddNewClientScreen : protected ClsScreen {
private:
    static void _readClientInfo(ClsBankClient& Client) {
        cout << "\nEnter FirstName: ";
        Client.setFirstName(ClsInputValidate::readString());

        cout << "\nEnter LastName: ";
        Client.setLastName(ClsInputValidate::readString());

        cout << "\nEnter Email: ";
        Client.setEmail(ClsInputValidate::readString());

        cout << "\nEnter Phone: ";
        Client.setPhone(ClsInputValidate::readString());

        cout << "\nEnter PinCode: ";
        Client.setPinCode(ClsInputValidate::readString());

        cout << "\nEnter Account Balance: ";
        Client.setAccountBalance(ClsInputValidate::readNumber<float>());
    }

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

public:

    static void showAddNewClientScreen() {
        _drawScreenHeader("\t  Add New Client Screen");

        string accountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        accountNumber = ClsInputValidate::readString();

        while (ClsBankClient::isClientExist(accountNumber)) {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            accountNumber = ClsInputValidate::readString();
        }

        ClsBankClient NewClient = ClsBankClient::getAddNewClientObject(accountNumber);


        _readClientInfo(NewClient);

        ClsBankClient::enSaveResults saveResult;

        saveResult = NewClient.save();

        switch (saveResult) {
            case  ClsBankClient::enSaveResults::svSucceeded: {
                cout << "\nAccount Addeded Successfully :-)\n";
                _printClient(NewClient);
                break;
            }

            case ClsBankClient::enSaveResults::svFaildEmptyObject: {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
        }
    }    
};

