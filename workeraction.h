#ifndef WORKERACTIONS_H
#define WORKERACTIONS_H
#include <stdint.h>

struct WorkerAction
{
    enum Type : int8_t
    {
        UNDEFINED,
        INTERSECT,
        UNITE
    };
};

#endif // WORKERACTIONS_H
