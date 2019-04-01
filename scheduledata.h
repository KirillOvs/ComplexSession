#ifndef SCHEDULEDATA_H
#define SCHEDULEDATA_H
#include "utils.h"

struct ScheduleData
{
    ScheduleData(const int start, const int end, Utils::Week _dayNum);

    std::string toString() const;

    Range range;
    Utils::Week dayNum;
};

#endif // SCHEDULEDATA_H
