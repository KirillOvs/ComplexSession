#include "scheduledata.h"
#include <sstream>
#include "runtimeexception.h"

ScheduleData::ScheduleData(const int start, const int end, Utils::Week _dayNum)
    : range(start, end)
    , dayNum(_dayNum)
{
    if(range.first > range.second)
        throw RunTimeException(ErrorCode::IncorrectRange);
}

std::string ScheduleData::toString() const
{
    std::stringstream ss;
    ss << range.first << ',' << range.second << ',' << Utils::convertNumDayToString(dayNum);
    return ss.str();
}
