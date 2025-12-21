#pragma once
#include "..\ClsScreen.h"
#include "..\..\Core\ClsBankClient.h"
#include "iomanip"

class ClsClientListScreen : protected ClsScreen {
private:
     static void _printClientRecordLine(ClsBankClient Client) {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.accountNumber();
        cout << "| " << setw(20) << left << Client.fullName();
        cout << "| " << setw(12) << left << Client.getPhone();
        cout << "| " << setw(20) << left << Client.getEmail();
        cout << "| " << setw(10) << left << Client.getPinCode();
        cout << "| " << setw(12) << left << Client.getAccountBalance();
    }

public: 
    static void showClientsList() {

        if (!checkAccessRights(ClsUser::EnPermissions::pListClients)) {
            return;
        }
        
        vector <ClsBankClient> vClients = ClsBankClient::getClientsList();

        string title = "\t  Client List Screen";
        string subTitle ="\t    (" + to_string(vClients.size()) + ") Client(s).";

        _drawScreenHeader(title, subTitle);
        

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (ClsBankClient Client : vClients) {
                _printClientRecordLine(Client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};