#ifndef __US_AFFINE_TRANSFORM_HPP__
#define __US_AFFINE_TRANSFORM_HPP__

#ifndef __US_VEC2_HPP__
#include "us_vec2.hpp"
#endif // !__US_VEC2_HPP__


#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

namespace unispace
{

	/**********************************************************************//**
	 * @brief	地理(投影)坐标转影像行列坐标.
	 *
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/23
	 *
	 * @param [in]	adfGeoTransform 坐标转换参数(仿射变换).
	 * @param		projx			地理坐标X.
	 * @param		projy			地理坐标Y.
	 * @param [out] out_col		   If non-null, the out col.
	 * @param [out] out_row		   If non-null, the out row.
	 *
	 * @return true if it succeeds, false if it fails.
	 *************************************************************************/
	_US_UTIL_DLL bool projection_to_image_rowcol(const double *adfGeoTransform,
		double projx, double projy,
		int* out_col, int* out_row);

	/**********************************************************************//**
	 * @brief	影像行列坐标转地理(投影)坐标.
	 *
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/23
	 *
	 * @param [in]	adfGeoTransform	坐标转换参数(仿射变换).
	 * @param		col				影像上列坐标.
	 * @param		row				影像上行坐标.
	 * @param [out] out_projx	   If non-null, the out projx.
	 * @param [out] out_projy	   If non-null, the out projy.
	 *************************************************************************/
	_US_UTIL_DLL void image_rowcol_to_projection(const double *adfGeoTransform,
		int col, int row,
		double* out_projx, double* out_projy);



	/**********************************************************************//**
	 * @brief	批量地理(投影)坐标转影像行列坐标.
	 *
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/11/03
	 *
	 * @param [in]	adfGeoTransform	坐标转换参数(仿射变换).
	 * @param		proj			地理坐标数组指针.
	 * @param		nproj			地理坐标个数.
	 * @param [out] out_rowcol	    输出影像行列坐标.
	 *************************************************************************/
	_US_UTIL_DLL bool multi_projection_to_image_rowcol(const double *adfGeoTransform,
		const unispace::us_vec2<double>* proj,
		const int nproj,
		unispace::us_vec2<int>* out_rowcol);
}

#endif // !__US_AFFINE_TRANSFORM_HPP__

