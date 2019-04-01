#include "worker.h"
#include <fstream>
#include <sstream>
#include <iostream> // TODO: to remove
#include "scheduleitem.h"
#include "runtimeexception.h"

Worker::Worker(){}
Worker::~Worker(){}

void Worker::init(Set&& schedules1, Set&& schedules2)
{
    m_set1.swap(schedules1);
    m_set2.swap(schedules2);
}

void Worker::process()
{
    // call virtual method
    processOneSet(m_set2);
    processOneSet(m_set1);
}

void Worker::findIntersections() const
{
    auto it1 = m_set1.begin(),
         it2 = m_set2.begin();
    while(it1 != m_set1.end() && it2 != m_set2.end())
    {
        auto a_absView = (*it1)->getAbsoluteView();
        auto b_absView = (*it2)->getAbsoluteView();

        if(a_absView->first < b_absView->second && // if periods intersect
           a_absView->second > b_absView->first)
        {
            Range* range = new Range(std::max(a_absView->first,  b_absView->first ),
                                     std::min(a_absView->second, b_absView->second));
            (*it1)->storeIntersectionRange(range);
            (*it2)->storeIntersectionRange(range);
        }

        if(a_absView->second <= b_absView->second)
            ++it1;
        else if(a_absView->second >= b_absView->second)
            ++it2;
    }
}

void Worker::resultToFile(const std::string& pathToFile)
{
    if(m_resMap.empty())
        return;
    //std::ofstream out(pathToFile);
    //if(!out)
    //    throw RunTimeException(ErrorCode::FileNotOpen);

    try
    {
        // grouping
        std::map<Range, std::string> groupingMap;
        for(auto& it : m_resMap)
        {
            ScheduleDataPtr itemData = it.second;
            auto findResIt = groupingMap.find(itemData->range);
            if(findResIt == groupingMap.end())
                groupingMap.emplace(itemData->range, Utils::convertNumDayToString(itemData->dayNum));
            else
                groupingMap[itemData->range] += "," + Utils::convertNumDayToString(itemData->dayNum);
        }

        //for(auto& it : groupingMap)
        //    out << it.first.first << ',' << it.first.second << ',' << it.second << std::endl;

        for(auto& it : groupingMap)
        {
            std::stringstream ss;
            ss << it.first.first << ',' << it.first.second << ',' << it.second;
            std::cout << ss.str() << std::endl;
        }
    }
    catch (std::exception& e)
    {
        //out.close();
        throw;
    }
    //out.close();
}

bool Worker::execute()
{
    if(!isValid())
        return false;

    this->findIntersections();
    this->process();

    return !m_resMap.empty();
}
