#ifndef INTERSECTWORKER_H
#define INTERSECTWORKER_H
#include "worker.h"

class IntersectWorker : public Worker
{
    virtual void processOneSet(const Set& set) override;
public:
    virtual bool isValid() const override;
};

#endif // INTERSECTWORKER_H
