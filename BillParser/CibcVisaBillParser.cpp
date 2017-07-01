//
//  CibcVisaBillParser.cpp
//  BillParser
//
//  Created by Ling on 17/6/28.
//  Copyright © 2017年 Ling. All rights reserved.
//

#include "CibcVisaBillParser.hpp"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void CibcVisaBillParser::parse(const std::string &fileName, std::vector<SpendingEntry> &spendingRecords)
{
    string line;
    ifstream myfile (fileName);
    if (!myfile.is_open()) {
        return;
    }
    
    while (getline(myfile,line)) {
        SpendingEntry spendingEntry(line, SpendingEntry::CIBC_VISA);
        if (!spendingEntry.isValid()) {
            cerr << "Warning: Invalid SpendingEntry read" << endl;
            continue;
        }
        
        spendingRecords.push_back(spendingEntry);
    }
    myfile.close();
}