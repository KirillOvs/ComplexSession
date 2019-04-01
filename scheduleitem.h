#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H
#include "utils.h"
#include "scheduledata.h"
#include "pointers.h"

class ScheduleItem
{
public:
    ScheduleItem() = delete;
    ScheduleItem(ScheduleItem&&) = delete;
    ScheduleItem(const ScheduleItem&) = delete;
    ScheduleItem& operator=(ScheduleItem&&) = delete;
    ScheduleItem& operator=(const ScheduleItem&) = delete;

    ScheduleItem(const int start, const int end, const std::string& weekDayString);

    // comparison for stl algorithms
    bool operator < (const ScheduleItem& item) const;
    RangePtr getAbsoluteView() const;
    ScheduleDataPtr convertAbsoluteViewToSpecified(const Range& absRnge) const;
    ScheduleDataPtr getScheduleData() const;
    std::vector<RangePtr>& getIntersectionRangesArray() const;
    void storeIntersectionRange(Range* range) const;
protected:
    ScheduleData m_data;
    mutable RangePtr m_absoluteDataView;
    mutable std::vector<RangePtr> m_intersectionRanges;
};

#endif // SCHEDULEITEM_H
