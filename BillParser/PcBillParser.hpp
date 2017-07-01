//
//  pc_parser.hpp
//  BillParser
//
//  Created by Ling on 17/6/28.
//  Copyright © 2017年 Ling. All rights reserved.
//

#pragma once

#include "SpendingEntry.hpp"

#include <vector>

class PcBillParser {
public:
    static void parse(const std::string &, std::vector<SpendingEntry> &);
private:
    static std::vector<std::string> fixedSpendingNames;
    static std::vector<std::string> incomeNames;
};