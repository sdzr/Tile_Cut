/**********************************************************************//**
 * @file us_grid_degree.hpp
 *
 * Declares the grid degree class.
 *************************************************************************/

#ifndef __US_GRID_DEGREE_HPP__
#define __US_GRID_DEGREE_HPP__

#ifndef __US_LATLNG_RECT_HPP__
#include "util/math/us_latlng_rect.hpp"
#endif

#ifndef __US_GRID_BASE_HPP__
#include "us_grid_base.hpp"
#endif


namespace unispace
{
	/**********************************************************************//**
	 * @class	us_grid_degree
	 * @brief	经纬度网格.<br>
	 *			基准网格大小为<b>1° x 1°</b>。<br>
	 *			符号位1bit，整度占用8位，小数占用23位，以便网格ID编码为正值。<br>
	 *			各个基本属性，如rect，corner，center等均用度单位，经度在前纬度在后。<br>
	 *			网格构建范围：经度（-180°~180°），纬度（-88°~88°）。<br>
	 *			<b>以4°×4°作为顶级网格（m_level = 6），level<6网格无效。</b>
	 *			一维编码二进制穿插纬度在前。
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/17
	 *************************************************************************/

	class _US_GRID_SYSTEM_DLL us_grid_degree :
		public us_grid_base
	{
	public:
		// 构造函数(设置网格类型为GRID_TYPE_DEGREE)
		us_grid_degree();

		/**********************************************************************//**
		 * @brief	构造函数，从一个网格ID来构造.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/28
		 *
		 * @param fullid  网格全ID.
		 *************************************************************************/
		explicit us_grid_degree(const us_grid_id& fullid);

		/**********************************************************************//**
		 * @brief	拷贝构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/28
		 *
		 * @param other 度网格对象.
		 *************************************************************************/
		us_grid_degree(const us_grid_degree& other);

		// 判等操作(比对网格等级和网格坐标)
		bool operator== (const us_grid_degree& t);


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
		 * @date	2016/4/28
		 * @param	horizontal	横向偏移量.
		 * @param	vertical	纵向偏移量.
		 * @return	返回偏移后的新网格对象.
		 *************************************************************************/
		virtual us_grid_degree get_offset_grid(int horizontal, int vertical)const;

		// 获取网格有效性
		virtual bool is_valid()const;
		// 获取网格地理范围(经纬度范围)
		virtual const us_geo_rect& get_geo_rect()const;
		// 获取网格地理中心点坐标
		virtual us_vec2<double> get_center()const;
		// 获取网格地理角点坐标
		virtual us_vec2<double> get_corner(us_geo_rect::CONRNER_TYPE type)const;

		// 经纬度网格，超出地球范围的时候，返回false，设置为无效网格
		// 如果level不在 0~31的范围内，也属于无效网格
		// 无论参数是否合理，都会照样设置网格属性为参数值，但不会更新一维编码值
		virtual bool set_grid_from_coords(double lng, double lat, int level);
		// 给定网格ID，设置网格对象属性值
		virtual bool set_grid_from_id(const us_grid_id& gid);
		// 给定网格一维编码ID和level，设置网格对象属性值
		virtual bool set_grid_from_id(uint64_t id, int level);


		/**********************************************************************//**
		 * @brief	给定网格二维编码和level，设置网格对象属性值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/31
		 * @param	lngcode	纬度的编码.
		 * @param	latcode 经度的编码.
		 * @param	level   网格级别.
		 * @return	成功返回 true，否则返回 false.
		 *************************************************************************/
		bool set_grid_from_latlng_id(uint32_t lngcode, uint32_t latcode, int level);

	protected:
		// 更新网格地理范围
		void update_geo_rect();
		// 更新网格地理范围，传入的经纬度方向坐标编码作为更新参考
		void update_geo_rect(uint32_t lng_x_code, uint32_t lat_y_code);
	protected:
		/** 经纬度地理范围. */
		us_latlng_rect m_rect;
		/** 定点数整数部分bit位数. */
		static const int s_fixed_int_width;
		/** 坐标系整体偏移. */
		// static const double m_coord_sys_offset;

		/**
		如果不对坐标进行整体的偏移，即采取区分四个象限的做法。实际上编码依然连续，因为负数以补码的形式表示。
		只是在对网格进行向上合并与向下分割的时候，要注意，不要再做区分。取上一级(低精度)网格的时候，抹去多余
		位即可，取下一级的四个网格的时候，需要分别对x和y做补充一位，来表示更高精度网格。
		例如：[-1,-2]网格，向上合并的时候应该与[-1,-1],[-2,-1],[-2,-2]合并成一个编码为[-2,-2]的网格。
		而: -2 & 0xfffffffe = -2;-1 & 0xfffffffe = -2;
		将[-2,-2]网格拆分成四个网格也是一样的，因为 -2 | 0x00000001 = -1
		注:-2的二进制形式为 0xffffffe;-1为0xffffffff
		**/
	};

}


#endif //!__US_GRID_DEGREE_HPP__