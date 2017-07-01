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
#include "Utility.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

std::vector<std::string> BillParser::fixedSpendingNames =
{
    // pc spending
    "HYDRO BILL PAYMENT HYDRO OTTAWA",
    "INSURANCE Cooperators CSI",
    "MISCELLANEOUS PAYMENTS GOODLIFE FITNESS CLUBS",
    "TELEPHONE BILL PAYMENT FIDO MOBILE",
    "TELEPHONE BILL PAYMENT FIDO HOME",
    "UTILITY BILL PAYMENT RELIANCECOMFORT"
};

std::vector<std::string> BillParser::incomeNames =
{
    // pc income
    "BANK TO BANK TSF EXT TSF FR 5577594"
};

BillParser::BillParser(const std::string &fileName)
{
    std::vector<SpendingEntry> records;
    
    if (isSubStringOf("pc", fileName))
        PcBillParser::parse(fileName, records);
    else if (isSubStringOf("cibc_visa", fileName))
        CibcVisaBillParser::parse(fileName, records);
    
    spendingRecords = records;
    
    categorizeFixedSpendings();
}

void BillParser::printSpendingRecord() const
{
    for (const auto &it : spendingRecords)
        cout << it.toStr() << endl;
}

std::string BillParser::getFixedSpendingName(const SpendingEntry &record) const
{
    for(const auto &fixedSpending : fixedSpendingNames) {
        if (record.is(fixedSpending))
            return fixedSpending;
    }
    return "";
}

std::string BillParser::getIncomeName(const SpendingEntry &record) const
{
    for(const auto &income : incomeNames) {
        if (record.is(income))
            return income;
    }
    return "";
}

void BillParser::categorizeFixedSpendings()
{
    for (const auto &record : spendingRecords) {
        const string incomeName = getIncomeName(record);
        if (incomeName != "") {
            if (incomes.find(incomeName) == incomes.end())
                incomes[incomeName] = SpendingKind(incomeName);
            incomes[incomeName].addEntry(record);
            continue;
        }
        
        const string fixedSpendingName = getFixedSpendingName(record);
        if (fixedSpendingName == "") {
            nonFixedSpendings.push_back(record);
            continue;
        }
        
        // record is fixed spending
        if (fixedSpendings.find(fixedSpendingName) == fixedSpendings.end())
            fixedSpendings[fixedSpendingName] = SpendingKind(fixedSpendingName);
        
        fixedSpendings[fixedSpendingName].addEntry(record);
    }
}

map<string, vector<SpendingEntry>> BillParser::categorizeSpendingsByMonths()
{
    map<std::string, vector<SpendingEntry>> result;
    
    for (auto spending : nonFixedSpendings) {
        if (!spending.isSpending())
            continue;
        
        const string &monthAndYear = spending.getMonthAndYearStr();
        if (result.find(monthAndYear) == result.end()) {
            result[monthAndYear] = vector<SpendingEntry>();
        }
        result[monthAndYear].push_back(spending);
    }
    
    return result;
}

string BillParser::incomesToStr() const
{
    stringstream ss;
    
    ss << "<<< Incomes >>>" << endl;
    for(const auto &it : incomes) {
        ss << it.second.getSummary(false);
    }
    return ss.str();
}

string BillParser::fixedSpendingsToStr() const
{
    stringstream ss;
    
    ss << "<<< Fixed Spendings >>>" << endl;
    for(const auto &it : fixedSpendings) {
        ss << it.second.getSummary(false);
    }
    return ss.str();
}

string BillParser::nonfixedSpendingsToStr() const
{
    stringstream ss;
    
    ss << "<<<Non Fixed Spendings >>>" << endl;
    for(const auto &it : nonFixedSpendings) {
        ss << it.toStr() << endl;
    }
    return ss.str();
}


