#include "workerfactory.h"
#include "intersectworker.h"
#include "uniteworker.h"
#include "runtimeexception.h"

WorkerPtr WorkerFactory::getWorker(int action)
{
    switch(action)
    {
    case WorkerAction::Type::INTERSECT:
        return WorkerPtr(new IntersectWorker());
    case WorkerAction::Type::UNITE:
        return WorkerPtr(new UniteWorker());
    default:
        throw RunTimeException(ErrorCode::InvalidActionType);
    }
}
