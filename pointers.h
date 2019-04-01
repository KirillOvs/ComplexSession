#ifndef POINTERS_H
#define POINTERS_H
#include <memory>

#include "range.h"

struct ScheduleData;
using ScheduleDataPtr = std::shared_ptr<ScheduleData>;

class ScheduleItem;
using ScheduleItemPtr = std::unique_ptr<const ScheduleItem>;

class Worker;
using WorkerPtr = std::unique_ptr<Worker>;

#endif // POINTERS_H
