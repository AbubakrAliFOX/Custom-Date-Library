#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include "clsString.h"
#include "clsDate.h"
#include "clsPeriod.h";

using namespace std;


int main()
{
    
    clsDate From1("1/1/2021");
    clsDate To1("31/12/2021");
    clsPeriod Period1 (From1, To1);

    clsDate From2("30/12/2021");
    clsDate To2("31/12/2022");
    clsPeriod Period2 (From2, To2);

    
    cout << Period1.OverlapDays(Period2) << endl; 

    // clsDate NewDate1;
    // NewDate1.Print();

    // clsDate NewDate2("3/12/2021");
    // NewDate2.Print();

    // clsDate NewDate3(29, 12, 1999);
    // NewDate3.Print();

    // clsDate NewDate4(365, 2018);
    // NewDate4.Print();

    // NewDate2.PrintYearCalender();

    // cout << clsDate::AgeInDays(clsDate(29, 12, 1999)) << endl;
    // cout << NewDate3.IsDateEqualtoDate2(clsDate(29,12,1999)) << endl;
}
