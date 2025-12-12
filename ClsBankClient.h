#pragma once
#include <iostream>
#include <string>
#include "ClsPerson.h"
#include "ClsString.h"
#include <vector>
#include <fstream>
using namespace std;

class ClsBankClient : public ClsPerson {
    private:
        enum EnMode {EmptyMode = 0, UpdateMode = 1};
        EnMode _mode;
        string _accountNumber;
        string _pinCode;
        float _accountBalance;

        static ClsBankClient _convertLinetoClientObject(string Line, string Seperator = "#//#") {
            vector<string> vClientData;
            vClientData = ClsString::splitString(Line, Seperator);

            return ClsBankClient(EnMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
        }

        static string _convertClientObjectToLine(ClsBankClient Client, string Seperator = "#//#") {
            string stClientRecord = "";

            stClientRecord += Client.getFirstName() + Seperator;
            stClientRecord += Client.getLastName() + Seperator;
            stClientRecord += Client.getEmail() + Seperator;
            stClientRecord += Client.getPhone() + Seperator;
            stClientRecord += Client.accountNumber() + Seperator;
            stClientRecord += Client.getPinCode() + Seperator;
            stClientRecord += to_string(Client.getAccountBalance());

            return stClientRecord;

        }

        static  vector <ClsBankClient> _loadClientsDataFromFile() {
            vector <ClsBankClient> vClients;

            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);

            if (MyFile.is_open()) {

                string Line;

                while (getline(MyFile, Line)) {
                    ClsBankClient Client = _convertLinetoClientObject(Line);
                    vClients.push_back(Client);
                }

                MyFile.close();
            }

            return vClients;

        }

        static void _saveCleintsDataToFile(vector <ClsBankClient> vClients) {
            fstream MyFile;
            MyFile.open("Clients.txt", ios::out);

            string DataLine;

            if (MyFile.is_open()) {
                for (ClsBankClient C : vClients) {
                    DataLine = _convertClientObjectToLine(C);
                    MyFile << DataLine << endl;

                }

                MyFile.close();
            }

        }

        void _addDataLineToFile(string  stDataLine) {
            fstream MyFile;
            MyFile.open("Clients.txt", ios::out | ios::app);

            if (MyFile.is_open()) {
                MyFile << stDataLine << endl;
                MyFile.close();
            }
        }

        static ClsBankClient _getEmptyClientObject() {
            return ClsBankClient(EnMode::EmptyMode, "", "", "", "", "", "", 0);
        };

        static ClsBankClient _internalFind(string accountNumber, string pinCode, bool findByPinCode) {
            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);

            if (MyFile.is_open()) {
                string Line;
                while (getline(MyFile, Line)) {
                    ClsBankClient Client = _convertLinetoClientObject(Line);

                    if (findByPinCode) {
                        if (Client.accountNumber() == accountNumber && Client.getPinCode() == pinCode) {
                            MyFile.close();
                            return Client;
                        }

                    } else {
                        if (Client.accountNumber() == accountNumber) {
                            MyFile.close();
                            return Client;
                        }
                    }
                }
                MyFile.close();
            }

            return _getEmptyClientObject();
        }

    public:
        ClsBankClient(EnMode mode, string firstName, string lastName, string email, string Phone,
            string accountNumber, string pinCode, float accountBalance) 
            : ClsPerson(firstName, lastName, email, Phone) {
            _mode = mode;
            _accountNumber = accountNumber;
            _pinCode = pinCode;
            _accountBalance = accountBalance;
        }

        bool isEmpty() {
            return (_mode == EnMode::EmptyMode);
        }

        string accountNumber() {
            return _accountNumber;
        }

        void setPinCode(string pinCode) {
            _pinCode = pinCode;
        }

        string getPinCode() {
            return _pinCode;
        }

        void setAccountBalance(float accountBalance) {
            _accountBalance = accountBalance;
        }

        float getAccountBalance() {
            return _accountBalance;
        }

        void print() {
            cout << "\nClient Card:";
            cout << "\n___________________";
            ClsPerson::print();
            cout << "\nAcc. Number : " << _accountNumber;
            cout << "\nPassword    : " << _pinCode;
            cout << "\nBalance     : " << _accountBalance;
            cout << "\n___________________\n";
        }

        static ClsBankClient find(string accountNumber) {
            return _internalFind(accountNumber, "", false); 
        }

        static ClsBankClient find(string accountNumber, string pinCode) {
            return _internalFind(accountNumber, pinCode, true); 
        }

        static bool isClientExist(string accountNumber) {
            ClsBankClient Client1 = find(accountNumber);
            return (!Client1.isEmpty());
        }
};