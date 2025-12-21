#pragma once
#include <iostream>
#include "..\ClsScreen.h"
#include "..\..\Core\ClsPerson.h"
#include "..\..\Core\ClsUser.h"
#include "..\..\Lib\ClsInputValidate.h"

class ClsFindUserScreen : protected ClsScreen {

private:
    static void _printUser(ClsUser User) {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.getFirstName();
        cout << "\nLastName    : " << User.getLastName();
        cout << "\nFull Name   : " << User.fullName();
        cout << "\nEmail       : " << User.getEmail();
        cout << "\nPhone       : " << User.getPhone();
        cout << "\nUserName    : " << User.getUserName();
        cout << "\nPassword    : " << User.getPassword();
        cout << "\nPermissions : " << User.getPermissions();
        cout << "\n___________________\n";
    }

public:
    static void showFindUserScreen() {
        _drawScreenHeader("\t  Find User Screen");

        string userName;
        cout << "\nPlease Enter UserName: ";
        userName = ClsInputValidate::readString();

        while (!ClsUser::isUserExist(userName)) {
            cout << "\nUser is not found, choose another one: ";
            userName = ClsInputValidate::readString();
        }

        ClsUser User1 = ClsUser::find(userName);

        if (!User1.isEmpty()) {
            cout << "\nUser Found :-)\n";
        }
        
        else {
            cout << "\nUser Was not Found :-(\n";
        }

        _printUser(User1);
    }
};