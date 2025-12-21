#pragma once
#include <iostream>
#include "..\ClsScreen.h"
#include "..\..\Core\ClsUser.h"
#include "..\..\Lib\ClsInputValidate.h"
#include <iomanip>

class ClsAddNewUserScreen : protected ClsScreen {
private:

    static void _readUserInfo(ClsUser& User) {
        cout << "\nEnter FirstName: ";
        User.setFirstName(ClsInputValidate::readString());

        cout << "\nEnter LastName: ";
        User.setLastName(ClsInputValidate::readString());

        cout << "\nEnter Email: ";
        User.setEmail(ClsInputValidate::readString());

        cout << "\nEnter Phone: ";
        User.setPhone(ClsInputValidate::readString());

        cout << "\nEnter Password: ";
        User.setPassword(ClsInputValidate::readString());

        cout << "\nEnter Permission: ";
        User.setPermissions(_readPermissionsToSet());
    }

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

    static int _readPermissionsToSet() {
        int permissions = 0;
        char answer = 'n';

        cout << "\nDo you want to give full access? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            permissions += ClsUser::EnPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            permissions += ClsUser::EnPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            permissions += ClsUser::EnPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            permissions += ClsUser::EnPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            permissions += ClsUser::EnPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            permissions += ClsUser::EnPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            permissions += ClsUser::EnPermissions::pManageUsers;
        }

        cout << "\nShow Login Register? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            permissions += ClsUser::EnPermissions::pShowLoginRegister;
        }

        return permissions;
    }


public:
    static void showAddNewUserScreen() {
        _drawScreenHeader("\t  Add New User Screen");

        string userName = "";

        cout << "\nPlease Enter UserName: ";
        userName = ClsInputValidate::readString();

        while (ClsUser::isUserExist(userName)) {
            cout << "\nUserName Is Already Used, Choose another one: ";
            userName = ClsInputValidate::readString();
        }

        ClsUser NewUser = ClsUser::getAddNewUserObject(userName);

        _readUserInfo(NewUser);

        ClsUser::enSaveResults SaveResult;

        SaveResult = NewUser.save();

        switch (SaveResult) {
            case  ClsUser::enSaveResults::svSucceeded: {
                cout << "\nUser Addeded Successfully :-)\n";
                _printUser(NewUser);
                break;
            }

            case ClsUser::enSaveResults::svFaildEmptyObject: {
                cout << "\nError User was not saved because it's Empty";
                break;
            }

            case ClsUser::enSaveResults::svFaildUserExists: {
                cout << "\nError User was not saved because UserName is used!\n";
                break;
            }
        }
    }
};

