#ifndef __US_GRID_SYSTEM_HPP__
#define __US_GRID_SYSTEM_HPP__

// windows下DLL导出
#if defined(_WIN32)  
#if defined(_US_GRID_SYSTEM_LIB)
#if defined(_WINDLL) && defined(_US_GRID_SYSTEM_DLL)
#undef _US_GRID_SYSTEM_DLL
#define _US_GRID_SYSTEM_DLL __declspec(dllexport)
#else
#define _US_GRID_SYSTEM_DLL __declspec(dllimport)
#endif	// _WINDLL ...
#endif

#ifndef _US_GRID_SYSTEM_DLL
#define _US_GRID_SYSTEM_DLL
#endif

#else
#define _US_GRID_SYSTEM_DLL
#endif	// _WIN32

// 
#if !defined(__US_GRID_TYPE_HPP__) && \
	!defined(__US_GRID_ID_HPP__) && \
	!defined(__US_GRID_BASE_HPP__) && \
	!defined(__US_GRID_METER_HPP__) && \
	!defined(__US_GRID_DEGREE_HPP__)

#include "us_grid_type.hpp"
#include "us_grid_id.hpp"
#include "us_grid_base.hpp"
#include "us_grid_meter.hpp"
#include "us_grid_degree.hpp"

#endif



#endif //!__US_GRID_SYSTEM_HPP__