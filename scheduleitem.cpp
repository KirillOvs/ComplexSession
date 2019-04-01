#include "scheduleitem.h"

ScheduleItem::ScheduleItem(const int start, const int end, const std::string& weekDayString)
    : m_data(start, end, Utils::convertStrDayToNumber(weekDayString))
    , m_absoluteDataView(nullptr)
{

}

Range* ScheduleItem::getAbsoluteView() const
{
    if(!m_absoluteDataView)
        m_absoluteDataView.reset(new Range(Utils::convertRangeToAbsoluteValues(m_data.range.first,
                                                                               m_data.range.second,
                                                                               m_data.dayNum)));
    return m_absoluteDataView.get();
}

ScheduleDataPtr ScheduleItem::convertAbsoluteViewToSpecified(const Range& absRnge) const
{
    int fullMin = m_data.dayNum * Utils::Minute::IN_DAY;
    int dif = absRnge.second - absRnge.first;
    int offset =absRnge.first - fullMin;
    if(offset < m_data.range.first)
        offset += Utils::Minute::IN_WEEK;

    return ScheduleDataPtr(new ScheduleData(offset, offset+dif, m_data.dayNum));
}

void ScheduleItem::storeIntersectionRange(const Range& range) const
{
    m_intersectionRanges.emplace_back(range);
}

std::vector<Range>& ScheduleItem::getIntersectionRangesArray() const
{
    return m_intersectionRanges;
}

bool ScheduleItem::operator < (const ScheduleItem& item) const
{
    return this->getAbsoluteView()->first < item.getAbsoluteView()->first;
}

//ScheduleDataPtr ScheduleItem::getScheduleData() const
//{
//    return ScheduleDataPtr(new ScheduleData(m_data));
//}
