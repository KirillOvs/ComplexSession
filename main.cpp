#include <iostream>
#include "schedulesparser.h"
#include "worker.h"

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Application takes two parameters: paths to input and output files" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inputFileName (argv[1]);
    std::string outputFileName(argv[2]);

    try
    {
        WorkerPtr worker(SchedulesParser::parse(inputFileName));
        if(worker)
        {
            if(worker->execute())
                worker->resultToFile(outputFileName);
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
