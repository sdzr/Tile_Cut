#ifndef __US_METADATA_HPP__
#define __US_METADATA_HPP__

#if defined(_WIN32) 

#if defined(_US_METADATA_LIB)
#if defined(_WINDLL) &&  defined(_US_METADATA_DLL)
#undef _US_METADATA_DLL
#define _US_METADATA_DLL __declspec(dllexport)
#else
#define _US_METADATA_DLL __declspec(dllimport)
#endif
#endif

#ifndef _US_METADATA_DLL
#define _US_METADATA_DLL
#endif

#else
#define _US_METADATA_DLL
#endif

#if !defined(__US_IMAGE_BASIC_META_HPP__) &&\
	!defined(__US_DATASET_BASIC_META_HPP__) &&\
	!defined(__US_BASIC_UV_HPP__) &&\
	!defined(__US_GRID_UV_HPP__) &&\
	!defined(__US_WMTS_BASIC_META_HPP__) &&\
	!defined(__US_WMTS_THEME_BASIC_META_HPP__) &&\
	!defined(__US_META_JSON_CONVERT_HPP__)

#include "us_image_basic_meta.hpp"
#include "us_grid_uv.hpp"
#include "us_basic_uv.hpp"
#include "us_dataset_basic_meta.hpp"
#include "us_wmts_basic_meta.hpp"
#include "us_wmts_theme_basic_meta.hpp"
#include "us_meta_json_convert.hpp"

#endif


#endif //!__US_METADATA_HPP__