#include <iostream>
#include "ClsBankClient.h"
#include "ClsInputValidate.h"
#include "ClsUtil.h"
#include "ClsMainScreen.h"
#include <iomanip>

void readClientInfo(ClsBankClient& Client) {
    cout << "\nEnter FirstName: ";
    Client.setFirstName(ClsInputValidate::readString());

    cout << "\nEnter LastName: ";
    Client.setLastName(ClsInputValidate::readString());

    cout << "\nEnter Email: ";
    Client.setEmail(ClsInputValidate::readString());

    cout << "\nEnter Phone: ";
    Client.setPhone(ClsInputValidate::readString());

    cout << "\nEnter PinCode: ";
    Client.setPinCode(ClsInputValidate::readString());

    cout << "\nEnter Account Balance: ";
    Client.setAccountBalance(ClsInputValidate::readNumber<float>());
}

void updateClient() {
    string accountNumber = "";

    cout << "\nPlease Enter client Account Number: ";
    accountNumber = ClsInputValidate::readString();
    
    while (!ClsBankClient::isClientExist(accountNumber)) {
        cout << "\nAccount number is not found, choose another one: ";
        accountNumber = ClsInputValidate::readString();
    }

    ClsBankClient Client1 = ClsBankClient::find(accountNumber);
    Client1.print();

    cout << "\n\nUpdate Client Info:";
    cout << "\n____________________\n";

    readClientInfo(Client1);

    ClsBankClient::enSaveResults saveResult;

    saveResult = Client1.save();

    switch (saveResult) {
        case ClsBankClient::enSaveResults::svSucceeded: {
            cout << "\nAccount Updated Successfully :-)\n";
            Client1.print();
            break;
        }

        case ClsBankClient::enSaveResults::svFaildEmptyObject: {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }
}

void addNewClient() {
    string accountNumber = "";

    cout << "\nPlease Enter Account Number: ";
    accountNumber = ClsInputValidate::readString();

    while (ClsBankClient::isClientExist(accountNumber)) {
        cout << "\nAccount Number Is Already Used, Choose another one: ";
        accountNumber = ClsInputValidate::readString();
    }

    ClsBankClient NewClient = ClsBankClient::getAddNewClientObject(accountNumber);


    readClientInfo(NewClient);

    ClsBankClient::enSaveResults saveResult;

    saveResult = NewClient.save();

    switch (saveResult) {
        case  ClsBankClient::enSaveResults::svSucceeded: {
            cout << "\nAccount Addeded Successfully :-)\n";
            NewClient.print();
            break;
        }

        case ClsBankClient::enSaveResults::svFaildEmptyObject: {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }
}

void deleteClient() {
    string accountNumber = "";

    cout << "\nPlease Enter Account Number: ";
    accountNumber = ClsInputValidate::readString();

    while (!ClsBankClient::isClientExist(accountNumber)) {
        cout << "\nAccount number is not found, choose another one: ";
        accountNumber = ClsInputValidate::readString();
    }

    ClsBankClient Client1 = ClsBankClient::find(accountNumber);
    Client1.print();

    cout << "\nAre you sure you want to delete this client y/n? ";
    
    char answer = 'n';
    cin >> answer;

    if (answer == 'y' || answer == 'Y') {
        if (Client1.markForDelete()) {
            cout << "\nClient Deleted Successfully :-)\n";
            Client1.print();
        }

        else {
            cout << "\nError Client Was not Deleted\n";
        }
    }
}


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