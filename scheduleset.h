#ifndef SCHEDULESET_H
#define SCHEDULESET_H
#include <set>
#include "pointers.h"

struct Comparator
{
    bool operator ()(const ScheduleItemPtr& a, const ScheduleItemPtr& b);
};
using Set = std::set<ScheduleItemPtr, Comparator>;

#endif // SCHEDULESET_H
