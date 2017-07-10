//
//  BillParser.cpp
//  BillParser
//
//  Created by Ling on 17/6/19.
//  Copyright © 2017年 Ling. All rights reserved.
//

#include "BillParser.hpp"

#include "CibcVisaBillParser.hpp"
#include "PcBillParser.hpp"
#include "SpendingCategorizer.hpp"
#include "Utility.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void BillParser::parse(const std::string &fileName)
{
    if (isSubStringOf("pc", fileName))
        PcBillParser::parse(fileName, spendingRecords);
    else if (isSubStringOf("cibc_visa", fileName))
        CibcVisaBillParser::parse(fileName, spendingRecords);
}

void BillParser::printSpendingRecords(const bool showDetails) const
{
    map<string, vector<SpendingEntry>> monthToSpending = getSpendingsByMonth();
    
    auto sortedmonthToSpending = getSorted(monthToSpending);
    
    stringstream ss;

    for (const auto it : sortedmonthToSpending) {
        ss << it.first << endl;
        SpendingCategorizer categorizer(it.second);
        
        int sum;
        const string &incomeStr = categorizer.incomesToStr(sum);
        if (showDetails)
            ss << "<Incomes: " << sum << ">" << endl << incomeStr;
        else
            ss << "Incomes: " << sum << endl;
        
        const string &fixedSpendingStr = categorizer.fixedSpendingsToStr(sum);
        if (showDetails)
            ss << "<Fixed Spendings: " << sum << ">" << endl << fixedSpendingStr;
        else
            ss << "Fixed Spendings: " << sum << endl;
        
        const string &nonFixedSpendingStr = categorizer.nonFixedSpendingsToStr(sum);
        if (showDetails)
            ss << "<Non-fixed Spendings: " << sum << ">" << endl << nonFixedSpendingStr;
        else
            ss << "Non-fixed Spendings: " << sum << endl;
        
        ss << categorizer.unknownSpendingsToStr();
        
        ss << endl;
    }
    
    cout << ss.str();
}

vector<pair<string, vector<SpendingEntry> > > BillParser::getSorted(const map<string, vector<SpendingEntry> > &mp) const
{
    std::vector<std::pair<string, vector<SpendingEntry> > > result;
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        result.push_back(*it);
    }
    
    sort(result.begin(), result.end(), [=](std::pair<string, vector<SpendingEntry> >& a, std::pair<string, vector<SpendingEntry> >& b)
        {
            return stringToNumber(a.first) < stringToNumber(b.first);
        }
    );
    
    return result;
}

map<string, vector<SpendingEntry> > BillParser::getSpendingsByMonth() const
{
    map<std::string, vector<SpendingEntry>> result;
    
    for (auto spending : spendingRecords) {
        const string &monthAndYear = spending.getMonthAndYearStr();
        if (result.find(monthAndYear) == result.end()) {
            result[monthAndYear] = vector<SpendingEntry>();
        }
        result[monthAndYear].push_back(spending);
    }
    
    return result;
}

