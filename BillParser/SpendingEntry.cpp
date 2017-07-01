//
//  SpendingEntry.cpp
//  BillParser
//
//  Created by Ling on 17/6/19.
//  Copyright © 2017年 Ling. All rights reserved.
//

#include "SpendingEntry.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;

#include "Utility.hpp"

SpendingEntry::SpendingEntry(const std::string &line, const ParseKind parseKind)
: property(NONE)
{
    switch (parseKind) {
        case PC: {
            vector<string> entryList = splitString(line, "\t");
            if (entryList.size() != 4) {
                validity = false;
                return;
            }
    
            date = parseDate(entryList[0]);
            entryName = entryList[1];
            amount = stringToNumberWithRounding(entryList[2]);
            balance = stringToNumberWithRounding(entryList[3]);
    
            validity = true;
            return;
        }
        case CIBC_VISA: {
            vector<string> entryList = splitString(line, "\t");
            
            for (auto i : entryList)
                cout << i << "|";
            cout << endl;
            
            if (entryList.size() != 5) {
                validity = false;
                return;
            }
            
            date = parseDate(entryList[0]);
            entryName = entryList[2];
            if (entryList[4] == "Not applicable") {
                amount = stringToNumberWithRounding(entryList[3]);
                property = SPENDING;
            } else {
                amount = stringToNumberWithRounding(entryList[4]);
                property = INCOME;
            }
                
            balance = 0;  // not available in cibc visa bill
            
            validity = true;
            return;
        }
    }
}

void SpendingEntry::setProperty(const int nextEntryAmount)
{
    const int addition = nextEntryAmount + amount;
    property = ((addition - 1) <= balance && balance <= (addition + 1)) ? INCOME : SPENDING;
    
}

SpendingEntry::Date SpendingEntry::parseDate(const string &str) const
{
    Date result;
    
    vector<string> parsedDate = splitString(str, " ");
    assert(parsedDate.size() == 3);
    
    result.month = monthStringToNumber(parsedDate[0]);
    result.day = stringToNumber(parsedDate[1]);
    result.year = stringToNumber(parsedDate[2]);
    
    assert(1 <= result.month && result.month <= 12);
    assert(1 <= result.day && result.day <= 31);
    assert(2000 <= result.year && result.year <= 3000); // plan until year 3000 :-)
    
    return result;
}

string SpendingEntry::dateToStr() const
{
    stringstream ss;
    ss << date.month << "-" << date.day << "-" << date.year;
    return ss.str();
}

std::string SpendingEntry::getMonthAndYearStr() const
{
    stringstream ss;
    ss << date.month << "-" << date.year;
    return ss.str();
}

string SpendingEntry::propertyToStr() const
{
    switch(property) {
        case NONE:
            return "NONE";
        case SPENDING:
            return "SPENDING";
        case INCOME:
            return "INCOME";
        default:
            return "ERROR_property";
    }
}

string SpendingEntry::toStr() const
{
    if (!validity)
        return "Invalid";
    
    stringstream ss;
    
    ss << propertyToStr();
    ss << "|" << dateToStr();
    ss << "|" << entryName;
    ss << "|" << amount;
    //ss << "|" << balance;
    
    return ss.str();
}

bool SpendingEntry::is(const std::string &name) const
{
    return entryName.compare(name) == 0;
}

int SpendingEntry::getAmount() const
{
    return amount;
}

bool SpendingEntry::isSpending() const
{
    return property == SPENDING;
}

bool SpendingEntry::isValid() const
{
    return validity;
}
