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

        static ClsBankClient _getEmptyClientObject() {
            return ClsBankClient(EnMode::EmptyMode, "", "", "", "", "", "", 0);
        };

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
};