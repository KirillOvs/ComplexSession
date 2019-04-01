#ifndef SCHEDULESPARSER_H
#define SCHEDULESPARSER_H
#include "scheduleset.h"
#include "workeraction.h"

class SchedulesParser
{
    enum {
        START_PERIOD,
        END_PERIOD
    };
    enum {
        DATA_FOR_FIRST_INSTRUMENT,
        DATA_FOR_SECOND_INSTRUMENT
    };

    static WorkerAction::Type parseActionType(std::string& line);
    static unsigned parseNumber(const std::string& line);
    static void parseSchedules(std::ifstream& inStream, const unsigned number, Set* const items);
public:
    static Worker* parse(const std::string& pathToInputFile);
};

#endif // SCHEDULESPARSER_H
