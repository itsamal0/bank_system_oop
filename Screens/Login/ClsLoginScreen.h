#pragma once
#include <iostream>
#include "..\ClsScreen.h"
#include "..\..\Core\ClsUser.h"
#include <iomanip>
#include "..\ClsMainScreen.h"
#include "..\..\Global.h"

class ClsLoginScreen : protected ClsScreen {
private:

    static bool _login() {
        bool loginFaild = false;
        string userName, password;
        short faildLoginCount = 0;

        do {
            if (loginFaild) {
                faildLoginCount++;
                cout << "\nInvlaid Username/Password!";
                cout << "\nYou have " << (3 - faildLoginCount) << " Trial(s) to login.\n\n";   
            }

            if (faildLoginCount == 3) {
                cout << "\nYour are Locked after 3 faild trails \n\n";
                return false;
            }

            cout << "Enter Username? ";
            cin >> userName;

            cout << "Enter Password? ";
            cin >> password;

            CurrentUser = ClsUser::find(userName, password);

            loginFaild = CurrentUser.isEmpty();

        } while (loginFaild);

        CurrentUser.RegisterLogIn();
        ClsMainScreen::showMainMenue();
        return true;
    }

public:

    static bool showLoginScreen() {
        system("cls");
        _drawScreenHeader("\t  Login Screen");
        return _login();
    }

};