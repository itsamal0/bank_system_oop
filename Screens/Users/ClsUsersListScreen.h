#pragma once
#include <iostream>
#include "..\ClsScreen.h"
#include "..\..\Core\ClsUser.h"
#include <iomanip>

class ClsUsersListScreen : protected ClsScreen {
private:
    static void _printUserRecordLine(ClsUser User) {
        cout << setw(8) << left << "" << "| " << setw(12) << left << User.getUserName();
        cout << "| " << setw(25) << left << User.fullName();
        cout << "| " << setw(12) << left << User.getPhone();
        cout << "| " << setw(20) << left << User.getEmail();
        cout << "| " << setw(10) << left << User.getPassword();
        cout << "| " << setw(12) << left << User.getPermissions();
    }

public:
    static void showUsersList() {
        vector <ClsUser> vUsers = ClsUser::getUsersList();

        string title = "\t  User List Screen";
        string subTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _drawScreenHeader(title, subTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";

        else
            for (ClsUser User : vUsers) {
                _printUserRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};

