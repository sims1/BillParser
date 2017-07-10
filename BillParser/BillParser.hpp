//
//  BillParser.hpp
//  BillParser
//
//  Created by Ling on 17/6/19.
//  Copyright © 2017年 Ling. All rights reserved.
//

#pragma once

#include "SpendingEntry.hpp"
#include "SpendingKind.hpp"

#include <map>
#include <string>
#include <vector>

class BillParser
{
public:
    BillParser() = default;
    ~BillParser() = default;
    
    void parse(const std::string &);
    void printSpendingRecords(const bool showDetails) const;
    
private:
    std::map<std::string, std::vector<SpendingEntry> > getSpendingsByMonth() const;
    
    std::vector<std::pair<std::string, std::vector<SpendingEntry> > > getSorted(const std::map<std::string, std::vector<SpendingEntry> > &) const;
    
    /// for debugging purpose
    void printSpendingRecord() const;
private:
    std::vector<SpendingEntry> spendingRecords;
};
