/**********************************************************************//**
 * @file math\us_latlng_rect.hpp
 *
 * Declares the latlng rectangle class.
 *************************************************************************/

#ifndef __US_LATLNG_RECT_HPP__
#define __US_LATLNG_RECT_HPP__

#ifndef __US_GEO_RECT_HPP__
#include "us_geo_rect.hpp"
#endif

#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif



namespace unispace
{
	/**********************************************************************//**
	 * @class	us_latlng_rect
	 * @brief	经纬度地理范围矩形
	 * 			<pre>
	 * 			约定使用us_vec2作为经纬度坐标，x为经度(lng)，y为纬度(lat)。
	 * 			以经度方向(x)的长度为宽度，纬度方向(y)的长度为高度。
	 * 			</pre>
	 * @author yimin.liu@unispace-x.com
	 * @date 2016/3/14
	 *************************************************************************/
	class _US_UTIL_DLL us_latlng_rect :
		public us_geo_rect
	{
	public:

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 *************************************************************************/
		us_latlng_rect();
		// 从地理范围构造
		us_latlng_rect(const us_geo_rect& other);
		// 从一般矩形范围构造
		us_latlng_rect(const us_rect<double>& other);


		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	west  The west.
		 * @param	east  The east.
		 * @param	south The south.
		 * @param	north The north.
		 *************************************************************************/

		us_latlng_rect(double west, double east, double south, double north);
	public:

		/**********************************************************************//**
		 * @brief	判断矩形是否为有效的经纬度地理矩形.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	有效返回 true,无效返回 false.
		 *************************************************************************/

		virtual bool is_valid()const;

		/**********************************************************************//**
		 * @brief	转换为字符串.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	This object as a std::string.
		 *************************************************************************/

		virtual std::string to_string()const;
	};
}

#endif //!__US_LATLNG_RECT_HPP__