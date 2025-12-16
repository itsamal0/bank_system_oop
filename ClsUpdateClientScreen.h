#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsBankClient.h"
#include "ClsInputValidate.h"

class ClsUpdateClientScreen : protected ClsScreen {
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
        static void showUpdateClientScreen() {
            _drawScreenHeader("\tUpdate Client Screen");

            string accountNumber = "";

            cout << "\nPlease Enter client Account Number: ";
            accountNumber = ClsInputValidate::readString();
            
            while (!ClsBankClient::isClientExist(accountNumber)) {
                cout << "\nAccount number is not found, choose another one: ";
                accountNumber = ClsInputValidate::readString();
            }

            ClsBankClient Client1 = ClsBankClient::find(accountNumber);
            _printClient(Client1);

            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";

            _readClientInfo(Client1);

            ClsBankClient::enSaveResults saveResult;

            saveResult = Client1.save();

            switch (saveResult) {
                case ClsBankClient::enSaveResults::svSucceeded: {
                    cout << "\nAccount Updated Successfully :-)\n";
                    _printClient(Client1);
                    break;
                }

                case ClsBankClient::enSaveResults::svFaildEmptyObject: {
                    cout << "\nError account was not saved because it's Empty";
                    break;
                }
            }
        }
};