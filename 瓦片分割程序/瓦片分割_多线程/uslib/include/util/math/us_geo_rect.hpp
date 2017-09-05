/**********************************************************************//**
 * @file math\us_geo_rect.hpp
 *
 * Declares the geo rectangle class.
 *************************************************************************/

#ifndef __US_GEO_RECT_HPP__
#define __US_GEO_RECT_HPP__

#ifndef __US_RECT_HPP__
#include "us_rect.hpp"
#endif



#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif




namespace unispace
{
	/**********************************************************************//**
	 * @class	us_geo_rect
	 * @brief	地理范围矩形.
	 * 			约定使用us_vec2作为经纬度坐标，x为经度方向，y为纬度。<br>
	 * 			即以x为横向方向，y为纵向方向。这与大地坐标(geodetic coordinate)的方向是相反的。
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/09
	 *************************************************************************/
	class _US_UTIL_DLL us_geo_rect :
		public us_rect<double>
	{
	public:
		/** Values that represent conrners types. */
		enum _US_UTIL_DLL CONRNER_TYPE
		{
			WEST_NORTH,	///< 西北
			EAST_NORTH,	///< 东北
			EAST_SOUTH,	///< 东南
			WEST_SOUTH	///< 西南
		};

		using us_rect::operator==;
		using us_rect::operator!=;

	public:

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 *************************************************************************/
		us_geo_rect();
		us_geo_rect(const us_rect<double>& other);
		us_geo_rect(const us_geo_rect& other);

		/**********************************************************************//**
		 * @brief	构造函数(西东南北)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	west  西部界限.
		 * @param	east  东部界限.
		 * @param	south 南部界限.
		 * @param	north 北部界限.
		 *************************************************************************/
		us_geo_rect(double west, double east, double south, double north);

		/**********************************************************************//**
		 * @brief	获取东部界限值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The east.
		 *************************************************************************/
		double get_east()const;

		/**********************************************************************//**
		 * @brief	获取西部界限值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The west.
		 *************************************************************************/
		double get_west()const;

		/**********************************************************************//**
		 * @brief	获取北部界限值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The north.
		 *************************************************************************/
		double get_north()const;

		/**********************************************************************//**
		 * @brief	获取南部界限值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The south.
		 *************************************************************************/
		double get_south()const;

		/**********************************************************************//**
		 * @brief	获取角点(默认西北)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	type 角点类型[WestNorth;EastNorth;EastSouth;WestSouth].
		 * @return	角点坐标.
		 *************************************************************************/
		us_vec2<double> get_corner(CONRNER_TYPE type)const;

		/**********************************************************************//**
		 * @brief	获取所有角点(按照[西北,东北,东南,西南)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	[out] out_vec2_array 如果不是 NULL，用于传出所有角点坐标的值
		 *************************************************************************/
		void get_all_corner(us_vec2<double>* out_vec2_array)const;

		/**********************************************************************//**
		 * @brief	获取恰好包含 rect 与本对象的矩形(最大组合矩形)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	rect The rectangle.
		 * @return	组合后的地理矩形.
		 *************************************************************************/
		us_geo_rect get_combine(const us_rect& rect)const;

		/**********************************************************************//**
		 * @brief	设置地理范围(西东南北)
		 * @author	yimin.liu@unispace-x.com
		 * @date		2016/3/14
		 * @param	west  西部界限.
		 * @param	east  东部界限.
		 * @param	south 南部界限.
		 * @param	north 北部界限.
		 * @return	对象自身的引用.
		 *************************************************************************/
		us_geo_rect& set_geo_rect(double west, double east, double south, double north);

		/**********************************************************************//**
		 * @brief	设置东部界限值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	east 东部界限.
		 * @return	A reference to an us_geo_rect.
		 *************************************************************************/
		us_geo_rect& set_east(double east);

		/**********************************************************************//**
		 * @brief	设置西部界限值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	west 西部界限.
		 * @return	A reference to an us_geo_rect.
		 *************************************************************************/
		us_geo_rect& set_west(double west);

		/**********************************************************************//**
		 * @brief	设置北部界限值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	south 南部界限.
		 * @return	A reference to an us_geo_rect.
		 *************************************************************************/
		us_geo_rect& set_north(double south);

		/**********************************************************************//**
		 * @brief	设置南部界限值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	north 北部界限.
		 * @return	A reference to an us_geo_rect.
		 *************************************************************************/
		us_geo_rect& set_south(double north);

		/**********************************************************************//**
		 * @brief	判断矩形是否为有效的地理矩形.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	true if valid, false if not.
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
#endif //!__US_GEO_RECT_HPP__