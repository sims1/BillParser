//
//  SpendingKind.cpp
//  BillParser
//
//  Created by Ling on 17/6/24.
//  Copyright © 2017年 Ling. All rights reserved.
//

#include "SpendingKind.hpp"

#include <sstream>

using namespace std;

SpendingKind::SpendingKind(const std::string &n)
: name(n)
{}

void SpendingKind::addEntry(const SpendingEntry &entry)
{
    spendings.push_back(entry);
}

int SpendingKind::getSum() const
{
    int result = 0;
    for (const auto &it : spendings)
        result += it.getAmount();
    return result;
}

string SpendingKind::getSummary(const bool withDates) const
{
    stringstream ss;
    
    ss << name << ": " << getSum() << endl;
    
    if (withDates) {
        for (const auto &it : spendings)
            ss << it.dateToStr() << " " << it.getAmount() << endl;
    }
    
    return ss.str();
}