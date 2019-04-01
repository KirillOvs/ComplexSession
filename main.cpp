#include <iostream>
#include "schedulesparser.h"
#include "worker.h"

int main(int argc, char *argv[])
{
    try {
        WorkerPtr worker = SchedulesParser::parse("case1.txt");
        if(worker)
        {
            if(worker->execute())
                worker->resultToFile("");
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what();
    }

    return 0;
}
