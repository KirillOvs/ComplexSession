#include "uniteworker.h"
#include "scheduleitem.h"

void UniteWorker::processOneSet(const Set& set)
{
    for(auto& it : set)
    {
        auto absView = it->getAbsoluteView();
        auto& intersectionRanges = it->getIntersectionRangesArray();

        // set of point
        std::set<int> allPoints;
        allPoints.insert(absView->first);
        for(auto& elem : intersectionRanges)
        {
            allPoints.insert(elem.first);
            allPoints.insert(elem.second);
        }
        allPoints.insert(absView->second);

        // insert of result periods
        for(auto elem = allPoints.begin(); elem != allPoints.end(); )
        {
            auto start = *elem;
            if(++elem != allPoints.end())
            {
                auto end = *(elem);
                m_resMap.emplace(*elem, it->convertAbsoluteViewToSpecified( {start, end} ));
            }
        }
    }
}

bool UniteWorker::isValid() const
{
    return !m_set1.empty() || !m_set2.empty();
}
