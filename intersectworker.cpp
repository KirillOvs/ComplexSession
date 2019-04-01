#include "intersectworker.h"
#include "scheduleitem.h"

void IntersectWorker::processOneSet(const Set& set)
{
    for(auto& it : set)
    {
        for(auto& elem : it->getIntersectionRangesArray())
        {
            int key = elem->first;
            m_resMap.emplace(key, it->convertAbsoluteViewToSpecified(*elem));
        }
    }
}

bool IntersectWorker::isValid() const
{
    return !m_set1.empty() && !m_set2.empty();
}
