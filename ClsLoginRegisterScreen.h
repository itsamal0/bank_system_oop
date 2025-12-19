#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsUser.h"
#include <iomanip>
#include <fstream>

class ClsLoginRegisterScreen : protected ClsScreen {

private:
    
    static void _printLoginRegisterRecordLine(ClsUser::StLoginRegisterRecord LoginRegisterRecord) {
        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.dateTime;
        cout << "| " << setw(20) << left << LoginRegisterRecord.userName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.permissions;
    }

public:
  
    static void showLoginRegisterScreen() {
        if (!checkAccessRights(ClsUser::EnPermissions::pShowLoginRegister)) {
            return;
        }

        vector <ClsUser::StLoginRegisterRecord> vLoginRegisterRecord = ClsUser::getLoginRegisterList();
  
        string title = "\tLogin Register List Screen";
        string subTitle = "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _drawScreenHeader(title, subTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegisterRecord.size() == 0) {
            cout << "\t\t\t\tNo Logins Available In the System!";
        }
        
        else {
            for (ClsUser::StLoginRegisterRecord record : vLoginRegisterRecord) {
                _printLoginRegisterRecordLine(record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};