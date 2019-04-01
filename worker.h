#ifndef WORKER_H
#define WORKER_H
#include "scheduleset.h"
#include <map>

class Worker
{
protected:
    virtual void processOneSet(const Set& set) = 0;
    void process();

    void findIntersections() const;
public:
    Worker(const Worker&) = delete;
    Worker(Worker&&) = delete;
    Worker& operator=(const Worker&) = delete;
    Worker& operator=(Worker&&) = delete;


    Worker();
    virtual ~Worker();

    void init(Set&& schedules1, Set&& schedules2);

    virtual bool isValid() const = 0;

    void resultToFile(const std::string& pathToFile);

    bool execute();

protected:
    Set m_set1;
    Set m_set2;
    std::map<int, ScheduleDataPtr> m_resMap;
};

#endif // WORKER_H
