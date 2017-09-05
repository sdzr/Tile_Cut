#ifndef __US_GEO_COORD_TRANSFORM_HPP__
#define __US_GEO_COORD_TRANSFORM_HPP__



// windows下DLL导出
#if defined(_WIN32)		// WIN32平台才导出或导入

#if defined(_US_GEO_COORD_TRANSFORM_LIB) // 本工程中才导出(引用此项目的程序需定义此宏才导入)

#if defined(_WINDLL) && defined(_US_GEO_COORD_TRANSFORM_DLL)	// 是_WINDLL项目且定义了_US_UTIL_DLL才导出
#undef _US_GEO_COORD_TRANSFORM_DLL
#define _US_GEO_COORD_TRANSFORM_DLL __declspec(dllexport)
#else
#define _US_GEO_COORD_TRANSFORM_DLL __declspec(dllimport)
#endif	// _WINDLL + _US_DATA_MANAGER_LIB

#endif  // _US_DATA_MANAGER_LIB

#ifndef _US_GEO_COORD_TRANSFORM_DLL
#define _US_GEO_COORD_TRANSFORM_DLL	// 如果没有定义，那就定义
#endif

#else
#define _US_GEO_COORD_TRANSFORM_DLL
#endif	// _WIN32

#if !defined(__US_SPATIAL_REFERENCE_HPP__)

#include "us_spatial_reference.hpp"

#endif

#endif