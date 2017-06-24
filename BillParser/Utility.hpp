//
//  Utility.hpp
//  BillParser
//
//  Created by Ling on 17/6/19.
//  Copyright © 2017年 Ling. All rights reserved.
//

#ifndef Utility_hpp
#define Utility_hpp

#include <string>
#include <vector>

std::vector<std::string> splitString(const std::string &, const std::string);

int stringToNumber(const std::string &);
float stringToNumberWithRounding(const std::string &str);

int monthStringToNumber(const std::string &);

#endif /* Utility_hpp */
