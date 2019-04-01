#include "utils.h"
#include <algorithm>
#include "runtimeexception.h"

std::string Utils::convertNumDayToString(const Week numDay)
{
    return weekDaysStringArray[static_cast<size_t>(numDay)];
}

std::string Utils::convertErrNumToString(const ErrorCode errCode)
{
    return ErrStringsArray[static_cast<size_t>(errCode)];
}

Utils::Week Utils::convertStrDayToNumber(const std::string& strDay)
{
    auto it = std::find(weekDaysStringArray.cbegin(), weekDaysStringArray.cend(), strDay);
    if(it == weekDaysStringArray.end())
        throw RunTimeException(ErrorCode::IncorrectRange);

    return static_cast<Week>(std::distance(weekDaysStringArray.cbegin(), it));
}

Range Utils::convertRangeToAbsoluteValues(int startOffset, int endOffset, Utils::Week weekDay) // need to check
{
    if(startOffset > endOffset)
        throw RunTimeException(ErrorCode::IncorrectRange);

    int length = abs(endOffset - startOffset);

    if(length >= Minute::IN_WEEK) // this is super period, all other periods will be intersect with
        return { Minute::ZERO, Minute::IN_WEEK };

    if(abs(startOffset) > Minute::IN_WEEK)
        startOffset = startOffset % Minute::IN_WEEK;

    int start = Minute::IN_DAY * weekDay + startOffset;

    if(start + length > Minute::IN_WEEK)
        start -= Minute::IN_WEEK;

    return { start, start + length };
}

const std::vector<std::string> Utils::weekDaysStringArray = { "Monday"   ,
                                                              "Tuesday"  ,
                                                              "Wednesday",
                                                              "Thursday" ,
                                                              "Friday"   ,
                                                              "Saturday" ,
                                                              "Sunday"  };

const std::vector<std::string> Utils::ErrStringsArray = { " Unkown error ",
                                                          " File not open ",
                                                          " Invalid format: invalid action type ",
                                                          " Invalid format: invalid shedule format ",
                                                          " Invalid format: invalid number of following lines ",
                                                          " Conversion is not possible: incorrect period range" };
