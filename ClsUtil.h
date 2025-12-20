#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "ClsDate.h"

using namespace std;

class ClsUtil {
public:
    enum enCharType {
        small = 1, capital = 2,
        digit = 3, mix = 4, special = 5
    };

    static void initRandom() {
        srand((unsigned)time(NULL));
    }

    static int generateRandomNumber(int min, int max) {
        return rand() % (max - min + 1) + min;
    }

    static string tabs(short count) {
        string txt = "";
        for (int i = 0; i < count; i++) {
            txt += "\t";
        }
        return txt;
    }

    static void swap(int& x, int& y) {
        int temp = x;
        x = y;
        y = temp;
    }

    static void swap(double& x, double& y) {
        double temp = x;
        x = y;
        y = temp;
    }

    static void swap(string& x, string& y) {
        string temp = x;
        x = y;
        y = temp;
    }

    static void swap(ClsDate& x, ClsDate& y) {
        ClsDate::swapDates(x, y);
    }

    static char generateRandomChar(enCharType type) {
        if (type == mix) {
            type = (enCharType)generateRandomNumber(1, 3);
        }
        switch (type) {
            case small: 
                return (char)generateRandomNumber(97, 122);
            case capital:
                return (char)generateRandomNumber(65, 90);
            case special:
                return (char)generateRandomNumber(33, 47);
            case digit:
                return (char)generateRandomNumber(48, 57);
            default:
                return (char)generateRandomNumber(65, 90);
        }
    }

    static string generateWord(enCharType type, short len) {
        string s = "";
        for (int i = 0; i < len; i++) {
            s = s + generateRandomChar(type);
        }
        return s;
    }

    static string generateKey(enCharType type = capital) {
        string k = "";
        k = generateWord(type, 4) + "-";
        k += generateWord(type, 4) + "-";
        k += generateWord(type, 4) + "-";
        k += generateWord(type, 4);
        return k;
    }

    static void printKeyList(short num, enCharType type, short tabsCount = 0) {
        for (int i = 1; i <= num; i++) {
            cout << tabs(tabsCount) << "Key " << i << ": " << generateKey(type) << endl;
        }
    }

    static void fillArrWithRandomNumbers(int arr[100], int size, int min, int max) {
        for (int i = 0; i < size; i++)
            arr[i] = generateRandomNumber(min, max);
    }

    static void fillArrWithRandomWords(string arr[100], int size, enCharType type, short len) {
        for (int i = 0; i < size; i++)
            arr[i] = generateWord(type, len);
    }

    static void mixArr(int arr[100], int size) {
        for (int i = 0; i < size; i++) {
            int randIndex = generateRandomNumber(0, size - 1);
            swap(arr[i], arr[randIndex]);
        }
    }

    static void mixArr(string arr[100], int size) {
        for (int i = 0; i < size; i++) {
            int randIndex = generateRandomNumber(0, size - 1);
            swap(arr[i], arr[randIndex]);
        }
    }

    static string encryptText(string txt, short key = 10) {
        for (int i = 0; i < txt.length(); i++) {
            txt[i] = char((int)txt[i] + key);
        }
        return txt;
    }

    static string decryptText(string txt, short key = 10) {
        for (int i = 0; i < txt.length(); i++) {
            txt[i] = char((int)txt[i] - key);
        }
        return txt;
    }

    // Convert a single digit [0–9] to text
    static string digitToText(int n) {
        switch (n) {
            case 0: return "Zero";
            case 1: return "One";
            case 2: return "Two";
            case 3: return "Three";
            case 4: return "Four";
            case 5: return "Five";
            case 6: return "Six";
            case 7: return "Seven";
            case 8: return "Eight";
            case 9: return "Nine";
            default: return "";
        }
    }

    // Convert numbers from 10–19 to text
    static string numberTeens(int n) {
        switch (n) {
            case 10: return "Ten";
            case 11: return "Eleven";
            case 12: return "Twelve";
            case 13: return "Thirteen";
            case 14: return "Fourteen";
            case 15: return "Fifteen";
            case 16: return "Sixteen";
            case 17: return "Seventeen";
            case 18: return "Eighteen";
            case 19: return "Nineteen";
            default: return "";
        }
    }

    // Convert tens multiples [20, 30, 40, ...]
    static string numberToTens(int n) {
        switch (n) {
            case 2: return "Twenty";
            case 3: return "Thirty";
            case 4: return "Forty";
            case 5: return "Fifty";
            case 6: return "Sixty";
            case 7: return "Seventy";
            case 8: return "Eighty";
            case 9: return "Ninety";
            default: return "";
        }
    }

    // Convert a full integer number into text
    static string numberToText(int n) {
        if (n == 0) return "Zero";

        string result = "";

        if (n >= 1000000000) {
            result += numberToText(n / 1000000000) + " Billion";
            n %= 1000000000;
            if (n > 0) result += " ";
        }

        if (n >= 1000000) {
            result += numberToText(n / 1000000) + " Million";
            n %= 1000000;
            if (n > 0) result += " ";
        }

        if (n >= 1000) {
            result += numberToText(n / 1000) + " Thousand";
            n %= 1000;
            if (n > 0) result += " ";
        }

        if (n >= 100) {
            result += digitToText(n / 100) + " Hundred";
            n %= 100;
            if (n > 0) result += " ";
        }

        if (n >= 20) {
            result += numberToTens(n / 10);
            n %= 10;
            if (n > 0) result += " " + digitToText(n);
        }

        else if (n >= 10) {
            result += numberTeens(n);
        }

        else if (n > 0) {
            result += digitToText(n);
        }

        return result;
    }
};