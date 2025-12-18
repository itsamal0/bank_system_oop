#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsBankClient.h"
#include "ClsInputValidate.h"

class ClsFindClientScreen : protected ClsScreen {
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

    public: 
        static void showFindClientScreen() {

            if (!checkAccessRights(ClsUser::EnPermissions::pFindClient)) {
                return;
            }

            _drawScreenHeader("\tFind Client Screen");

            string accountNumber;
            cout << "\nPlease Enter Account Number: ";
            accountNumber = ClsInputValidate::readString();

            while (!ClsBankClient::isClientExist(accountNumber)) {
                cout << "\nAccount number is not found, choose another one: ";
                accountNumber = ClsInputValidate::readString();
            }

            ClsBankClient Client1 = ClsBankClient::find(accountNumber);

            if (!Client1.isEmpty())
                cout << "\nClient Found :-)\n";
            
            else
                cout << "\nClient Was not Found :-(\n";

            _printClient(Client1);
        }
};