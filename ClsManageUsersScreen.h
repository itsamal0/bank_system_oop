#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsInputValidate.h"
#include "ClsUsersListScreen.h"
#include "ClsAddNewUserScreen.h"
#include "ClsDeleteUserScreen.h"
#include "ClsUpdateUserScreen.h"
#include "ClsFindUserScreen.h"
#include <iomanip>
using namespace std;

class ClsManageUsersScreen : protected ClsScreen {
private:
    enum EnManageUsersMenuOptions {
        ListUsers = 1, AddNewUser = 2, DeleteUser = 3,
        UpdateUser = 4, FindUser = 5, MainMenu = 6
    };

    static short readManageUsersMenuOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = ClsInputValidate::readNumberBetween<short>(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _goBackToManageUsersMenu() {
        cout << "\n\nPress any key to go back to Manage Users Menue...";
        system("pause>0");
        showManageUsersMenu();
    }

    static void _showListUsersScreen() {
        ClsUsersListScreen::showUsersList();
    }

    static void _showAddNewUserScreen() {
        ClsAddNewUserScreen::showAddNewUserScreen();
    }

    static void _showDeleteUserScreen() {
        ClsDeleteUserScreen::showDeleteUserScreen();
    }

    static void _showUpdateUserScreen() {
        ClsUpdateUserScreen::showUpdateUserScreen();
    }

    static void _showFindUserScreen() {
        ClsFindUserScreen::showFindUserScreen();
    }

    static void _performManageUsersMenuOption(EnManageUsersMenuOptions ManageUsersMenuOption) {
        switch (ManageUsersMenuOption) {
            case EnManageUsersMenuOptions::ListUsers: {
                system("cls");
                _showListUsersScreen();
                _goBackToManageUsersMenu();
                break;
            }

            case EnManageUsersMenuOptions::AddNewUser: {
                system("cls");
                _showAddNewUserScreen();
                _goBackToManageUsersMenu();
                break;
            }

            case EnManageUsersMenuOptions::DeleteUser: {
                system("cls");
                _showDeleteUserScreen();
                _goBackToManageUsersMenu();
                break;
            }

            case EnManageUsersMenuOptions::UpdateUser: {
                system("cls");
                _showUpdateUserScreen();
                _goBackToManageUsersMenu();
                break;
            }

            case EnManageUsersMenuOptions::FindUser: {
                system("cls");
                _showFindUserScreen();
                _goBackToManageUsersMenu();
                break;
            }
        }

    }


public:
    static void showManageUsersMenu() {
        if (!checkAccessRights(ClsUser::EnPermissions::pManageUsers)) {
            return;
        }

        system("cls");
        _drawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _performManageUsersMenuOption((EnManageUsersMenuOptions)readManageUsersMenuOption());
    }

};

