#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsInputValidate.h"
#include "ClsDepositScreen.h"
#include "ClsWithdrawtScreen.h"
#include "ClsTotalBalancesScreen.h"
#include "ClsTransferScreen.h"
#include <iomanip>
using namespace std;

class ClsTransactionsScreen : protected ClsScreen {
private:
    enum EnTransactionsMenueOptions {
        Deposit = 1, Withdraw = 2,
        ShowTotalBalance = 3, Transfer = 4, ShowMainMenue = 5
    };

    static short readTransactionsMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 4]? ";
        short choice = ClsInputValidate::readNumberBetween<short>(1, 4, "Enter Number between 1 to 4? ");
        return choice;
    }

    static void _showDepositScreen() {
        ClsDepositScreen::showDepositScreen();
    }

    static void _showWithdrawScreen() {
        ClsWithdrawScreen::showWithdrawScreen();
    }

    static void _showTotalBalancesScreen() {
        ClsTotalBalancesScreen::showtotalBalances();
    }
    
    static void _showTransferScreen() {
        ClsTransferScreen::showTransferScreen();
    }

    static void _goBackToTransactionsMenue() {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        showTransactionsMenue();
    }

    static void _PerformTransactionsMenueOption(EnTransactionsMenueOptions TransactionsMenueOption) {
        switch (TransactionsMenueOption) {
            case EnTransactionsMenueOptions::Deposit: {
                system("cls");
                _showDepositScreen();
                _goBackToTransactionsMenue();
                break;
            }

            case EnTransactionsMenueOptions::Withdraw: {
                system("cls");
                _showWithdrawScreen();
                _goBackToTransactionsMenue();
                break;
            }

            case EnTransactionsMenueOptions::ShowTotalBalance: {
                system("cls");
                _showTotalBalancesScreen();
                _goBackToTransactionsMenue();
                break;
            }
            
            case EnTransactionsMenueOptions::Transfer: {
                system("cls");
                _showTransferScreen();
                _goBackToTransactionsMenue();
                break;
            }
        }

    }

public:
    static void showTransactionsMenue() {
        if (!checkAccessRights(ClsUser::EnPermissions::pTranactions)) {
                return;
        }

        system("cls");
        _drawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((EnTransactionsMenueOptions)readTransactionsMenueOption());
    }
};

