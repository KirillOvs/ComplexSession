#ifndef UNITEWORKER_H
#define UNITEWORKER_H
#include "worker.h"

class UniteWorker : public Worker
{
    virtual void processOneSet(const Set& set) override;
public:
    virtual bool isValid() const override;
};

#endif // UNITEWORKER_H
