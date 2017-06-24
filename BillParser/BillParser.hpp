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

#include <string>
#include <vector>

class BillParser
{
public:
    BillParser(const std::string &);
    
private:
    std::vector<SpendingEntry> spendingRecord;
};

#endif /* BillParser_hpp */
