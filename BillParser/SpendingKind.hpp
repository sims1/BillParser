//
//  SpendingKind.hpp
//  BillParser
//
//  Created by Ling on 17/6/24.
//  Copyright © 2017年 Ling. All rights reserved.
//

#pragma once

#include "SpendingEntry.hpp"

#include <string>
#include <vector>

class SpendingKind {
public:
    SpendingKind() = default;
    SpendingKind(const std::string &);
    void addEntry(const SpendingEntry &);
    
    int getSum() const;
    
    std::string getSummary(const bool withDates) const;
    
private:
    std::string name;
    std::vector<SpendingEntry> spendings;
};