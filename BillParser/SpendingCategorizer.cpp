//
//  SpendingCategorizer.cpp
//  BillParser
//
//  Created by Ling on 17/7/1.
//  Copyright © 2017年 Ling. All rights reserved.
//

#include "SpendingCategorizer.hpp"

#include <iostream>
#include <sstream>

using namespace std;

std::vector<std::string> SpendingCategorizer::fixedSpendingNames =
{
    // pc spending
    "HYDRO BILL PAYMENT HYDRO OTTAWA",
    "INSURANCE Cooperators CSI",
    "MISCELLANEOUS PAYMENTS GOODLIFE FITNESS CLUBS",
    "TELEPHONE BILL PAYMENT FIDO MOBILE",
    "TELEPHONE BILL PAYMENT FIDO HOME",
    "UTILITY BILL PAYMENT RELIANCECOMFORT",
    
    // cibc spending
    "Personal & Household Expenses NETFLIX.COM 866-716-0414, ON",
};

std::vector<std::string> SpendingCategorizer::incomeNames =
{
    // pc income
    "INTEREST"
};

std::map<std::string, NonFixedSpendingKind> SpendingCategorizer::nonFixedSpendingNames =
{
    {"Transportation SPEEDY GLASS #8131 OTTAWA, ON", CAR},
    
    {"ABM WITHDRAWAL", CASH},
    
    {"POS MERCHANDISE THE OTTAWA HUMA", CLOTHES},
    {"Retail and Grocery CLAIRES #2727 KANATA, ON", CLOTHES},
    {"Retail and Grocery DYNAMITE # 317 TORONTO, ON", CLOTHES},
    {"Retail and Grocery GAP OUTLET - CANADA / OTTAWA, ON", CLOTHES},
    {"Retail and Grocery GARAGE/DYNAMITE #31 OTTAWA, ON", CLOTHES},
    {"Retail and Grocery KATE SPADE HALTON HILL GEORGETOWN, ON", CLOTHES},
    {"Retail and Grocery NINE WEST SHOE STUDIO KANATA, ON", CLOTHES},
    {"Retail and Grocery WINNERS 339 TORONTO, ON", CLOTHES},
    {"Retail and Grocery ZARA TEC #3194 TORONTO, ON", CLOTHES},
    
    
    {"Hotels, Entertainment, and Recreation CANADA'S WONDERLAND-RE MAPLE, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation CANADA'S WONDERLAND-FR MAPLE, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation CN TOWER RETAIL STORE TORONTO, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation LANDMARK 24 KANATA KANATA, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation RIPLEYS AQUARIUM TORONTO, ON", ENTERTAIN},
    
    {"Home & Office Improvement IKEA OTTAWA OTTAWA, ON", FURNITURE},
    
    {"Transportation ONROUTE #01170 BRIGHTON, ON", GAS},
    {"Transportation PETROCAN KANATA, ON", GAS},
    {"Transportation PETROCAN MISSISSAUGA, ON", GAS},
    {"Transportation PETROCAN WILLOWDALE, ON", GAS},
    
    {"POS MERCHANDISE COSTCO WHOLESAL", GROCERY},
    {"POS MERCHANDISE DOLLARAMA #0977", GROCERY},
    {"POS MERCHANDISE DOLLARAMA # 352", GROCERY},
    {"POS MERCHANDISE T&T SUPERMARKET", GROCERY},
    {"POS MERCHANDISE LOBLAWS #1114", GROCERY},
    {"Health & Education SHOPPERS DRUG MART #08 TORONTO, ON", GROCERY},
    {"Retail and Grocery BULK BARN #507 KANATA, ON", GROCERY},
    {"Retail and Grocery COSTCO WHOLESALE W541 KANATA, ON", GROCERY},
    {"Retail and Grocery DOLLARAMA # 352 KANATA, ON", GROCERY},
    {"Retail and Grocery FOOD BASICS #869 KANATA, ON", GROCERY},
    {"Retail and Grocery LA PROVENCE BAKE SHOP KANATA, ON", GROCERY},
    {"Retail and Grocery LOBLAWS 95.3 OTTAWA, ON", GROCERY},
    {"Retail and Grocery LOBLAWS #1114 KANATA, ON", GROCERY},
    {"Retail and Grocery SOBEYS #4734 KANATA, ON", GROCERY},
    {"Retail and Grocery TONE TAI SUPERMARKET NORTH YORK, ON", GROCERY},
    {"Retail and Grocery T&T SUPERMARKET #011 MARKHAM, ON", GROCERY},
    {"Retail and Grocery T&T SUPERMARKET #018 OTTAWA, ON", GROCERY},

    
    {"POS MERCHANDISE EMBASSY OF THE", IMMIGRATION},
    {"POS MERCHANDISE IMMIGRATION MED", IMMIGRATION},
    {"Professional and Financial Services LAW OFFICE OF RONALEE 613-2779401, ON", IMMIGRATION},
    
    {"POS MERCHANDISE LA NOODLE", RESTAURANT},
    {"POS MERCHANDISE ORIENTAL RICE N", RESTAURANT},
    {"POS MERCHANDISE SUBWAY # 6521", RESTAURANT},
    {"Restaurants AI2-NU CARIBBEAN KANATA, ON", RESTAURANT},
    {"Restaurants CAFE CREPE TORONTO, ON", RESTAURANT},
    {"Restaurants CHATIME NORTH YORK, ON", RESTAURANT},
    {"Restaurants CHONGQING LIUYISHOU HO NEPEAN, ON", RESTAURANT},
    {"Restaurants DARCY MCGEES #5837 OTTAWA, ON", RESTAURANT},
    {"Restaurants FORTUNE EXPRESS RESTAU KANATA, ON", RESTAURANT},
    {"Restaurants FULL HOUSE ASIAN CUISI OTTAWA, ON", RESTAURANT},
    {"Restaurants HOCKEY SUSHI KANATA, ON", RESTAURANT},
    {"Restaurants IKEA OTTAWA OTTAWA, ON", RESTAURANT},
    {"Restaurants KANATA NOODLE HOUSE KANATA, ON", RESTAURANT},
    {"Restaurants KFC/TACO BELL #1416 KANATA, ON", RESTAURANT},
    {"Restaurants MCDONALD'S #3211 BROCKVILLE, ON", RESTAURANT},
    {"Restaurants SUBWAY 13794 KANATA, ON", RESTAURANT},
    {"Restaurants SUBWAY #6521 OTTAWA, ON", RESTAURANT},
    {"Restaurants TABLE 85 CAFE & CATERI OTTAWA, ON", RESTAURANT},
    {"Restaurants THE MONGOLIAN VILLAGE NEPEAN, ON", RESTAURANT},
    {"Restaurants TSUJIRI TEA HOUSE TORONTO, ON", RESTAURANT},
    
};

std::vector<std::string> SpendingCategorizer::ignoredNames =
{
    // pc income
    "BANK TO BANK TSF EXT TSF FR 5577594",
};

SpendingCategorizer::SpendingCategorizer(const std::vector<SpendingEntry> spendings)
: spendings(spendings)
{
    categorizeSpendings();
}

std::string SpendingCategorizer::getIncomeName(const SpendingEntry &record) const
{
    for(const auto &income : incomeNames) {
        if (record.is(income))
            return income;
    }
    return "";
}

std::string SpendingCategorizer::getFixedSpendingName(const SpendingEntry &record) const
{
    for(const auto &fixedSpending : fixedSpendingNames) {
        if (record.is(fixedSpending))
            return fixedSpending;
    }
    return "";
}

std::string SpendingCategorizer::getNonFixedSpendingName(const SpendingEntry &record) const
{
    for(const auto &nonFixedSpending : nonFixedSpendingNames) {
        if (record.is(nonFixedSpending.first))
            return NonFixedSPendingKindToStr(nonFixedSpending.second);
    }
    return "";
}

std::string SpendingCategorizer::getIgnoredName(const SpendingEntry &record) const
{
    for(const auto &ignoredSpending : ignoredNames) {
        if (record.is(ignoredSpending))
            return ignoredSpending;
    }
    return "";
}

std::string SpendingCategorizer::NonFixedSPendingKindToStr(const NonFixedSpendingKind &kind) const
{
    switch(kind) {
        case CAR:
            return "Car";
        case CASH:
            return "Cash";
        case CLOTHES:
            return "Clothes";
        case ENTERTAIN:
            return "Entertain";
        case FURNITURE:
            return "Furniture";
        case GAS:
            return "Gas";
        case GROCERY:
            return "Grocery";
        case IMMIGRATION:
            return "Immigration";
        case RESTAURANT:
            return "Restaurant";
        default:
            return "unknown_NonFixedSPendingKind";
    }
};

void SpendingCategorizer::categorizeSpendings()
{
    for (const auto &spending : spendings) {
        
        const string incomeName = getIncomeName(spending);
        if (incomeName != "") {
            if (incomes.find(incomeName) == incomes.end())
                incomes[incomeName] = SpendingKind(incomeName);
            incomes[incomeName].addEntry(spending);
            continue;
        }
        
        const string fixedSpendingName = getFixedSpendingName(spending);
        if (fixedSpendingName != "") {
            if (fixedSpendings.find(fixedSpendingName) == fixedSpendings.end())
                fixedSpendings[fixedSpendingName] = SpendingKind(fixedSpendingName);
            fixedSpendings[fixedSpendingName].addEntry(spending);
            continue;
        }
        
        const string &nonFixedSpendingName = getNonFixedSpendingName(spending);
        if (nonFixedSpendingName != "") {
            if (nonFixedSpendings.find(nonFixedSpendingName) == nonFixedSpendings.end())
                nonFixedSpendings[nonFixedSpendingName] = SpendingKind(nonFixedSpendingName);
            nonFixedSpendings[nonFixedSpendingName].addEntry(spending);
            continue;
        }
        
        const string &ignoredName = getIgnoredName(spending);
        if (ignoredName != "") {
            continue;
        }
        
        
            
        unknownSpendings.push_back(spending);
    }
}

string SpendingCategorizer::incomesToStr(int &sum) const
{
    sum = 0;
    
    stringstream ss;
    for(const auto &it : incomes) {
        ss << it.second.getSummary(false);
        sum += it.second.getSum();
    }
    return ss.str();
}

string SpendingCategorizer::fixedSpendingsToStr(int &sum) const
{
    sum = 0;
    
    stringstream ss;
    for(const auto &it : fixedSpendings) {
        ss << it.second.getSummary(false);
        sum += it.second.getSum();
    }
    return ss.str();
}

string SpendingCategorizer::nonFixedSpendingsToStr(int &sum) const
{
    sum = 0;
    
    stringstream ss;
    for(const auto &it : nonFixedSpendings) {
        ss << it.second.getSummary(false);
        sum += it.second.getSum();
    }
    return ss.str();
}

string SpendingCategorizer::unknownSpendingsToStr() const
{
    stringstream ss;
    
    ss << "<Unknown Spendings>" << endl;
    for(const auto &it : unknownSpendings) {
        ss << it.toStr() << endl;
    }
    return ss.str();
}
