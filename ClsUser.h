#pragma once
#include <iostream>
#include <string>
#include "ClsPerson.h"
#include "ClsString.h"
#include "ClsDate.h"
#include <vector>
#include <fstream>
using namespace std;

class ClsUser : public ClsPerson {
public: 
    struct StLoginRegisterRecord {
        string dateTime;
        string userName;
        string password;
        int permissions;
    };

private:
    enum EnMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    EnMode _mode;
    string _userName;
    string _password;
    int _permissions;
    bool _markedForDelete = false;

    static StLoginRegisterRecord _convertLoginRegisterLineToRecord(string Line, string Seperator = "#//#") {
        StLoginRegisterRecord LoginRegisterRecord;
        vector <string> vloginRegisterRecord = ClsString::splitString(Line, Seperator);

        LoginRegisterRecord.dateTime = vloginRegisterRecord[0];
        LoginRegisterRecord.userName = vloginRegisterRecord[1];
        LoginRegisterRecord.password = vloginRegisterRecord[2];
        LoginRegisterRecord.permissions = stoi(vloginRegisterRecord[3]);

        return LoginRegisterRecord;
    }
    
    string _prepareLogInRecord( string seperator = "#//#") {
        string loginRecord = "";
        loginRecord += ClsDate::GetSystemDateTimeString() + seperator;
        loginRecord += _userName + seperator;
        loginRecord += _password + seperator;
        loginRecord += to_string(_permissions);
        return loginRecord;
    }

    static ClsUser _convertLinetoUserObject(string Line, string Seperator = "#//#") {
        vector<string> vUserData;
        vUserData = ClsString::splitString(Line, Seperator);

        return ClsUser(EnMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));
    }

    static string _convertUserObjectToLine(ClsUser User, string Seperator = "#//#") {
        string stUserRecord = "";
        stUserRecord += User.getFirstName() + Seperator;
        stUserRecord += User.getLastName() + Seperator;
        stUserRecord += User.getEmail() + Seperator;
        stUserRecord += User.getPhone() + Seperator;
        stUserRecord += User.getUserName() + Seperator;
        stUserRecord += User.getPassword() + Seperator;
        stUserRecord += to_string(User.getPermissions());

        return stUserRecord;
    }

    static vector <ClsUser> _loadUsersDataFromFile() {
        vector <ClsUser> vUsers;
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);

        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                ClsUser User = _convertLinetoUserObject(Line);
                vUsers.push_back(User);
            }
            MyFile.close();
        }
        return vUsers;
    }

    static void _saveUsersDataToFile(vector <ClsUser> vUsers) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out);

        string DataLine;
        if (MyFile.is_open()) {
            for (ClsUser U : vUsers) {
                if (U._markedForDelete == false) {
                    DataLine = _convertUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    void _update() {
        vector <ClsUser> _vUsers;
        _vUsers = _loadUsersDataFromFile();

        for (ClsUser& U : _vUsers) {
            if (U.getUserName() == _userName) {
                U = *this;
                break;
            }
        }
        _saveUsersDataToFile(_vUsers);
    }

    void _addNew() {
        _addDataLineToFile(_convertUserObjectToLine(*this));
    }

    void _addDataLineToFile(string stDataLine) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open()) {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    static ClsUser _internalFind(string userName, string password, bool findWithPassword) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);

        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                ClsUser User = _convertLinetoUserObject(Line);

                if (findWithPassword) {
                    if (User.getUserName() == userName && User.getPassword() == password) {
                        MyFile.close();
                        return User;
                    }
                }
                else {
                    if (User.getUserName() == userName) {
                        MyFile.close();
                        return User;
                    }
                }
            }
            MyFile.close();
        }
        return _getEmptyUserObject();
    }

    static ClsUser _getEmptyUserObject() {
        return ClsUser(EnMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    enum EnPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
    };

    ClsUser(EnMode mode, string firstName, string lastName,
        string email, string phone, string userName, string password,
        int permissions) :
        ClsPerson(firstName, lastName, email, phone) {
        _mode = mode;
        _userName = userName;
        _password = password;
        _permissions = permissions;
    }

    bool isEmpty() {
        return (_mode == EnMode::EmptyMode);
    }

    string getUserName() {
        return _userName;
    }

    void setUserName(string userName) {
        _userName = userName;
    }

    void setPassword(string password) {
        _password = password;
    }

    string getPassword() {
        return _password;
    }

    void setPermissions(int permissions) {
        _permissions = permissions;
    }

    int getPermissions() {
        return _permissions;
    }

    static ClsUser find(string userName) {
        return _internalFind(userName, "", false);
    }

    static ClsUser find(string userName, string password) {
        return _internalFind(userName, password, true);
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults save() {
        switch (_mode) {
            case EnMode::EmptyMode:
                return enSaveResults::svFaildEmptyObject;

            case EnMode::UpdateMode:
                _update();
                return enSaveResults::svSucceeded;

            case EnMode::AddNewMode:
                if (ClsUser::isUserExist(_userName)) {
                    return enSaveResults::svFaildUserExists;
                }
                else {
                    _addNew();
                    _mode = EnMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
            
            default:
                return enSaveResults::svFaildEmptyObject;
        }
    }

    static bool isUserExist(string userName) {
        ClsUser User = ClsUser::find(userName);
        return (!User.isEmpty());
    }

    bool markForDelete() {
        vector <ClsUser> _vUsers;
        _vUsers = _loadUsersDataFromFile();

        for (ClsUser& U : _vUsers) {
            if (U.getUserName() == _userName) {
                U._markedForDelete = true;
                break;
            }
        }

        _saveUsersDataToFile(_vUsers);
        *this = _getEmptyUserObject();
        return true;
    }

    static ClsUser getAddNewUserObject(string userName) {
        return ClsUser(EnMode::AddNewMode, "", "", "", "", userName, "", 0);
    }

    static vector <ClsUser> getUsersList() {
        return _loadUsersDataFromFile();
    }

    bool checkAccessPermission(EnPermissions Permission) {
        if (this->_permissions == EnPermissions::eAll)
            return true;

        return ((Permission & this->_permissions) == Permission);
    }

    void RegisterLogIn() {
        string stDataLine = _prepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open()) {
            MyFile << stDataLine << endl;
            MyFile.close();
        }

    }

    static  vector <StLoginRegisterRecord> getLoginRegisterList() {
         vector <StLoginRegisterRecord> vLoginRegisterRecord;

         fstream MyFile;
         MyFile.open("LoginRegister.txt", ios::in);

         if (MyFile.is_open()) {

             string Line;
             StLoginRegisterRecord LoginRegisterRecord;

             while (getline(MyFile, Line)) {
                 LoginRegisterRecord = _convertLoginRegisterLineToRecord(Line);
                 vLoginRegisterRecord.push_back(LoginRegisterRecord);
             }

             MyFile.close();
         }

         return vLoginRegisterRecord;
     }
};