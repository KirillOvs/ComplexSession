#ifndef ENUMERROR_H
#define ENUMERROR_H

#include "stdint.h"

enum class ErrorCode : uint16_t
{
    UnkownError,
    // - files -
    FileNotOpen,
    // - invalid format -
    InvalidActionType,
    InvalidSheduleFormat,
    InvalidNumberOfFollowingLines,
    // - conversion is not possible -
    IncorrectRange
};

#endif // ENUMERROR_H
