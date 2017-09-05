/**********************************************************************//**
 * @file us_grid_base.hpp
 *
 * Declares the grid base class.
 *************************************************************************/

#ifndef __US_GRID_BASE_HPP__
#define __US_GRID_BASE_HPP__

#ifndef __US_GRID_ID_HPP__
#include "us_grid_id.hpp"
#endif
#ifndef __US_GEO_RECT_HPP__
#include "util/math/us_geo_rect.hpp"
#endif

#ifndef __US_GRID_SYSTEM_HPP__
#include "us_grid_system.hpp"
#endif



namespace unispace
{

	/**********************************************************************//**
	 * @class	us_grid_base
	 * @brief	网格定义基类
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/14
	 *************************************************************************/
	class _US_GRID_SYSTEM_DLL us_grid_base
	{
	protected:

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 *************************************************************************/
		us_grid_base();

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/14
		 *************************************************************************/
		virtual ~us_grid_base(){}
	public:

		/**********************************************************************//**
		 * @brief	获取网格一维编码ID.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @return	网格的一维编码ID.
		 *************************************************************************/
		uint64_t get_id()const;

		/**********************************************************************//**
		 * @brief	获取网格全ID.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @return	网格的全ID(us_grid_id).
		 *************************************************************************/
		us_grid_id get_full_id()const;

		/**********************************************************************//**
		 * @brief	获取网格类型.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @return	The type.
		 *************************************************************************/
		us_grid_type get_type()const;

		/**********************************************************************//**
		 * @brief	获取网格级别信息.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @return	The level.
		 *************************************************************************/
		uint32_t get_level()const;
		
		/**********************************************************************//**
		 * @brief	获取父级网格.
		 *			网格按照四叉分割而来，除了0级网格外，每一个网格都有一个父级网格。<br>
		 *			0级网格一共有四个，这四个本应该有一个共同的父级网格，但是在这里的编码中无法表示。
		 *			所以默认0级网格没有父级网格。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/13
		 * @param	out_parent	传出父网格.
		 * @return	成功返回true，失败返回false.
		 *************************************************************************/

		virtual bool get_parent_grid(us_grid_base* out_parent)const;
		
		/**********************************************************************//**
		 * @brief	获取四个子网格.
		 *			除了最精细级别(31级)的网格不能够再继续四叉分割外，所有的网格都可以分作四个子网格。
		 *			如果不需要某个方位的子网格，只需要对应的参数传NULL即可。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/13
		 * @param	out_sub_lt	传出左上角子网格.
		 * @param	out_sub_rt	传出右上角子网格.
		 * @param	out_sub_lb	传出左下角子网格.
		 * @param	out_sub_rb	传出右下角子网格.
		 * @return	成功返回true，失败返回false.
		 *************************************************************************/
		virtual bool get_sub_grid(us_grid_base* out_sub_lt, us_grid_base* out_sub_rt,
						  us_grid_base* out_sub_lb, us_grid_base* out_sub_rb)const;

		/**********************************************************************//**
		 * @brief	获取偏移网格.
		 *			<br>获取一个相对于本网格对象有一个偏移量的网格，偏移量由参数决定。<br>因为
		 *			各个级别的网格纵横向的分割都是有限的，所以偏移量不应该超过限制。如果超过限制
		 *			返回的将是把网格看作一个球，两个方向超过限制后回到原点，继续偏移到一个位置。
		 *			<br>例如:第1级网格一共是4*4=16个网格，如果对(1,0)网格偏移(1,2)就会获取到
		 *			(-2,-2)网格。
		 *			<pre>第1级网格，4x4(实际编码值可能会扩大2^30)
		 *			+-----+-----+-----+-----+
		 *			|-2,1 |-1,1 |0,1  |1,1  |
		 *			+-----+-----+-----+-----+
		 *			|-2,0 |-1,0 |0,0  |1,0  |
		 *			+-----+-----+-----+-----+
		 *			|-2,-1|-1,-1|0,-1 |1,-1 |
		 *			+-----+-----+-----+-----+
		 *			|-2,-2|-1,-2|0,-2 |1,-2 |
		 *			+-----+-----+-----+-----+
		 *			</pre>
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/13
		 * @param	out_grid	传出偏移后的网格.
		 * @param	horizontal	横向偏移量.
		 * @param	vertical	纵向偏移量.
		 * @return	成功返回true，失败返回false.
		 *************************************************************************/
		virtual bool get_offset_grid(us_grid_base* out_grid, int horizontal, int vertical)const;


	public:

		/**********************************************************************//**
		 * @brief	获取网格有效性.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @return	true if valid, false if not.
		 *************************************************************************/

		virtual bool is_valid()const = 0;

		/**********************************************************************//**
		 * @brief	获取网格地理范围.<br>
		 *			要注意，经纬度网格下获取的是一个指向 @ref us_latlng_rect 的对象的引用。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @return	The geo rectangle.
		 *************************************************************************/
		virtual const us_geo_rect& get_geo_rect()const = 0;

		/**********************************************************************//**
		 * @brief	获取网格中心点坐标.<br>
		 *			经纬度网格下，vec2的x表示经度，y表示纬度。<br>
		 *			米网格下，vec2的x表示横向位置，y表示纵向。与大地坐标相反。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @return	The center.
		 *************************************************************************/
		virtual us_vec2<double> get_center()const = 0;

		/**********************************************************************//**
		 * @brief	获取网格角点坐标.<br>
		 *			经纬度网格下，vec2的x表示经度，y表示纬度。<br>
		 *			米网格下，vec2的x表示横向位置，y表示纵向。与大地坐标相反。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	type The type.
		 * @return	The corner.
		 *************************************************************************/
		virtual us_vec2<double> get_corner(us_geo_rect::CONRNER_TYPE type)const = 0;

		/**********************************************************************//**
		 * @brief	根据坐标位置计算网格编码，坐标为网格类型对应的坐标. <br>
		 * 			如果是经纬度网格，超出地球范围的时候，返回false，设置为无效网格.<br>
		 * 			如果level不在0~31的范围内，也属于无效网格 无论参数是否合理，都会照样设置.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	x	    The x coordinate.
		 * @param	y	    The y coordinate.
		 * @param	level The level.
		 * @return	true if it succeeds, false if it fails.
		 *************************************************************************/
		virtual bool set_grid_from_coords(double x, double y, int level) = 0;

		/**********************************************************************//**
		 * @brief	给定网格ID，设置网格对象属性值.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	gid The gid.
		 * @return	true if it succeeds, false if it fails.
		 *************************************************************************/
		virtual bool set_grid_from_id(const us_grid_id& gid) = 0;

		/**********************************************************************//**
		 * @brief	给定网格一维编码ID和level，设置网格对象属性值.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	id    The identifier.
		 * @param	level The level.
		 * @return	true if it succeeds, false if it fails.
		 *************************************************************************/
		virtual bool set_grid_from_id(uint64_t id, int level) = 0;

		/**********************************************************************//**
		 * @brief	获取给定类型的网格的某个级别的单位地理长度。
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/12
		 * @param	type  网格类型.
		 * @param	level 网格级别.
		 * @return	网格类型和级别合法时，返回长度。失败返回负值.
		 *************************************************************************/
		static double grid_unit_length(us_grid_type type, int level);
	protected:
		us_grid_id		m_full_id;	//全编码ID，包含level和64位完整ID
	};

}
#endif //!__US_GRID_BASE_HPP__
