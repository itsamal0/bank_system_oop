#include <iostream>
#include "ClsBankClient.h"
#include "ClsInputValidate.h"

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

int main() {
    updateClient();
    system("pause>0");
    return 0;
}