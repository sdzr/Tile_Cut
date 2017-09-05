#ifndef __US_TIME_HPP__
#define __US_TIME_HPP__

#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

#ifdef _WIN32
#include <WinSock2.h>
_US_UTIL_DLL int gettimeofday(struct timeval *tv, void *dummy);
#else
#include <sys/time.h>
#endif
namespace unispace
{
_US_UTIL_DLL int us_timeval_to_local_time_str(struct timeval *tv, char* bj);
}

#endif //!__US_TIME_HPP__
