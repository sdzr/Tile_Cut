#ifndef __US_DATA_PROCESS_HPP__
#define __US_DATA_PROCESS_HPP__


// 为保证正确的DLL导入导出，请不要修改如下定义
#if defined(_WIN32) 
#if defined(_US_DATA_PROCESS_LIB)
#if defined(_WINDLL) &&  defined(_US_DATA_PROCESS_DLL)
#undef _US_DATA_PROCESS_DLL
#define _US_DATA_PROCESS_DLL __declspec(dllexport)
#else
#define _US_DATA_PROCESS_DLL __declspec(dllimport)
#endif
#endif

#ifndef _US_DATA_PROCESS_DLL
#define _US_DATA_PROCESS_DLL
#endif

#else
#define _US_DATA_PROCESS_DLL
#endif



#if !defined(__US_IMAGE_HPP__) && \
	!defined(__US_DATA_PROCESS_OPERATOR_HPP__) && \
	!defined(__US_IMAGE_POLYGON_CLIP_HPP__) && \
	!defined(__US_POLY_CLIP_PARAM_HPP__) && \
	!defined(__US_IMAGE_READ_DATA_HPP__)

#include "us_image.hpp"
#include "us_data_process_operator.hpp"
#include "us_poly_clip_param.hpp"
#include "us_image_polygon_clip.hpp"
#include "us_image_read_data.hpp"

#endif






#endif	//! __US_DATA_PROCESS_HPP__


