#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsUser.h"
#include <iomanip>
#include "ClsMainScreen.h"
#include "Global.h"

class ClsLoginScreen : protected ClsScreen {
private:

    static void _login() {
        bool loginFaild = false;
        string userName, password;

        do {
            if (loginFaild) {
                cout << "\nInvlaid Username/Password!\n\n";
            }

            cout << "Enter Username? ";
            cin >> userName;

            cout << "Enter Password? ";
            cin >> password;

            CurrentUser = ClsUser::find(userName, password);

            loginFaild = CurrentUser.isEmpty();

        } while (loginFaild);

        ClsMainScreen::showMainMenue();
    }

public:

    static void showLoginScreen() {
        system("cls");
        _drawScreenHeader("\t  Login Screen");
        _login();
    }

};