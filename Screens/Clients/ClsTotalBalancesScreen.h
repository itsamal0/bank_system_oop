#pragma once
#include <iostream>
#include "..\ClsScreen.h"
#include "..\..\Core\ClsBankClient.h"
#include "..\..\Lib\ClsUtil.h"
#include <iomanip>

class ClsTotalBalancesScreen : protected ClsScreen {
private:
    static void printClientRecordBalanceLine(ClsBankClient Client) {
        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.accountNumber();
        cout << "| " << setw(40) << left << Client.fullName();
        cout << "| " << setw(12) << left << Client.getAccountBalance();
    }

public:
    static void showtotalBalances() {
        vector <ClsBankClient> vClients = ClsBankClient::getClientsList();

        string title = "\t  Balances List Screen";
        string subTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _drawScreenHeader(title, subTitle);

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;
        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        double totalBalances = ClsBankClient::getTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";

        else
            for (ClsBankClient Client : vClients) {
                printClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;
        cout << "\t\t\t\t\t   Total Balances = " << totalBalances << endl;
        cout << "\t\t\t\t\t   ( " << ClsUtil::numberToText(totalBalances) << ")";
    }

};

