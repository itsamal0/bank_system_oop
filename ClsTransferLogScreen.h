#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsBankClient.h"
#include <iomanip>
#include <fstream>

class ClsTransferLogScreen : protected ClsScreen {
private:

    static void _printTransferLogRecordLine(ClsBankClient::StTrnsferLogRecord transferLogRecord) {
        cout << setw(8) << left << "" << "| " << setw(23) << left << transferLogRecord.dateTime;
        cout << "| " << setw(8) << left << transferLogRecord.sourceAccountNumber;
        cout << "| " << setw(8) << left << transferLogRecord.destinationAccountNumber;
        cout << "| " << setw(8) << left << transferLogRecord.amount;
        cout << "| " << setw(10) << left << transferLogRecord.srcBalanceAfter;
        cout << "| " << setw(10) << left << transferLogRecord.destBalanceAfter;
        cout << "| " << setw(8) << left << transferLogRecord.userName;
    }

public:

    static void showTransferLogScreen() {
        vector <ClsBankClient::StTrnsferLogRecord> vTransferLogRecord = ClsBankClient::getTransfersLogList();

        string title = "\tTransfer Log List Screen";
        string subTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _drawScreenHeader(title, subTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "From Acc";
        cout << "| " << left << setw(8) << "To Acc";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "Src.Bal";
        cout << "| " << left << setw(10) << "Dst.Bal";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0) {
            cout << "\t\t\t\tNo Transfers Available In the System!";
        } 

        else {
            for (ClsBankClient::StTrnsferLogRecord record : vTransferLogRecord) {
                _printTransferLogRecordLine(record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};