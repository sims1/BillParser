//
//  SpendingCategorizer.hpp
//  BillParser
//
//  Created by Ling on 17/7/1.
//  Copyright © 2017年 Ling. All rights reserved.
//

#pragma once

#include "SpendingEntry.hpp"
#include "SpendingKind.hpp"

#include <map>
#include <vector>

enum NonFixedSpendingKind {
    BEAUTY,
    CAR,
    CASH,
    CLOTHES,
    ENTERTAIN,
    FURNITURE,
    GAS,
    GROCERY,
    IMMIGRATION,
    PET,
    RESTAURANT,
    UNKNOWN
};

class SpendingCategorizer
{
public:
    SpendingCategorizer(const std::vector<SpendingEntry>);

    std::string incomesToStr(int &sum) const;
    std::string fixedSpendingsToStr(int &sum) const;
    std::string nonFixedSpendingsToStr(int &sum) const;
    std::string unknownSpendingsToStr() const;
    
private:

    void categorizeSpendings();
    
    std::string getIncomeName(const SpendingEntry &) const;
    std::string getFixedSpendingName(const SpendingEntry &) const;
    std::string getNonFixedSpendingName(const SpendingEntry &) const;
    std::string getIgnoredName(const SpendingEntry &) const;
    
    std::string NonFixedSPendingKindToStr(const NonFixedSpendingKind &) const;
    
    
    std::map<std::string, std::vector<SpendingEntry> > categorizeSpendingsByMonths();
    
private:
    std::vector<SpendingEntry> spendings;
    std::map<std::string, SpendingKind> fixedSpendings;
    std::map<std::string, SpendingKind> incomes;
    std::map<std::string, SpendingKind> nonFixedSpendings;
    std::vector<SpendingEntry> unknownSpendings;
    
    static std::vector<std::string> incomeNames;
    static std::vector<std::string> fixedSpendingNames;
    static std::vector<std::string> ignoredNames;
    static std::map<std::string, NonFixedSpendingKind> nonFixedSpendingNames;
    
};