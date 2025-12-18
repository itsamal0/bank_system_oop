#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsPerson.h"
#include "ClsBankClient.h"
#include "ClsInputValidate.h"

class ClsDeleteClientScreen : protected ClsScreen {
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
        static void showDeleteClientScreen() {

            if (!checkAccessRights(ClsUser::EnPermissions::pDeleteClient)) {
                return;
            }
            
            _drawScreenHeader("\tDelete Client Screen");
            
            string accountNumber = "";

            cout << "\nPlease Enter Account Number: ";
            accountNumber = ClsInputValidate::readString();

            while (!ClsBankClient::isClientExist(accountNumber)) {
                cout << "\nAccount number is not found, choose another one: ";
                accountNumber = ClsInputValidate::readString();
            }

            ClsBankClient Client1 = ClsBankClient::find(accountNumber);
            _printClient(Client1);

            cout << "\nAre you sure you want to delete this client y/n? ";
            
            char answer = 'n';
            cin >> answer;

            if (answer == 'y' || answer == 'Y') {
                if (Client1.markForDelete()) {
                    cout << "\nClient Deleted Successfully :-)\n";
                    _printClient(Client1);
                }

                else {
                    cout << "\nError Client Was not Deleted\n";
                }
            }
    }
};