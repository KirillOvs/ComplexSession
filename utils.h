#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include "pointers.h"
#include "enumerror.h"

class Utils
{
public:
    static const std::vector <std::string> weekDaysStringArray;
    static const std::vector <std::string> ErrStringsArray;
    enum Week : int8_t
    {
        MON,
        TUE,
        WED,
        THU,
        FRI,
        SAT,
        SUN
    };
    enum Minute : int16_t
    {
        ZERO    = 0,
        IN_DAY  = 1440,
        IN_WEEK = 10080
    };

    static Range convertRangeToAbsoluteValues(int startOffset, int endOffset, Week weekDay);
    static Week convertStrDayToNumber(const std::string& strDay);
    static std::string convertNumDayToString(const Week numDay);
    static std::string convertErrNumToString(const ErrorCode errCode);
};

#endif // UTILS_H
