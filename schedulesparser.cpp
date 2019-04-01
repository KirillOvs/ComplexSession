#include "schedulesparser.h"
#include <algorithm>
#include <regex>
#include <fstream>
#include "worker.h"
#include "scheduleitem.h"
#include "workerfactory.h"
#include "runtimeexception.h"

WorkerAction::Type SchedulesParser::parseActionType(std::string& line)
{
    line.erase(remove_if(line.begin(), line.end(), isspace), line.end()); // remove all spases
    if("intersect" == line)
        return WorkerAction::Type::INTERSECT;
    else if("unite" == line)
        return WorkerAction::Type::UNITE;
    else
        throw RunTimeException(ErrorCode::InvalidActionType);
}

unsigned SchedulesParser::parseNumber(const std::string& line)
{
    if(!std::regex_match(line, std::regex("^\\d+$")))
        throw RunTimeException(ErrorCode::InvalidNumberOfFollowingLines);
    int numberFollowingLines = std::stoi(line);
    if(numberFollowingLines <= 0)
        throw RunTimeException(ErrorCode::InvalidNumberOfFollowingLines);

    return static_cast<unsigned>(numberFollowingLines);
}

void SchedulesParser::parseSchedules(std::ifstream& inStream, const unsigned number, Set* const items)
{
    std::string line;
    for (unsigned i = number; i > 0; --i)
    {
        if(std::getline(inStream, line))
        {
            line.erase(remove_if(line.begin(), line.end(), isspace), line.end()); // remove all spases
            if(!std::regex_match(line, std::regex("^-*\\d+,-*\\d+,(Monday,?|Tuesday,?|Wednesday,?|Thursday,?|Friday,?|Saturday,?|Sunday,?)+$")))
                throw RunTimeException(ErrorCode::InvalidSheduleFormat);

            int start = 0;
            int end   = 0;
            std::stringstream sStrem(line);
            std::string token;
            for(int i = START_PERIOD; std::getline(sStrem, token, ','); ++i)
            {
                if(START_PERIOD == i)
                    start = std::stoi(token);
                else if(END_PERIOD == i)
                    end = std::stoi(token);
                else if(END_PERIOD < i)
                    items->emplace(new ScheduleItem(start, end, token)); // here everything is checked and it can be pushed
            }
        }
    }
}

WorkerPtr SchedulesParser::parse(const std::string& pathToInputFile)
{
    std::ifstream in(pathToInputFile);
    if(!in)
        throw RunTimeException(ErrorCode::FileNotOpen);

    WorkerAction::Type actionType = WorkerAction::Type::UNDEFINED;
    Set schedule1;
    Set schedule2;

    try {
        std::string line;
        if(std::getline(in, line)) // 1st - actionType line
            actionType = parseActionType(line);

        for(int i = DATA_FOR_FIRST_INSTRUMENT; std::getline(in, line); ++i)
        {
            line.erase(remove_if(line.begin(), line.end(), isspace), line.end()); // remove all spases
            if(line.empty()) continue;
            // 2nd - number of lines
            unsigned numberFollowingLines = parseNumber(line);

            // 3rd - shedules
            if(i == DATA_FOR_FIRST_INSTRUMENT)
                parseSchedules(in, numberFollowingLines, &schedule1);
            else if(i == DATA_FOR_SECOND_INSTRUMENT)
                parseSchedules(in, numberFollowingLines, &schedule2);
            else
                break;
        }
    }
    catch(const std::exception& ex)
    {
        in.close();
        throw;
    }

    in.close();
    auto workObject = WorkerFactory::getWorker(actionType);
    workObject->init(std::move(schedule1), std::move(schedule2));

    if(workObject->isValid())
        return workObject;

    return nullptr;
}
