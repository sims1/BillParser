//
//  main.cpp
//  BillParser
//
//  Created by Ling on 17/6/19.
//  Copyright © 2017年 Ling. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

#include "BillParser.hpp"

int main(int argc, const char * argv[]) {
    const std::string pc2017 = "/Users/ling/GitHub/BillParser/pc_2017.txt";
    const std::string cibc2017 = "/Users/ling/GitHub/BillParser/cibc_visa_2017.txt";
    
    BillParser billParser;
    billParser.parse(pc2017);
    billParser.parse(cibc2017);
    
    billParser.printSpendingRecords(true);
 
    return 0;
}
