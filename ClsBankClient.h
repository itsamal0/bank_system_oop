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
        enum EnMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
        EnMode _mode;
        string _accountNumber;
        string _pinCode;
        float _accountBalance;
        bool _markedForDelete = false;

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
                    if (C._markedForDelete == false) {
                        DataLine = _convertClientObjectToLine(C);
                        MyFile << DataLine << endl;
                    }

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

        void _update() {
            vector <ClsBankClient> _vClients;
            _vClients = _loadClientsDataFromFile();

            for (ClsBankClient& C : _vClients) {
                if (C.accountNumber() == accountNumber()) {
                    C = *this;
                    break;
                }
            }

            _saveCleintsDataToFile(_vClients);
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

        void _addNew() {
            _addDataLineToFile(_convertClientObjectToLine(*this));
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

        // No UI Related code iside object.
        // void print() {
        //     cout << "\nClient Card:";
        //     cout << "\n___________________";
        //     ClsPerson::print();
        //     cout << "\nAcc. Number : " << _accountNumber;
        //     cout << "\nPassword    : " << _pinCode;
        //     cout << "\nBalance     : " << _accountBalance;
        //     cout << "\n___________________\n";
        // }

        static ClsBankClient find(string accountNumber) {
            return _internalFind(accountNumber, "", false); 
        }

        static ClsBankClient find(string accountNumber, string pinCode) {
            return _internalFind(accountNumber, pinCode, true); 
        }

        enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

        enSaveResults save() {
            switch (_mode) {
                case EnMode::EmptyMode:
                    return enSaveResults::svFaildEmptyObject;

                case EnMode::UpdateMode: {
                    _update();
                    return enSaveResults::svSucceeded;
                }

                case EnMode::AddNewMode: {
                    //This will add new record to file or database
                    if (ClsBankClient::isClientExist(_accountNumber)) {
                        return enSaveResults::svFaildAccountNumberExists;
                    }

                    else {
                        _addNew();
                        //We need to set the mode to update after add new
                        _mode = EnMode::UpdateMode;
                        return enSaveResults::svSucceeded;
                    }
                }

                default:
                    return enSaveResults::svFaildEmptyObject;
            }
        }

        
        bool markForDelete() {
            vector <ClsBankClient> _vClients;
            _vClients = _loadClientsDataFromFile();

            for (ClsBankClient& C : _vClients) {
                if (C.accountNumber() == _accountNumber) {
                    C._markedForDelete = true;
                    break;
                }

            }

            _saveCleintsDataToFile(_vClients);

            *this = _getEmptyClientObject();

            return true;
        }

        static bool isClientExist(string accountNumber) {
            ClsBankClient Client1 = find(accountNumber);
            return (!Client1.isEmpty());
        }

        static ClsBankClient getAddNewClientObject(string accountNumber) {
            return ClsBankClient(EnMode::AddNewMode, "", "", "", "", accountNumber, "", 0);
        }

        static vector <ClsBankClient> getClientsList() {
            return _loadClientsDataFromFile();
        }
  
        static float getTotalBalances() {
            vector <ClsBankClient> vClients = ClsBankClient::getClientsList();
            double totalBalances = 0;

            for (ClsBankClient Client : vClients)
                totalBalances += Client.getAccountBalance();

            return totalBalances;
        }

        void deposit(double amount) {
            _accountBalance += amount;
            save();
        }

        bool withdraw(double amount) {
            if (amount > _accountBalance)
                return false;
            
            else {
                _accountBalance -= amount;
                save();
                return true;
            }
        }

};