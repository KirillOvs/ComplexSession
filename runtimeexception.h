#ifndef RUNTIMEEXCEPTION_H
#define RUNTIMEEXCEPTION_H

#include <exception>
#include "enumerror.h"
#include <string>

class RunTimeException : public std::exception
{
public:
    RunTimeException(const ErrorCode errNum, const std::string& errString = "");
    virtual const char* what() const noexcept override;
protected:
    ErrorCode m_errNum;
    std::string m_errString;
};

#endif // RUNTIMEEXCEPTION_H
