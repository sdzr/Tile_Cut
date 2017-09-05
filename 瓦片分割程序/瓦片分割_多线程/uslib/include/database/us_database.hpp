#ifndef __US_DATABASE_HPP__
#define __US_DATABASE_HPP__

// windows下DLL导出
#if defined(_WIN32)
#if defined(_US_DATABASE_LIB)
#if defined(_WINDLL) && defined(_US_DATABASE_DLL)
#undef _US_DATABASE_DLL
#define _US_DATABASE_DLL __declspec(dllexport)
#else
#define _US_DATABASE_DLL __declspec(dllimport)
#endif	// _WINDLL + _US_DATABASE_DLL
#endif  // _US_DATABASE_LIB
#ifndef _US_DATABASE_DLL
#define _US_DATABASE_DLL
#endif

#else
#define _US_UTIL_DLL
#endif	// _WIN32

#if !defined(__US_DB_CONNECTION_HPP__) && \
	!defined(__US_DB_REPLY_HPP__) && \
	!defined(__US_DB_DRIVER_HPP__) && \
	!defined(__US_DB_SQLITE3_CONNECTION_HPP__) && \
	!defined(__US_DB_SQLITE3_REPLY_HPP__) && \
	!defined(__US_DB_SQLITE3_DRIVER_HPP__)

#include "us_db_connection.hpp"
#include "us_db_reply.hpp"
#include "us_db_driver.hpp"
#include "sqlite3/us_db_sqlite3_connection.hpp"
#include "sqlite3/us_db_sqlite3_reply.hpp"
#include "sqlite3/us_db_sqlite3_driver.hpp"


#endif


#endif //! __US_DATABASE_HPP__