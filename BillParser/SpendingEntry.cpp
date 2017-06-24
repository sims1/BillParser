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

SpendingEntry::SpendingEntry(const std::string &line)
{
    vector<string> entryList = splitString(line, "\t");
    if (entryList.size() != 4) {
        validity = false;
        return;
    }
    
    date = parseDate(entryList[0]);
    item = entryList[1];
    spendingAmount = stringToNumberWithRounding(entryList[2]);
    balance = stringToNumberWithRounding(entryList[3]);
    
    cout << dateToStr() << " | " << item << " | " << spendingAmount << " | " << balance << endl;
    
    validity = true;
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

bool SpendingEntry::isValid() const
{
    return validity;
}
