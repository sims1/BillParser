//
//  SpendingEntry.hpp
//  BillParser
//
//  Created by Ling on 17/6/19.
//  Copyright © 2017年 Ling. All rights reserved.
//

#ifndef SpendingEntry_hpp
#define SpendingEntry_hpp

#include <string>

class SpendingEntry
{
public:
    struct Date {
        int day;
        int month;
        int year;
    };
    
    SpendingEntry(const std::string &);
    
    bool isValid() const;
    
private:
    Date parseDate(const std::string &) const;
    std::string dateToStr() const;
    
private:
    Date date;
    std::string item;
    unsigned int spendingAmount;
    unsigned int balance;
    bool validity;
};



#endif /* SpendingEntry_hpp */

