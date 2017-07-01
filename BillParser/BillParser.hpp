//
//  BillParser.hpp
//  BillParser
//
//  Created by Ling on 17/6/19.
//  Copyright © 2017年 Ling. All rights reserved.
//

#ifndef BillParser_hpp
#define BillParser_hpp

#include "SpendingEntry.hpp"
#include "SpendingKind.hpp"

#include <map>
#include <string>
#include <vector>

class BillParser
{
public:
    BillParser(const std::string &);
    ~BillParser() = default;
    
    std::string incomesToStr() const;
    std::string fixedSpendingsToStr() const;
    std::string nonfixedSpendingsToStr() const;
    
private:
    std::string getFixedSpendingName(const SpendingEntry &) const;
    std::string getIncomeName(const SpendingEntry &) const;
    
    void categorizeFixedSpendings();
    
    /// for debugging purpose
    void printSpendingRecord() const;
private:
    std::vector<SpendingEntry> spendingRecords;
    std::map<std::string, SpendingKind> fixedSpendings;
    std::map<std::string, SpendingKind> incomes;
    std::vector<SpendingEntry> nonFixedSpendings;
    
    std::map<std::string, std::vector<SpendingEntry> > categorizeSpendingsByMonths();
    
private:
    static std::vector<std::string> fixedSpendingNames;
    static std::vector<std::string> incomeNames;
};

#endif /* BillParser_hpp */
