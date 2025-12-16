#include <iostream>
#include "ClsBankClient.h"
#include "ClsInputValidate.h"
#include "ClsUtil.h"
#include "ClsMainScreen.h"
#include <iomanip>


void printClientRecordBalanceLine(ClsBankClient Client) {
    cout << "| " << setw(15) << left << Client.accountNumber();
    cout << "| " << setw(40) << left << Client.fullName();
    cout << "| " << setw(12) << left << Client.getAccountBalance();
}

void showtotalBalances() {
    vector <ClsBankClient> vClients = ClsBankClient::getClientsList();

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double totalBalances = ClsBankClient::getTotalBalances();

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";

    else
        for (ClsBankClient Client : vClients) {
            printClientRecordBalanceLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << totalBalances << endl;
    cout << "\t\t\t\t\t   ( " << ClsUtil::numberToText(totalBalances) << ")";
}

int main() {
    ClsMainScreen::showMainMenue();
    system("pause>0");
    return 0;
}