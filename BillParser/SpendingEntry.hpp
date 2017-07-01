//
//  SpendingEntry.hpp
//  BillParser
//
//  Created by Ling on 17/6/19.
//  Copyright © 2017年 Ling. All rights reserved.
//

#pragma once

#include <string>

class SpendingEntry
{
public:
    struct Date {
        int day;
        int month;
        int year;
    };
    
    enum EntryKind {
        NONE, SPENDING, INCOME
    };
    
    enum ParseKind {
        PC, CIBC_VISA
    };
    
public:
    SpendingEntry(const std::string &, const ParseKind);
    void setProperty(const int nextEntryAmount);
    
    int getAmount() const;
    bool isSpending() const;
    bool isValid() const;
    std::string dateToStr() const;
    std::string getMonthAndYearStr() const;
    std::string toStr() const;
    
    bool is(const std::string &) const;
    
private:
    Date parseDate(const std::string &) const;
    std::string propertyToStr() const;
    
private:
    Date date;
    std::string entryName;
    unsigned int amount;
    unsigned int balance;
    bool validity;
    EntryKind property;
};


