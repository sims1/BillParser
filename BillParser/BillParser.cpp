//
//  BillParser.cpp
//  BillParser
//
//  Created by Ling on 17/6/19.
//  Copyright © 2017年 Ling. All rights reserved.
//

#include "BillParser.hpp"

#include <fstream>
#include <iostream>
using namespace std;


BillParser::BillParser(const std::string &fileName)
{
    string line;
    ifstream myfile (fileName);
    if (!myfile.is_open()) {
        return;
    }
    
    std::vector<SpendingEntry> rawSpendingRecord;
    while (getline(myfile,line))
    {
        SpendingEntry spendingEntry(line);
        if (!spendingEntry.isValid()) {
            cerr << "Error: Invalid SpendingEntry Found" << endl;
            continue;
        }
        
        rawSpendingRecord.push_back(spendingEntry);

    }
    myfile.close();
    
}
