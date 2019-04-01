#include "runtimeexception.h"
#include <sstream>
#include "utils.h"

RunTimeException::RunTimeException(const ErrorCode errNum, const std::string& errString)
    : std::exception()
    , m_errNum(errNum)
    , m_errString(errString)
{
    std::stringstream ss;
    ss << "Run time error occured, code: " << static_cast<uint16_t>(m_errNum) << Utils::convertErrNumToString(m_errNum) << m_errString;
    m_errString = ss.str();
}

const char* RunTimeException::what() const noexcept
{
    return m_errString.c_str();
}
