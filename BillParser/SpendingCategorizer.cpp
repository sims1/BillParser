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
    "MISCELLANEOUS PAYMENTS GOODLIFE FITNESS CENTRES INC",
};

std::vector<std::string> SpendingCategorizer::incomeNames =
{
    // pc income
    "INTEREST",
};

std::map<std::string, NonFixedSpendingKind> SpendingCategorizer::nonFixedSpendingNames =
{
    {"Health & Education SHOPPERSDRUGMART0909 KANATA, ON", BEAUTY},
    {"Health & Education SHOPPER'S DRUG MART #1 KANATA, ON", BEAUTY},
    
    {"Transportation MYERS INFINITI NISSAN NEPEAN, ON", CAR},
    {"Transportation SPEEDY GLASS #8131 OTTAWA, ON", CAR},
    {"Transportation UBER CA MAR18 6FSKI HE help.uber.com, NLD", CAR},
    {"Professional and Financial Services 31-000 CITY OF OTTAWA KANATA, ON", CAR},
    {"Professional and Financial Services MYERS NISSAN INFINITI OTTAWA, ON", CAR},
    
    {"ABM WITHDRAWAL", CASH},
    
    {"POS MERCHANDISE THE OTTAWA HUMA", CLOTHES},
    {"Personal & Household Expenses GIRLS COSMETICS OTTAWA, ON", CLOTHES},
    {"Retail and Grocery ARITZIA YORKDALE 1301 TORONTO, ON", CLOTHES},
    {"Retail and Grocery CLAIRES #2727 KANATA, ON", CLOTHES},
    {"Retail and Grocery DYNAMITE # 317 TORONTO, ON", CLOTHES},
    {"Retail and Grocery FOOTACTION #99307 TORONTO, ON", CLOTHES},
    {"Retail and Grocery FOREVER 21 #390 TORONTO, ON", CLOTHES},
    {"Retail and Grocery GAP OUTLET - CANADA / OTTAWA, ON", CLOTHES},
    {"Retail and Grocery GARAGE/DYNAMITE #31 OTTAWA, ON", CLOTHES},
    {"Retail and Grocery HUDSON'S BAY #1554 NORTH YORK, ON", CLOTHES},
    {"Retail and Grocery KATE SPADE HALTON HILL GEORGETOWN, ON", CLOTHES},
    {"Hotels, Entertainment, and Recreation PUMA OTTAWA OTTAWA, ON", CLOTHES},
    {"Retail and Grocery LA SENZA EXPRESS # 641 NEPEAN, ON", CLOTHES},
    {"Retail and Grocery POLO FACTORY STORE/OTT KANATA, ON", CLOTHES},
    {"Retail and Grocery SAKS FIFTH AVENUE #731 OTTAWA, ON", CLOTHES},
    {"Retail and Grocery SAKS OFF 5TH #7315 OTTAWA, ON", CLOTHES},
    {"Retail and Grocery SOFTMOC 314 OTTAWA, ON", CLOTHES},
    {"Retail and Grocery NIKE CANADA KANATA OTTAWA, ON", CLOTHES},
    {"Retail and Grocery NINE WEST SHOE STUDIO KANATA, ON", CLOTHES},
    {"Retail and Grocery WHITE HOUSE BLACK MARK NEPEAN, ON", CLOTHES},
    {"Retail and Grocery WINNERS 339 TORONTO, ON", CLOTHES},
    {"Retail and Grocery ZARA TEC #3194 TORONTO, ON", CLOTHES},

    {"Home & Office Improvement CDN TIRE STORE #00457 KANATA, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation #266 SPORT CHEK KANATA, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation CAMP FORTUNE/MOORSIDE CHELSEA, QC", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation CANADA'S WONDERLAND-RE MAPLE, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation CANADA'S WONDERLAND-FR MAPLE, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation CINEPLEX #7311 OTTAWA, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation CN TOWER RETAIL STORE TORONTO, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation LANDMARK 24 KANATA KANATA, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation KUNSTADT SPORTS KANATA, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation NBX*ANNA BELANGER & AS OTTAWA, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation SPORT CHEK #266 KANATA, ON", ENTERTAIN},
    {"Hotels, Entertainment, and Recreation SPORT CHEK 5166 NEPEAN, ON", ENTERTAIN},
    
    {"Hotels, Entertainment, and Recreation RIPLEYS AQUARIUM TORONTO, ON", ENTERTAIN},
    {"Personal & Household Expenses THE OTTAWA HUMANE SOCI OTTAWA, ON", ENTERTAIN},
    {"Retail and Grocery CHAPTERS 767 OTTAWA, ON", ENTERTAIN},
    {"Retail and Grocery MUJI ATRIUM TORONTO, ON", ENTERTAIN},
    {"Transportation VIA RAIL//MCP940/06MAY MONTREAL, QC", ENTERTAIN},
    
    
    {"Home & Office Improvement BOWRING #903 OTTAWA, ON", FURNITURE},
    {"Home & Office Improvement IKEA OTTAWA OTTAWA, ON", FURNITURE},
    {"Home & Office Improvement STOKES KANATA, ON", FURNITURE},
    
    {"POS MERCHANDISE", GAS},
    {"Transportation CAPITAL PARKING OTTAWA, ON", GAS},
    {"Transportation CITY OF OTTAWA PARKING OTTAWA, ON", GAS},
    {"Transportation ONROUTE #01170 BRIGHTON, ON", GAS},
    {"Transportation PETROCAN KANATA, ON", GAS},
    {"Transportation PETROCAN MISSISSAUGA, ON", GAS},
    {"Transportation PETROCAN WILLOWDALE, ON", GAS},
    
    
    {"Health & Education CANADIAN MEDICAL ALLIA OTTAWA, ON", GROCERY},
    {"Health & Education KANATA PHARMASAVE #761 KANATA, ON", GROCERY},
    {"Health & Education SDM-BEAUTYBOUTIQUE 409 BRAMPTON, ON", GROCERY},
    {"Health & Education SHOPPERS DRUG MART #08 TORONTO, ON", GROCERY},
    {"Health & Education PHARMA PLUS DRUGMARTS KANATA, ON", GROCERY},
    {"Home & Office Improvement TOKYO SHOP OTTAWA, ON", GROCERY},
    {"Personal & Household Expenses KANATA SHOE REPAIR KANATA, ON", GROCERY},
    {"Retail and Grocery BULK BARN #507 KANATA, ON", GROCERY},
    {"Retail and Grocery COSTCO WHOLESALE W541 KANATA, ON", GROCERY},
    {"Retail and Grocery DOLLARAMA # 352 KANATA, ON", GROCERY},
    {"Retail and Grocery FARM BOY #60 KANATA, ON", GROCERY},
    {"Retail and Grocery FOOD BASICS #869 KANATA, ON", GROCERY},
    {"Retail and Grocery HENRY'S KANATA, ON", GROCERY},
    {"Retail and Grocery KOWLOON MARKET OTTAWA, ON", GROCERY},
    {"Retail and Grocery LA PROVENCE BAKE SHOP KANATA, ON", GROCERY},
    {"Retail and Grocery LCBO/RAO #0036 KANATA, ON", GROCERY},
    {"Retail and Grocery LOBLAWS 95.3 OTTAWA, ON", GROCERY},
    {"Retail and Grocery LOBLAWS #1114 KANATA, ON", GROCERY},
    {"Professional and Financial Services PHARMA PLUS DRUGMARTS KANATA, ON", GROCERY},
    {"Retail and Grocery SOBEYS #4734 KANATA, ON", GROCERY},
    {"Retail and Grocery SUGAR MOUNTAIN CONFECT OTTAWA, ON", GROCERY},
    {"Retail and Grocery TONE TAI SUPERMARKET NORTH YORK, ON", GROCERY},
    {"Retail and Grocery T&T SUPERMARKET #011 MARKHAM, ON", GROCERY},
    {"Retail and Grocery T&T SUPERMARKET #018 OTTAWA, ON", GROCERY},
    {"Retail and Grocery WAL-MART #3066 OTTAWA, ON", GROCERY},
    {"Retail and Grocery WAL-MART #3134 KANATA, ON", GROCERY},
    {"Retail and Grocery WALMART.CA Mississauga, ON", GROCERY},
    {"POS MERCHANDISE COSTCO WHOLESAL", GROCERY},
    {"POS MERCHANDISE DOLLARAMA #0977", GROCERY},
    {"POS MERCHANDISE DOLLARAMA # 352", GROCERY},
    {"POS MERCHANDISE T&T SUPERMARKET", GROCERY},
    {"POS MERCHANDISE LOBLAWS #1114", GROCERY},
    {"Professional and Financial Services DYNACARE #XX OTTAWA, ON", GROCERY},
    
    
    
    
    
    {"POS MERCHANDISE EMBASSY OF THE", IMMIGRATION},
    {"POS MERCHANDISE IMMIGRATION MED", IMMIGRATION},
    {"Professional and Financial Services CITIZEN&IMM-EAPPS ENLI OTTAWA, ON", IMMIGRATION},
    {"Professional and Financial Services LAW OFFICE OF RONALEE 613-2779401, ON", IMMIGRATION},
    
    
    {"Home & Office Improvement PETSMART CANADA MISSISSAUGA, ON", PET},
    {"Personal & Household Expenses PETSMART INC 2021 KANATA, ON", PET},
    
    {"POS MERCHANDISE LA NOODLE", RESTAURANT},
    {"POS MERCHANDISE ORIENTAL RICE N", RESTAURANT},
    {"POS MERCHANDISE SUBWAY # 6521", RESTAURANT},
    {"Restaurants AI2-NU CARIBBEAN KANATA, ON", RESTAURANT},
    {"Restaurants BEAVERTAILS KANATA, ON", RESTAURANT},
    {"Restaurants BOSTON PIZZA # 422 BARRHAVEN, ON", RESTAURANT},
    {"Restaurants CAFE CREPE TORONTO, ON", RESTAURANT},
    {"Restaurants CHATIME NORTH YORK, ON", RESTAURANT},
    {"Restaurants CHONGQING LIUYISHOU HO NEPEAN, ON", RESTAURANT},
    {"Restaurants DARCY MCGEES #5837 OTTAWA, ON", RESTAURANT},
    {"Restaurants DARCY MCGEES IRISH PUB KANATA, ON", RESTAURANT},
    {"Restaurants DUMPLING BOWL OTTAWA, ON", RESTAURANT},
    {"Restaurants EAST SIDE MARIOS KANATA, ON", RESTAURANT},
    {"Restaurants FORTUNE EXPRESS RESTAU KANATA, ON", RESTAURANT},
    {"Restaurants FULL HOUSE ASIAN CUISI OTTAWA, ON", RESTAURANT},
    {"Restaurants GOLDEN BOWL RESTAURANT GLOUCESTER, ON", RESTAURANT},
    {"Restaurants HOCKEY SUSHI KANATA, ON", RESTAURANT},
    {"Restaurants HONEY TOWN OTTAWA, ON", RESTAURANT},
    {"Restaurants IKEA OTTAWA OTTAWA, ON", RESTAURANT},
    {"Restaurants KAGUYA KITCHEN OTTAWA, ON", RESTAURANT},
    {"Restaurants KANATA NOODLE HOUSE KANATA, ON", RESTAURANT},
    {"Restaurants KFC/TACO BELL #1416 KANATA, ON", RESTAURANT},
    {"Restaurants LA NOODLE OTTAWA, ON", RESTAURANT},
    {"Restaurants MCDONALD'S #10702 Q04 KANATA, ON", RESTAURANT},
    {"Restaurants MCDONALD'S #3211 BROCKVILLE, ON", RESTAURANT},
    {"Restaurants MONGOLIAN HOT POT #4 NEPEAN, ON", RESTAURANT},
    {"Restaurants PANDA GARDEN KANATA, ON", RESTAURANT},
    {"Restaurants ROTISSERIE ST HUBERT 045 OTTAWA, ON", RESTAURANT},
    {"Restaurants SANSOTEI RAMEN TORONTO, ON", RESTAURANT},
    {"Restaurants SHANGHAI 360 NEPEAN, ON", RESTAURANT},
    {"Restaurants SU & SHI @ YORKDALE TORONTO, ON", RESTAURANT},
    {"Restaurants SUBWAY 13794 KANATA, ON", RESTAURANT},
    {"Restaurants SUBWAY #63885 OTTAWA, ON", RESTAURANT},
    {"Restaurants SUBWAY #6521 OTTAWA, ON", RESTAURANT},
    {"Restaurants SUBWAY # 25475 KANATA, ON", RESTAURANT},
    {"Restaurants SWISS CHALET 1764 OTTAWA, ON", RESTAURANT},
    {"Restaurants TABLE 85 CAFE & CATERI OTTAWA, ON", RESTAURANT},
    {"Restaurants THAI EXPRESS KANATA STITTSVILLE, ON", RESTAURANT},
    {"Restaurants THE MONGOLIAN VILLAGE NEPEAN, ON", RESTAURANT},
    {"Restaurants TIM HORTONS 1600 QTH KANATA, ON", RESTAURANT},
    {"Restaurants TSUJIRI TEA HOUSE TORONTO, ON", RESTAURANT},
    {"Restaurants XIANG ZI NEPEAN, ON", RESTAURANT},
    

    {"CHEQUE #2", UNKNOWN},
    {"Health & Education ALGONQUIN COLLEGE OF A NEPEAN, ON", UNKNOWN},
    {"Retail and Grocery 68050 MACS CONV. STORES KANATA, ON", UNKNOWN},
    {"Personal & Household Expenses GROUPON CANADA INC 877-788-7858, QC", UNKNOWN},
    {"POS MERCHANDISE HACH", UNKNOWN},
    {"Professional and Financial Services INTUIT CANADA 780-466-9996, AB", UNKNOWN},
    {"Professional and Financial Services OVERLIMIT FEE", UNKNOWN},
    {"Professional and Financial Services OVERLIMIT FEE REVERSAL", UNKNOWN},
    {"Transportation LANSDOWNE STADIUM LTD NORTH YORK, ON", UNKNOWN},
    
    
};

std::vector<std::string> SpendingCategorizer::ignoredNames =
{
    // pc income
    "BANK TO BANK TSF EXT TSF FR 5577594",
    
    // cibc visa income
    "PAYMENT THANK YOU/PAIEMEN T MERCI",
    
    // insurance pay for
    "Health & Education CENTRUM DENTAL CENTRE KANATA, ON",
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
        case BEAUTY:
            return "BEAUTY";
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
        case PET:
            return "PET";
        case RESTAURANT:
            return "Restaurant";
        case UNKNOWN:
            return "UNKNOWN";
        default:
            return "unknown_NonFixedSpendingKind";
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
    
    //ss << "<Unknown Spendings>" << endl;
    for(const auto &it : unknownSpendings) {
        ss << it.toStr() << endl;
    }
    return ss.str();
}
