#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsPerson.h"
#include "ClsUser.h"
#include "ClsInputValidate.h"

class ClsUpdateUserScreen : protected ClsScreen {
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

        return permissions;
    }

public:

    static void showUpdateUserScreen() {
        _drawScreenHeader("\tUpdate User Screen");

        string userName = "";

        cout << "\nPlease Enter User UserName: ";
        userName = ClsInputValidate::readString();

        while (!ClsUser::isUserExist(userName)) {
            cout << "\nAccount number is not found, choose another one: ";
            userName = ClsInputValidate::readString();
        }

        ClsUser User1 = ClsUser::find(userName);
        _printUser(User1);

        cout << "\nAre you sure you want to update this User y/n? ";

        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";

            _readUserInfo(User1);

            ClsUser::enSaveResults SaveResult;
            SaveResult = User1.save();

            switch (SaveResult) {
                case ClsUser::enSaveResults::svSucceeded: {
                    cout << "\nUser Updated Successfully :-)\n";
                    _printUser(User1);
                    break;
                }
                case ClsUser::enSaveResults::svFaildEmptyObject: {
                    cout << "\nError User was not saved because it's Empty";
                    break;
                }
            }
        }
    }
};