/**********************************************************************//**
 * @file us_grid_meter.hpp
 *
 * Declares the grid meter class.
 *************************************************************************/

#ifndef __US_GRID_METER_HPP__
#define __US_GRID_METER_HPP__


#ifndef __US_GEO_RECT_HPP__
#include "util/math/us_geo_rect.hpp"
#endif

#ifndef __US_GRID_BASE_HPP__
#include "us_grid_base.hpp"
#endif

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_grid_meter 
	 * @brief	米网格，基准网格为1m*1m的投影网格，不跨带.<br>
	 * 			符号位1bit，整米占用24位（±16777215），小数占用7位(约0.008米精度)。<br>
	 *			rect为米单位，corner，center等经度方向(X)在前，纬度方向(Y)在后。<br>
	 *			对于某一级别的rect的size，可以通过2^(31-level-7)计算得到。<br>
	 *			一维编码二进制穿插纬度方向在前。其中横向坐标中提取出带号，存储在m_full_id 中。
	 *			一维编码和二维编码都中不包含带号。<br>
	 *			大地坐标系是X轴朝北，Y轴向东。此处约定方向与大地坐标系相反。
	 *
	 * @author yimin.liu@unispace-x.com
	 * @date 2016/3/17
	 *************************************************************************/

	class _US_GRID_SYSTEM_DLL us_grid_meter :
		public us_grid_base
	{
	public:
		// 构造函数
		us_grid_meter();

		/**********************************************************************//**
		 * @brief	构造函数，从一个网格ID来构造.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/28
		 *
		 * @param fullid  网格全ID.
		 *************************************************************************/
		explicit us_grid_meter(const us_grid_id& fullid);

		/**********************************************************************//**
		 * @brief	拷贝构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/28
		 *
		 * @param other 米网格对象.
		 *************************************************************************/
		us_grid_meter(const us_grid_meter& other);

		// 判等操作(比对网格等级和网格坐标)
		bool operator== (const us_grid_meter& t);

		/**********************************************************************//**
		 * @brief	获取偏移网格.
		 *			<br>获取一个相对于本网格对象有一个偏移量的网格，偏移量由参数决定。<br>因为
		 *			各个级别的网格纵横向的分割都是有限的，所以偏移量不应该超过限制。如果超过限制
		 *			返回的将是把网格看作一个球，两个方向超过限制后回到原点，继续偏移到一个位置。
		 *			<br>例如:第1级网格一共是4*4=16个网格，如果对(1,0)网格偏移(1,2)就会获取到
		 *			(-2,-2)网格。中国范围内米网格是不应存在负数的，所以出现了负数时应检查。因为
		 *			这里未考虑跨带的情况，所以不是有效的网格编码就是有效的区域。
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
		us_grid_meter get_offset_grid(int horizontal, int vertical)const;



		// 获取网格有效性
		virtual bool is_valid()const;
		// 获取网格地理范围
		virtual const us_geo_rect& get_geo_rect()const;
		// 获取网格中心点坐标
		virtual us_vec2<double> get_center()const;
		// 获取网格角点坐标
		virtual us_vec2<double> get_corner(us_geo_rect::CONRNER_TYPE type)const;

		/**********************************************************************//**
		 * @brief	根据坐标位置计算网格编码，坐标为网格类型对应的坐标。如果level不在 0~31的
		 * 			范围内，也属于无效网格。无论参数是否合理，都会照样设置。参数不合理，将得到
		 * 			无效网格。<br>
		 * 			此处参数的<b>lng_x</b>指传入的应该是大地坐标系中的经度方向坐标，即<b>Y坐标</b>。
		 * 			<b>lat_y</b>指传入的坐标应该是大地坐标系中的纬度方向的坐标，即<b>X坐标</b>。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 *
		 * @param	lng_x_band	经度方向坐标(大地Y坐标，有带号).
		 * @param	lat_y		纬度方向坐标(大地X坐标).
		 * @param	level		网格级别.
		 * @return	网格为有效网格返回 true，否则返回 false.
		 *************************************************************************/
		virtual bool set_grid_from_coords(double lng_x_band, double lat_y, int level);


		// 给定网格ID，设置网格对象属性值
		virtual bool set_grid_from_id(const us_grid_id& gid);
		// 给定网格一维编码ID和level，设置网格对象属性值
		virtual bool set_grid_from_id(uint64_t id, int level);

		/**********************************************************************//**
		 * @brief	给定网格二维编码和level，设置网格对象属性值.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	lng_x_code	经度方向坐标编码(不含带号).
		 * @param	lat_y_code	纬度方向坐标编码.
		 * @param	band		带号(大地Y坐标).
		 * @param	level		网格级别.
		 * @return	成功返回 true，失败返回 false.
		 *************************************************************************/
		virtual bool set_grid_from_coord_id(uint32_t lng_x_code, uint32_t lat_y_code,int band, int level);
		
	protected:
		// 更新网格地理范围
		void update_geo_rect();
		// 更新网格地理范围，传入的经纬度方向坐标编码作为更新参考
		void update_geo_rect(uint32_t lng_x_code, uint32_t lat_y_code);
	protected:
		/** 网格的地理范围 【注意：rect中各点的x,y方向与地理坐标的xy方向相反】 */
		us_geo_rect m_rect;
		/** 定点数整数部分bit位数. */
		static const int s_fixed_int_width;
	};

}

#endif