#pragma once
#include "clsDate.h"

class clsPeriod
{
private:
	clsDate _Start;
	clsDate _End;

public:
	clsPeriod(clsDate Start, clsDate End)
	{
		_Start = Start;
		_End = End;
	}

	void setStart(clsDate Start)
	{
		_Start = Start;
	}

	clsDate getStart()
	{
		return _Start;
	}

	__declspec(property(get = getStart, put = setStart)) clsDate Start;

	clsDate getEnd()
	{
		return _End;
	}

	void setEnd(clsDate End)
	{
		_End = End;
	}

	__declspec(property(get = getEnd, put = setEnd)) clsDate End;

	bool AreDatesOverLapping(clsPeriod Period1, clsPeriod Period2)
	{
		if (clsDate::CompareTwoDates(Period2.End, Period1.Start) == clsDate::BeforeAfterEqualDate::Before || clsDate::CompareTwoDates(Period2.Start, Period1.End) == clsDate::BeforeAfterEqualDate::After)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};
