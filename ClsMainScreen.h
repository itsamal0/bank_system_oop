#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsInputValidate.h"
#include "ClsClientListScreen.h"
#include <iomanip>
using namespace std;

class ClsMainScreen : protected ClsScreen {
private:
    enum EnMainMenueOptions {
        ListClients = 1, AddNewClient = 2, DeleteClient = 3,
        UpdateClient = 4, FindClient = 5, ShowTransactionsMenue = 6,
        ManageUsers = 7, Exit = 8
    };

    static short _readMainMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
        short choice = ClsInputValidate::readNumberBetween<short>(1, 8, "Enter Number between 1 to 8? ");
        return choice;
    }

    static void _goBackToMainMenue() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        showMainMenue();
    }

    static void _showAllClientsScreen() {
        ClsClientListScreen::showClientsList();
    }

    static void _showAddNewClientsScreen() {
        cout << "\nAdd New Client Screen Will be here...\n";
    }

    static void _showDeleteClientScreen() {
        cout << "\nDelete Client Screen Will be here...\n";
    }

    static void _showUpdateClientScreen() {
        cout << "\nUpdate Client Screen Will be here...\n";
    }

    static void _showFindClientScreen() {
        cout << "\nFind Client Screen Will be here...\n";
    }

    static void _showTransactionsMenue() {
        cout << "\nTransactions Menue Will be here...\n";
    }

    static void _showManageUsersMenue() {
        cout << "\nUsers Menue Will be here...\n";
    }

    static void _showEndScreen() {
        cout << "\nEnd Screen Will be here...\n";
    }

    static void _perfromMainMenueOption(EnMainMenueOptions MainMenueOption) {
        switch (MainMenueOption) {
            case EnMainMenueOptions::ListClients: {
                system("cls");
                _showAllClientsScreen();
                _goBackToMainMenue();
                break;
            }

            case EnMainMenueOptions::AddNewClient: {
                system("cls");
                _showAddNewClientsScreen();
                _goBackToMainMenue();
                break;
            }    

            case EnMainMenueOptions::DeleteClient: {
                system("cls");
                _showDeleteClientScreen();
                _goBackToMainMenue();
                break;
            }    

            case EnMainMenueOptions::UpdateClient: {
                system("cls");
                _showUpdateClientScreen();
                _goBackToMainMenue();
                break;
            }    

            case EnMainMenueOptions::FindClient: {
                system("cls");
                _showFindClientScreen();
                _goBackToMainMenue();
                break;
            }

            case EnMainMenueOptions::ShowTransactionsMenue: {
                system("cls");
                _showTransactionsMenue();
                break;
            }

            case EnMainMenueOptions::ManageUsers: {
                system("cls");
                _showManageUsersMenue();
                break;
            }

            case EnMainMenueOptions::Exit: {
                system("cls");
                _showEndScreen();
                break;
            }    
        }
    }

public:
    static void showMainMenue() {
        system("cls");
        _drawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _perfromMainMenueOption((EnMainMenueOptions)_readMainMenueOption());
    }
};