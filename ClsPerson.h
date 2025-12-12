#pragma once
#include <iostream>
#include <string>

using namespace std;

class ClsPerson {
private:
    string _firstName;
    string _lastName;
    string _email;
    string _phone;

public:
    ClsPerson(string firstName, string lastName, string email, string phone) {
        _firstName = firstName;
        _lastName = lastName;
        _email = email;
        _phone = phone;
    }
    
    void setFirstName(string firstName) {
        _firstName = firstName;
    }

    string getFirstName() {
        return _firstName;
    }

    void setLastName(string lastName) {
        _lastName = lastName;
    }

    string getLastName() {
        return _lastName;
    }

    void setEmail(string email) {
        _email = email;
    }

    string getEmail() {
        return _email;
    }

    void setPhone(string phone) {
        _phone = phone;
    }

    string getPhone() {
        return _phone;
    }

    string fullName() {
        return _firstName + " " + _lastName;
    }

    void print() {
        cout << "\nInfo:";
        cout << "\nFirstName: " << _firstName;
        cout << "\nLastName : " << _lastName;
        cout << "\nFull Name: " << fullName();
        cout << "\nEmail : " << _email;
        cout << "\nPhone : " << _phone;
    }
};