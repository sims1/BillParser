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
    const std::string fileName = "/Users/ling/GitHub/BillParser/pc_2017.txt";
    //const std::string fileName = "/Users/ling/GitHub/BillParser/cibc_visa_2017.txt";
    
    BillParser billParser(fileName);
    
    cout << billParser.incomesToStr() << endl;
    cout << billParser.fixedSpendingsToStr() << endl;
    cout << billParser.nonfixedSpendingsToStr() << endl;
    
    return 0;
}
