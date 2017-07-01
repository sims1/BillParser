//
//  Utility.cpp
//  BillParser
//
//  Created by Ling on 17/6/19.
//  Copyright © 2017年 Ling. All rights reserved.
//

#include "Utility.hpp"

//#include <string.h>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
using namespace std;


std::vector<std::string> splitString(const string &str, const string separator)
{
    std::vector<std::string> result;
    
    char* cstr = const_cast<char*>(str.c_str());
    char* current=strtok(cstr,separator.c_str());
    while(current != NULL) {
        result.push_back(current);
        current = strtok(NULL, separator.c_str());
    }
    return result;
}

bool isSubStringOf(const std::string &substring, const std::string &str)
{
    return (str.find(substring) != std::string::npos);
}
    
int stringToNumber(const string &str)
{
    assert(str.length() < 10);
    
    unsigned int result = 0U;
    
    const char* cstr = str.c_str();
    for (int i = 0; i < str.length(); ++i) {
        switch (cstr[i]) {
            case '0':
                result = result*10;
                break;
            case '1':
                result = result*10 + 1;
                break;
            case '2':
                result = result*10 + 2;
                break;
            case '3':
                result = result*10 + 3;
                break;
            case '4':
                result = result*10 + 4;
                break;
            case '5':
                result = result*10 + 5;
                break;
            case '6':
                result = result*10 + 6;
                break;
            case '7':
                result = result*10 + 7;
                break;
            case '8':
                result = result*10 + 8;
                break;
            case '9':
                result = result*10 + 9;
                break;
            default:
                continue;
        }
    }
    return result;
}

int monthStringToNumber(const string &str)
{
    string upperCaseStr = str;
    transform(upperCaseStr.begin(), upperCaseStr.end(), upperCaseStr.begin(), ::toupper);
    
    assert(upperCaseStr.length() == 3);
    
    if (upperCaseStr == "JAN")
        return 1;
    if (upperCaseStr == "FEB")
        return 2;
    if (upperCaseStr == "MAR")
        return 3;
    if (upperCaseStr == "APR")
        return 4;
    if (upperCaseStr == "MAY")
        return 5;
    if (upperCaseStr == "JUN")
        return 6;
    if (upperCaseStr == "JUL")
        return 7;
    if (upperCaseStr == "AUG")
        return 8;
    if (upperCaseStr == "SEP")
        return 9;
    if (upperCaseStr == "OCT")
        return 10;
    if (upperCaseStr == "NOV")
        return 11;
    if (upperCaseStr == "DEC")
        return 12;
    return 13;
}

float stringToNumberWithRounding(const string &str)
{
    vector<string> numberPair = splitString(str, ".");
    assert(numberPair.size() == 2);
    
    bool isRounding = (numberPair[1].size() != 0 && 5 <= (numberPair[1].at(0) - '0') && (numberPair[1].at(0) - '0') < 9);

    return stringToNumber(numberPair[0]) + isRounding;
    
}

