//
//  CibcVisaBillParser.hpp
//  BillParser
//
//  Created by Ling on 17/6/28.
//  Copyright © 2017年 Ling. All rights reserved.
//

#pragma once

#include <vector>

#include "SpendingEntry.hpp"

class CibcVisaBillParser {
public:
    static void parse(const std::string &, std::vector<SpendingEntry> &);
    
};