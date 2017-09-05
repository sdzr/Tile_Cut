/**********************************************************************//**
 * @file math\us_rect.hpp
 *
 * Declares the rectangle class.
 *************************************************************************/

#ifndef __US_RECT_HPP__
#define __US_RECT_HPP__

#ifndef __US_SIZE_HPP
#include "us_size.hpp"
#endif

/*
* 这个rect是没有方向的，有的只是一个起始点和一个尺寸大小
* 假设坐标系是 x向右y向下的，那么rect就是这样的
*	origin(x,y)
*		O-------------+
*		|   rect范围   |height
*       +-------------+
*			width
* 如果坐标系是 x向右y向上，那么rect就是这样的
*		+-------------+
*		|   rect范围   |height
*       O-------------+
*	origin	width
*
* 所有的计算都以高宽是正数为基础，如果高宽有负数，部分计算的结果将出现错误
*/


namespace unispace
{

	/**********************************************************************//**
	 * @class	us_rect
	 * @brief	二维矩形包围范围
	 * 			<pre>
	 * 			这个rect是没有方向的，有的只是一个基准(起始)点和一个尺寸大小
	 *			假设坐标系是 x向右y向下的，那么rect就是这样的
	 *			origin(x,y)
	 *				O-------------+
	 *				|   rect范围   |height
	 *				+-------------+
	 *					width
	 *			如果坐标系是 x向右y向上，那么rect就是这样的
	 *				+-------------+
	 *		 		|   rect范围   |height
	 *				O-------------+
	 *			origin	width
	 *			所有的计算都以高宽是正数为基础，如果高宽有负数，部分计算的结果将出现错误
	 *			其中宽度的设置以 x 坐标差为基准
	 *			</pre>
	 * @author yimin.liu@unispace-x.com
	 * @date  2016/3/14
	 *************************************************************************/
	template<typename T = float>
	class us_rect{
		static_assert(std::is_same<T, int>::value ||
		std::is_same<T, float>::value ||
		std::is_same<T, double>::value,
		"template parameter must is int or float or double");
	public:

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 *************************************************************************/

		us_rect();

		/**********************************************************************//**
		 * @brief	构造函数。指定基准点和大小.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 *
		 * @param	origin 矩形基准点.
		 * @param	size   矩形大小.
		 *************************************************************************/

		us_rect(const us_vec2<T>& origin, const us_size<T>& size);

		/**********************************************************************//**
		 * @brief	构造函数。指定基准点坐标和高宽.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 *
		 * @param x		 矩形基准点 x 坐标.
		 * @param y		 矩形基准点 y 坐标.
		 * @param width  矩形宽度(x方向长度).
		 * @param height 矩形高度(y方向长度).
		 *************************************************************************/

		us_rect(T x, T y, T width, T height);

		/**********************************************************************//**
		 * @brief	构造函数。指定基准点和对角点.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 *
		 * @param	origin			矩形基准点.
		 * @param	diagonal_point	矩形基准点的对角点.
		 *************************************************************************/

		us_rect(const us_vec2<T>& origin, const us_vec2<T>& diagonal_point);

		/**********************************************************************//**
		 * @brief	拷贝构造函数.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 *
		 * @param	other The other.
		 *************************************************************************/

		us_rect(const us_rect& other);
	public:

		/**********************************************************************//**
		 * @brief	设置矩形的基准点位置.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	origin 矩形范围的基准点.
		 * @return	A reference to an us_rect.
		 *************************************************************************/

		us_rect& set_origin(const us_vec2<T>& origin);

		/**********************************************************************//**
		 * @brief	设置矩形基准点的位置.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	x	基准点的X坐标.
		 * @param	y	基准点的Y坐标.
		 * @return	这个 us_rect 自身的引用.
		 *************************************************************************/

		us_rect& set_origin(T x, T y);

		/**********************************************************************//**
		 * @brief	设置矩形对角点的位置.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	point	矩形范围基准点的对角点.
		 * @return	A reference to an us_rect.
		 *************************************************************************/

		us_rect& set_diagonal_point(const us_vec2<T>& point);

		/**********************************************************************//**
		 * @brief	设置矩形对角点的位置.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	x	对角点的X坐标.
		 * @param	y	对角点的Y坐标.
		 * @return	这个 us_rect 自身的引用.
		 *************************************************************************/

		us_rect& set_diagonal_point(T x, T y);

		/**********************************************************************//**
		 * @brief	设置矩形的宽.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	width	矩形的新宽度(x方向).
		 * @return	A reference to an us_rect.
		 *************************************************************************/

		us_rect& set_width(T width);

		/**********************************************************************//**
		 * @brief	设置矩形的高.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	height	矩形的新高度值.
		 * @return	A reference to an us_rect.
		 *************************************************************************/

		us_rect& set_height(T height);

		/**********************************************************************//**
		 * @brief	设置矩形的大小.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	size	矩形的新大小值.
		 * @return	A reference to an us_rect.
		 *************************************************************************/

		us_rect& set_size(const us_size<T>& size);

		/**********************************************************************//**
		 * @brief	设置矩形的大小.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	width  The width.
		 * @param	height The height.
		 * @return	A reference to an us_rect.
		 *************************************************************************/
		us_rect& set_size(T width, T height);

		/**********************************************************************//**
		 * @brief	设置矩形的基准点和大小.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	t The us_rect to process.
		 * @return	A reference to an us_rect.
		 *************************************************************************/
		us_rect& set_rect(const us_rect& t);

		/**********************************************************************//**
		 * @brief	设置矩形的基准点和大小.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	origin 基准点坐标.
		 * @param	size   大小.
		 * @return	A reference to an us_rect.
		 *************************************************************************/
		us_rect& set_rect(const us_vec2<T>& origin,const us_size<T>& size);


		/**********************************************************************//**
		 * @brief	设置矩形的基准点和大小.
		 *			通过多个点来获取一个范围，点的数量必须大于1。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	points	点坐标.
		 * @param	npoint	点个数.
		 * @return	A reference to an us_rect.
		 *************************************************************************/
		us_rect& set_rect(const us_vec2<T>* points, size_t npoint);

		/**********************************************************************//**
		 * @brief	对矩形自身进行位置平移.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	dx X 方向平移量.
		 * @param	dy Y 方向平移量.
		 * @return	A reference to an us_rect.
		 *************************************************************************/
		us_rect& translation(T dx, T dy);

		/**********************************************************************//**
		 * @brief	对矩形自身大小进行等比缩放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	scale_factor The scale factor.
		 * @return	A reference to an us_rect.
		 *************************************************************************/
		us_rect& set_scale(double scale_factor);

		/**********************************************************************//**
		 * @brief	对矩形自身大小进行缩放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/01
		 * @param	x_scale_factor X方向缩放因子.
		 * @param	y_scale_factor Y方向缩放因子.
		 * @return	A reference to an us_rect.
		 *************************************************************************/
		us_rect& set_scale(double x_scale_factor,double y_scale_factor);

		/**********************************************************************//**
		 * @brief	对矩形自身以中心位置为基准点进行缩放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	scale_factor The scale factor.
		 * @return	A reference to an us_rect.
		 *************************************************************************/
		us_rect& set_scale_with_center(double scale_factor);

		/**********************************************************************//**
		 * @brief	对矩形自身以中心位置为基准点进行缩放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/13
		 * @param	x_scale_factor X方向缩放因子.
		 * @param	y_scale_factor Y方向缩放因子.
		 * @return	A reference to an us_rect.
		 *************************************************************************/
		us_rect& set_scale_with_center(double x_scale_factor, double y_scale_factor);


	public:

		/**********************************************************************//**
		 * @brief	Equality operator.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	t The us_rect to process.
		 * @return	true if the parameters are considered equivalent.
		 *************************************************************************/
		bool operator== (const us_rect& t)const;

		/**********************************************************************//**
		 * Inequality operator.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	t The us_rect to process.
		 * @return	true if the parameters are not considered equivalent.
		 *************************************************************************/
		bool operator != (const us_rect& t)const;




		/**********************************************************************//**
		 * @brief	获取矩形的宽度.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The width.
		 *************************************************************************/
		T get_width()const;

		/**********************************************************************//**
		 * @brief	获取矩形的高度.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The height.
		 *************************************************************************/
		T get_height()const;

		/**********************************************************************//**
		 * @brief	获取矩形的X方向最小值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/01
		 * @return	The min x.
		 *************************************************************************/
		T get_min_x()const;

		/**********************************************************************//**
		 * @brief	获取矩形的y方向最小值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/01
		 * @return	The min y.
		 *************************************************************************/
		T get_min_y()const;

		/**********************************************************************//**
		 * @brief	获取矩形的X方向最大值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/01
		 * @return	The max x.
		 *************************************************************************/
		T get_max_x()const;

		/**********************************************************************//**
		 * @brief	获取矩形的y方向最大值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/01
		 * @return	The max y.
		 *************************************************************************/
		T get_max_y()const;

		/**********************************************************************//**
		 * @brief	获取矩形的尺寸大小.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The size.
		 *************************************************************************/
		us_size<T> get_size()const;

		/**********************************************************************//**
		 * @brief	获取矩形中心点坐标.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	中心点坐标.
		 *************************************************************************/
		us_vec2<T> get_center()const;

		/**********************************************************************//**
		 * @brief	获取矩形基准点点坐标.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The origin.
		 *************************************************************************/
		us_vec2<T> get_origin()const;

		/**********************************************************************//**
		 * @brief	获取矩形对角点坐标.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The diagonal point.
		 *************************************************************************/
		us_vec2<T> get_diagonal_point()const;

		/**********************************************************************//**
		 * @brief	获取矩形的面积.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The area.
		 *************************************************************************/
		T get_area()const;

		/**********************************************************************//**
		 * @brief	获取对矩形大小进行等比缩放后的值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/24
		 * @param	scale_factor The scale factor.
		 * @return	An us_rect.
		 *************************************************************************/
		us_rect scale(double scale_factor)const;

		/**********************************************************************//**
		 * @brief	获取对矩形大小进行缩放后的值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/01
		 * @param	x_scale_factor X方向缩放因子.
		 * @param	y_scale_factor Y方向缩放因子.
		 * @return	An us_rect.
		 *************************************************************************/
		us_rect scale(double x_scale_factor,double y_scale_factor)const;

		/**********************************************************************//**
		 * @brief	获取对矩形以中心位置为基准点进行缩放后的值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/24
		 * @param	scale_factor The scale factor.
		 * @return	An us_rect.
		 *************************************************************************/
		us_rect scale_with_center(double scale_factor)const;

		/**********************************************************************//**
		 * @brief	获取对矩形以中心位置为基准点进行缩放后的值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/13
		 * @param	x_scale_factor X方向缩放因子.
		 * @param	y_scale_factor Y方向缩放因子.
		 * @return	An us_rect.
		 *************************************************************************/
		us_rect scale_with_center(double x_scale_factor, double y_scale_factor)const;


		/**********************************************************************//**
		 * @brief	获取与 rect 的重叠部分(交集)，结果保存在out_rect中。不传out_rect即返回是否有交集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	rect	待判断是否有重叠部分的矩形.
		 * @param	[out] out_rect 传出重叠部分.
		 * @return	true if it succeeds, false if it fails.
		 *************************************************************************/
		bool get_intersection(const us_rect& rect,us_rect* out_rect = nullptr)const;

		/**********************************************************************//**
		 * @brief	获取恰好包含 rect 与本对象的矩形(最大组合矩形)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	rect The rectangle.
		 * @return	组合后的矩形.
		 *************************************************************************/
		us_rect get_combine(const us_rect& rect)const;

		/**********************************************************************//**
		 * @brief	获取恰好包含 pt点 与本对象的矩形(最大组合矩形)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/21
		 * @param	pt	传入的点.
		 * @return	组合后的矩形.
		 *************************************************************************/
		us_rect get_combine(const us_vec2<T>& pt);

		/**********************************************************************//**
		 * @brief	获取恰好包含 pts中的点 与本对象的矩形(最大组合矩形)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/21
		 * @param	points	传入的点数组.
		 * @param	npoint	传入的点个数.
		 * @return	组合后的矩形.
		 *************************************************************************/
		us_rect get_combine(const us_vec2<T>* points, size_t npoint);

		/**********************************************************************//**
		 * @brief	转为字符串形式.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	This object as a std::string.
		 *************************************************************************/
		virtual std::string to_string()const;

	public:

		/**********************************************************************//**
		 * @brief	判断点 point 是否在矩形范围内【在边界上也算在内】.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	point 待判断的点.
		 * @return	true if contain, false if not.
		 *************************************************************************/
		bool is_contain(const us_vec2<T>& point)const;

		/**********************************************************************//**
		 * @brief	判断点 point(x,y) 是否在矩形范围内【在边界上也算在内】.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	x 待判断点的X坐标.
		 * @param	y 待判断点的Y坐标.
		 * @return	true if contain, false if not.
		 *************************************************************************/
		bool is_contain(T x,T y)const;

		/**********************************************************************//**
		 * @brief	判断 rect 是否在矩形范围内【在边界上也算在内】.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	rect The rectangle.
		 * @return	true if contain, false if not.
		 *************************************************************************/
		bool is_contain(const us_rect& rect)const;

		/**********************************************************************//**
		 * @brief	判断 rect 和矩形是否有重叠部分.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	rect The rectangle.
		 * @return	true if intersection, false if not.
		 *************************************************************************/
		bool is_intersection(const us_rect& rect)const;

		/**********************************************************************//**
		 * @brief	判断矩形是否为有效的矩形(size没有0或负数)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	true if valid, false if not.
		 *************************************************************************/
		virtual bool is_valid()const;
	protected:
		/** 基准点. */
		us_vec2<T> m_origin;
		/** 尺寸大小. */
		us_size<T> m_size;
	};
}

//****************************************************************************//

#endif //!__US_RECT_HPP__
