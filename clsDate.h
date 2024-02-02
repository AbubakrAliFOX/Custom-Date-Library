#pragma once
class clsDate
{
private:
    struct Date
    {
        short Day, Month, Year;
    };

    Date _Date;

public:
    // constructors
    clsDate()
    {
        _Date = GetSysDate();
    }

    clsDate(string DateString)
    {
        _Date = StringToDate(DateString);
    }

    clsDate(short Day, short Month, short Year)
    {
        Date NewDate;
        NewDate.Day = Day;
        NewDate.Month = Month;
        NewDate.Year = Year;
        _Date = NewDate;
    }

    clsDate(short DayFromYearBeginning, short Year)
    {
        _Date = DateFromYearBegnning(Year, DayFromYearBeginning);
    }

    static Date GetSysDate()
    {
        Date SysDate;
        time_t t = time(0);
        tm now;
        localtime_s(&now, &t);
        SysDate.Year = now.tm_year + 1900;
        SysDate.Month = now.tm_mon + 1;
        SysDate.Day = now.tm_mday;
        return SysDate;
    }

    Date StringToDate(string strDate)
    {
        Date NewData;
        vector<string> vDate = clsString::split(strDate, "/");

        NewData.Day = stoi(vDate[0]);
        NewData.Month = stoi(vDate[1]);
        NewData.Year = stoi(vDate[2]);

        return NewData;
    }

    string DateToString(Date NewDate)
    {
        return to_string(NewDate.Day) + "/" + to_string(NewDate.Month) + "/" + to_string(NewDate.Year);
    }

    static bool IsLeapYear(short Number)
    {
        return (Number % 4 == 0 && Number % 100 != 0) || (Number % 400 == 0);
    }

    static short DaysInMonth(short Year, short Month)
    {
        int DaysOfMonths[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return (Month < 1 || Month > 12) ? 0 : (Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : (DaysOfMonths[Month - 1]));

        // In One Line:
        // return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : (Month == 4 || Month == 6 || Month == 9 || Month == 11) ? 30 : 31;
    }

    static short DaysInMonth(Date NewDate)
    {
        short Month = NewDate.Month;
        short Day = NewDate.Day;
        short Year = NewDate.Year;

        int DaysOfMonths[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return (Month < 1 || Month > 12) ? 0 : (Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : (DaysOfMonths[Month - 1]));

        // In One Line:
        // return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : (Month == 4 || Month == 6 || Month == 9 || Month == 11) ? 30 : 31;
    }

    Date DateFromYearBegnning(short Year, short Day)
    {
        Date NewDate;
        short Month = 1;
        while (true)
        {
            if (Day <= DaysInMonth(Year, Month))
            {
                break;
            }
            Day -= DaysInMonth(Year, Month);
            Month++;
        }

        NewDate.Day = Day;
        NewDate.Year = Year;
        NewDate.Month = Month;
        return NewDate;
    }

    static short OrderOfDate(short Year, short Month, short Day)
    {
        short a, y, m;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2; // Gregorian://0:sun, 1:Mon, 2:Tue...etc
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    static short OrderOfDate(Date NewDate)
    {
        return OrderOfDate(NewDate.Year, NewDate.Month, NewDate.Day);
    }

    static string DayShortName(short DayOfWeekOrder)
    {
        string arrDayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        return arrDayNames[DayOfWeekOrder];
    }

    static void Print(Date NewDate)
    {
        string DateString = to_string(NewDate.Day) + "/" + to_string(NewDate.Month) + "/" + to_string(NewDate.Year);

        cout << "\n\n"
            << DayShortName(OrderOfDate(NewDate)) << ", " << DateString << endl;
    }

    void Print()
    {
        Print(_Date);
    }

    static string MonthShortName(short Month)
    {
        string arrDayNames[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
        return arrDayNames[Month - 1];
    }

    static void PrintMonthCalender(short Year, short Month)
    {

        cout << "____________________________________________" << MonthShortName(Month) << "_____________________________________________\n"
            << endl;
        cout << setw(12) << left << "Sun";
        cout << setw(12) << left << "Mon";
        cout << setw(12) << left << "Tue";
        cout << setw(12) << left << "Wed";
        cout << setw(12) << left << "Thu";
        cout << setw(12) << left << "Fri";
        cout << setw(12) << left << "Sat";
        cout << "\n";

        short DaysOfMonth = DaysInMonth(Year, Month);
        short FirstDayOfMonth = OrderOfDate(Year, Month, 1);
        short NumberOfGaps = FirstDayOfMonth;

        short Day = 1;
        short Counter = 0;

        while (Day <= DaysOfMonth)
        {
            string WhatToPrint = NumberOfGaps > 0 ? " " : to_string(Day);
            cout << setw(12) << left << WhatToPrint;
            NumberOfGaps--;
            Counter++;

            if (Counter % 7 == 0)
            {
                cout << endl;
            }

            if (NumberOfGaps < 0)
            {
                Day++;
            }
        }

        cout << "\n____________________________________________________________________________________________" << endl;
    }

    void PrintMonthCalender()
    {
        PrintMonthCalender(_Date.Year, _Date.Month);
    }

    static void PrintYearCalender(short Year)
    {
        for (short Month = 1; Month <= 12; Month++)
        {
            PrintMonthCalender(Year, Month);
        }
    }

    void PrintYearCalender()
    {
        PrintYearCalender(_Date.Year);
    }

    static bool IsValid(Date NewDate)
    {
        return (NewDate.Month <= 12 && NewDate.Month >= 1) && ((NewDate.Day <= DaysInMonth(NewDate) && NewDate.Day >= 1));
    }

    bool IsValid()
    {
        return IsValid(_Date);
    }

    static bool IsDayLast(Date NewDate)
    {
        return NewDate.Day == DaysInMonth(NewDate.Year, NewDate.Month);
    }

    static bool IsMonthLast(Date NewDate)
    {
        return NewDate.Month == 12;
    }

    static void AddOneDayToDate(Date& NewDate)
    {
        if (IsDayLast(NewDate))
        {
            if (IsMonthLast(NewDate))
            {
                NewDate.Month = 1;
                NewDate.Year++;
            }
            else
            {
                NewDate.Month++;
            }
            NewDate.Day = 1;
        }
        else
        {
            NewDate.Day++;
        }
    }

    static int AgeInDays(clsDate Birthday, bool IncludeEndDay = false)
    {
        Date CurrentDate = GetSysDate();

        if (IsDateBeforeDate2(Birthday._Date, CurrentDate))
        {
            int Counter = 0;
            while (IsDateBeforeDate2(Birthday._Date, CurrentDate))
            {
                AddOneDayToDate(Birthday._Date);
                Counter++;
            }

            return IncludeEndDay ? ++Counter : Counter;
        }
        else
        {
            return -1;
        }
    }

    static bool IsDateBeforeDate2(Date Date1, Date Date2)
    {
        return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
    }

    static bool IsDateEqualtoDate2(Date Date1, Date Date2)
    {
        return Date1.Year == Date2.Year ? (Date1.Month == Date2.Month ? Date1.Day == Date2.Day : false) : (false);
    }

    static bool IsDateAfterDate2(Date Date1, Date Date2)
    {
        return !IsDateBeforeDate2(Date1, Date2) && !IsDateEqualtoDate2(Date1, Date2);
    }

    bool IsDateBeforeDate2(clsDate Date2)
    {
        return IsDateBeforeDate2(_Date, Date2._Date);
    }

    bool IsDateEqualtoDate2(clsDate Date2)
    {

        return IsDateEqualtoDate2(_Date, Date2._Date);
    }

    bool IsDateAfterDate2(clsDate Date2)
    {

        return IsDateAfterDate2(_Date, Date2._Date);
    }

};

