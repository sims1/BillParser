//
//  pc_parser.cpp
//  BillParser
//
//  Created by Ling on 17/6/28.
//  Copyright © 2017年 Ling. All rights reserved.
//

#include "PcBillParser.hpp"

#include <fstream>
#include <iostream>

using namespace std;

vector<string> PcBillParser::fixedSpendingNames =
{
    // pc spending
    "HYDRO BILL PAYMENT HYDRO OTTAWA",
    "INSURANCE Cooperators CSI",
    "MISCELLANEOUS PAYMENTS GOODLIFE FITNESS CLUBS",
    "TELEPHONE BILL PAYMENT FIDO MOBILE",
    "TELEPHONE BILL PAYMENT FIDO HOME",
    "UTILITY BILL PAYMENT RELIANCECOMFORT"
};

vector<string> PcBillParser::incomeNames =
{
    // pc income
    "BANK TO BANK TSF EXT TSF FR 5577594"
};

void PcBillParser::parse(const std::string &fileName, std::vector<SpendingEntry> &spendingRecords)
{
    string line;
    ifstream myfile (fileName);
    if (!myfile.is_open()) {
        return;
    }
    
    while (getline(myfile,line)) {
        SpendingEntry spendingEntry(line, SpendingEntry::PC);
        if (!spendingEntry.isValid()) {
            cerr << "Warning: Invalid SpendingEntry read" << endl;
            continue;
        }
        
        spendingRecords.push_back(spendingEntry);
    }
    myfile.close();
    
    for(int i = 0; i < spendingRecords.size()-1; ++i) {
        spendingRecords[i].setProperty(spendingRecords[i+1].getAmount());
    }
    
    if (spendingRecords.size() > 0)
        spendingRecords.pop_back();
}