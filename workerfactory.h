#ifndef WORKERFACTORY_H
#define WORKERFACTORY_H
#include "pointers.h"
#include "workeraction.h"

class WorkerFactory
{
public:
    static Worker* getWorker(int action);
};

#endif // WORKERFACTORY_H
