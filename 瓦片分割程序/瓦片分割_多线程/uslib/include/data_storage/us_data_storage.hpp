#ifndef __US_DATA_STORAGE_HPP__
#define __US_DATA_STORAGE_HPP__

// windows下DLL导出
#if defined(_WIN32)		// WIN32平台才导出或导入

#if defined(_US_DATA_STORAGE_LIB) // 本工程中才导出或导入(引用此项目的程序需定义此宏才导入)

#if defined(_WINDLL) && defined(_US_DATA_STORAGE_DLL)	// 是_WINDLL项目且定义了_US_UTIL_DLL才导出
#undef _US_DATA_STORAGE_DLL
#define _US_DATA_STORAGE_DLL __declspec(dllexport)
#else
#define _US_DATA_STORAGE_DLL __declspec(dllimport)
#endif	// _WINDLL + _US_DATA_STORAGE_DLL

#endif  // _US_DATA_STORAGE_LIB


#ifndef _US_DATA_STORAGE_DLL
#define _US_DATA_STORAGE_DLL	// 如果没有定义，那就定义
#endif

#else
#define _US_DATA_STORAGE_DLL
#endif	// _WIN32

#if !defined(__US_PATH_HPP__) && \
	!defined(__US_URL_HPP__) && \
	!defined(__US_DATA_STORAGE_MANAGER_HPP__)

#include "us_path.hpp"
#include "us_url.hpp"
#include "us_data_storage_manager.hpp"

#endif


#endif // !__US_DATA_STORAGE_HPP__

