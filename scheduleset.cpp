#include "scheduleset.h"
#include "scheduleitem.h"

bool Comparator::operator () (const ScheduleItemPtr& a, const ScheduleItemPtr& b)
{
    return *a < *b;
}
