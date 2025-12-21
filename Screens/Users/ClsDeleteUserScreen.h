#pragma once
#include <iostream>
#include "..\ClsScreen.h"
#include "..\..\Core\ClsUser.h"
#include "..\..\Lib\ClsInputValidate.h"
#include <iomanip>

class ClsDeleteUserScreen : protected ClsScreen {

private:
    static void _printUser(ClsUser User) {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.getFirstName();
        cout << "\nLastName    : " << User.getLastName();
        cout << "\nFull Name   : " << User.fullName();
        cout << "\nEmail       : " << User.getEmail();
        cout << "\nPhone       : " << User.getPhone();
        cout << "\nUser Name   : " << User.getUserName();
        cout << "\nPassword    : " << User.getPassword();
        cout << "\nPermissions : " << User.getPermissions();
        cout << "\n___________________\n";
    }

public:
    static void showDeleteUserScreen() {
        _drawScreenHeader("\tDelete User Screen");

        string userName = "";

        cout << "\nPlease Enter UserName: ";
        userName = ClsInputValidate::readString();

        while (!ClsUser::isUserExist(userName)) {
            cout << "\nUser is not found, choose another one: ";
            userName = ClsInputValidate::readString();
        }

        ClsUser User1 = ClsUser::find(userName);
        _printUser(User1);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            if (User1.markForDelete()) {
                cout << "\nUser Deleted Successfully :-)\n";
                _printUser(User1);
            }
            else {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }
};