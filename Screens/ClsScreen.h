#pragma once
#include <iostream>
#include "..\Core\ClsUser.h"
#include "..\Global.h"
#include "..\Lib\ClsDate.h"
using namespace std;

class ClsScreen {
protected :
    static void _drawScreenHeader(string title,string subTitle ="") {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << title;

        if (subTitle != "") {
            cout << "\n\t\t\t\t\t  " << subTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\n\t\t\t\t\tUser: " << CurrentUser.getUserName();
        cout << "\n\t\t\t\t\tDate: " << ClsDate::DateToString(ClsDate()) << "\n\n";
    }

    static bool checkAccessRights(ClsUser::EnPermissions Permission) {
        if (!CurrentUser.checkAccessPermission(Permission)) {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";   
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
            
        return true;
    }
};