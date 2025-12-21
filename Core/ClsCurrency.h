#pragma once
#include <iostream>
#include <string>
#include "..\Lib\ClsString.h"
#include <vector>
#include <fstream>
using namespace std;

class ClsCurrency
{

private:
    enum enMode
    {
        emptyMode = 0,
        updateMode = 1
    };
    enMode _mode;

    string _country;
    string _currencyCode;
    string _currencyName;
    float _rate;

    static ClsCurrency _convertLineToCurrencyObject(string line, string separator = "#//#")
    {
        vector<string> vCurrencyData = ClsString::splitString(line, separator);

        return ClsCurrency(enMode::updateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
                           stod(vCurrencyData[3]));
    }

    static string _convertCurrencyObjectToLine(ClsCurrency currency, string separator = "#//#")
    {
        string stCurrencyRecord = "";
        stCurrencyRecord += currency.country() + separator;
        stCurrencyRecord += currency.currencyCode() + separator;
        stCurrencyRecord += currency.currencyName() + separator;
        stCurrencyRecord += to_string(currency.rate());

        return stCurrencyRecord;
    }

    static vector<ClsCurrency> _loadCurrenciesDataFromFile()
    {
        vector<ClsCurrency> vCurrencies;
        fstream myFile;
        myFile.open("Data/Currencies.txt", ios::in);

        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                ClsCurrency currency = _convertLineToCurrencyObject(line);
                vCurrencies.push_back(currency);
            }
            myFile.close();
        }
        return vCurrencies;
    }

    static void _saveCurrencyDataToFile(vector<ClsCurrency> vCurrencies)
    {
        fstream myFile;
        myFile.open("Data/Currencies.txt", ios::out);

        if (myFile.is_open())
        {
            for (ClsCurrency c : vCurrencies)
            {
                myFile << _convertCurrencyObjectToLine(c) << endl;
            }
            myFile.close();
        }
    }

    void _update()
    {
        vector<ClsCurrency> vCurrencies = _loadCurrenciesDataFromFile();

        for (ClsCurrency &c : vCurrencies)
        {
            if (c.currencyCode() == currencyCode())
            {
                c = *this;
                break;
            }
        }
        _saveCurrencyDataToFile(vCurrencies);
    }

    static ClsCurrency _getEmptyCurrencyObject()
    {
        return ClsCurrency(enMode::emptyMode, "", "", "", 0);
    }

public:
    ClsCurrency(enMode mode, string country, string currencyCode, string currencyName, float rate)
    {
        _mode = mode;
        _country = country;
        _currencyCode = currencyCode;
        _currencyName = currencyName;
        _rate = rate;
    }

    static vector<ClsCurrency> getAllUSDRates()
    {
        return _loadCurrenciesDataFromFile();
    }

    bool isEmpty()
    {
        return (_mode == enMode::emptyMode);
    }

    string country()
    {
        return _country;
    }

    string currencyCode()
    {
        return _currencyCode;
    }

    string currencyName()
    {
        return _currencyName;
    }

    void updateRate(float newRate)
    {
        _rate = newRate;
        _update();
    }

    float rate()
    {
        return _rate;
    }

    static ClsCurrency findByCode(string currencyCode)
    {
        currencyCode = ClsString::upperAllString(currencyCode);

        fstream myFile;
        myFile.open("Data/Currencies.txt", ios::in);

        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                ClsCurrency currency = _convertLineToCurrencyObject(line);
                if (currency.currencyCode() == currencyCode)
                {
                    myFile.close();
                    return currency;
                }
            }
            myFile.close();
        }
        return _getEmptyCurrencyObject();
    }

    static ClsCurrency findByCountry(string country)
    {
        country = ClsString::upperAllString(country);

        fstream myFile;
        myFile.open("Data/Currencies.txt", ios::in);

        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                ClsCurrency currency = _convertLineToCurrencyObject(line);
                if (ClsString::upperAllString(currency.country()) == country)
                {
                    myFile.close();
                    return currency;
                }
            }
            myFile.close();
        }
        return _getEmptyCurrencyObject();
    }

    static bool isCurrencyExist(string currencyCode)
    {
        ClsCurrency c1 = ClsCurrency::findByCode(currencyCode);
        return (!c1.isEmpty());
    }

    static vector<ClsCurrency> getCurrenciesList()
    {
        return _loadCurrenciesDataFromFile();
    }

    float convertTo(float amount, ClsCurrency targetCurrency)
    {
        float amountInUSD = amount / rate();

        if (targetCurrency.currencyCode() == "USD")
        {
            return amountInUSD;
        }

        return amountInUSD * targetCurrency.rate();
    }
};