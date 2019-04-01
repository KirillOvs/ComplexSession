#include "workerfactory.h"
#include "intersectworker.h"
#include "uniteworker.h"
#include "runtimeexception.h"

Worker* WorkerFactory::getWorker(int action)
{
    switch(action)
    {
    case WorkerAction::Type::INTERSECT:
        return new IntersectWorker();
    case WorkerAction::Type::UNITE:
        return new UniteWorker();
    default:
        throw RunTimeException(ErrorCode::InvalidActionType);
    }
}
