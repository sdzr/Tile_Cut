/**********************************************************************//**
 * @file math\us_size.hpp
 *
 * Declares the size class.
 *************************************************************************/

#ifndef __US_SIZE_HPP__
#define __US_SIZE_HPP__

#ifndef __US_VEC2_HPP__
#include "us_vec2.hpp"
#endif

// #include <string>
// #include <type_traits>

namespace unispace
{

	/**********************************************************************//**
	 * @class	us_size
	 * @brief	二维尺寸大小类。
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/14
	 *************************************************************************/

	template<typename T = float>
	class us_size{
		static_assert(std::is_same<T, int>::value ||
		std::is_same<T, float>::value ||
		std::is_same<T, double>::value,
		"template parameter must is int or float or double");
	public:
		T m_width;
		T m_height;
	public:

		/******************************************************************//**
		 * @fn		us_size::us_size()
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 *********************************************************************/
		us_size();

		/******************************************************************//**
		 * Constructor.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 * @param width  The width.
		 * @param height The height.
		 *********************************************************************/

		us_size(T width, T height);

		/******************************************************************//**
		 * Copy constructor.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 * @param other The other.
		 *********************************************************************/

		us_size(const us_size& other);

		/******************************************************************//**
		 * Constructor.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 * @param v The us_vec2&lt;T&gt; to process.
		 *********************************************************************/

		explicit us_size(const us_vec2<T>& v);

		// 重载运算符
		us_size& operator= (const us_size& other);
		us_size& operator= (const us_vec2<T>& v);
		// 重载 + 加上一个 size 后的值
		us_size operator+(const us_size& right) const;
		// 重载 - 减去一个 size 后的值
		us_size operator-(const us_size& right) const;
		// 重载 * 放大 scale 倍 后的值
		us_size operator*(double scale) const;
		// 重载 / 缩小 scale 倍 后的值
		us_size operator/(double scale) const;

		// 重载 == 操作
		bool operator == (const us_size& t)const;
		// 重载 != 操作
		bool operator != (const us_size& t)const;

		/**********************************************************************//**
		 * @brief	获取缩放后的size值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/01
		 * @param	scale_factor The scale factor.
		 * @return	一个缩放后的us_size.
		 *************************************************************************/
		us_size scale(const double scale_factor)const;

		/**********************************************************************//**
		 * @brief	获取缩放后的size值.
		 * @author	2016/11/01
		 * @date	2016/3/24
		 * @param	scale_factor_x The scale factor x coordinate.
		 * @param	scale_factor_y The scale factor y coordinate.
		 * @return	一个缩放后的us_size.
		 *************************************************************************/
		us_size scale(const double scale_factor_x, const double scale_factor_y)const;

		/**********************************************************************//**
		 * @brief	判断是否是 0 size (高和宽都是0)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/24
		 * @return	true if zero, false if not.
		 *************************************************************************/
		bool is_zero()const;

		/**********************************************************************//**
		 * @brief	判断等于操作，主要是为 浮点数进行的.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/24
		 * @param	t	进行比较的对象.
		 *
		 * @return	两个us_size的高宽都相等，返回true.否则false.
		 *************************************************************************/
		bool equals(const us_size& t) const;

		/**********************************************************************//**
		 * @brief	判断宽或高的值是否有负数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/24
		 * @return	true if negative, false if not.
		 *************************************************************************/
		bool has_negative()const;

		/**********************************************************************//**
		 * @brief	判断宽或高的值是否有非正数值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/24
		 * @return	true 有非正数值, false 无非正数值.
		 *************************************************************************/
		bool has_non_positive()const;

		/*****************************************************************//**
		 * @fn		us_size& us_size::set_size(T width, T height);
		 * @brief	设置 size 的值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	width  The width.
		 * @param	height The height.
		 * @return	A reference to an us_size.
		 ********************************************************************/
		us_size& set_size(T width, T height);

		/*****************************************************************//**
		 * @brief	对size自身进行缩放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/01
		 * @param	scale_factor The scale factor.
		 * @return	A reference to an us_size.
		 *********************************************************************/
		us_size& set_scale(const double scale_factor);

		/*****************************************************************//**
		 * @brief	对size自身进行缩放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/01
		 * @param	scale_factor_x The scale factor x coordinate.
		 * @param	scale_factor_y The scale factor y coordinate.
		 * @return	A reference to an us_size.
		 *********************************************************************/
		us_size& set_scale(const double scale_factor_x, const double scale_factor_y);

		// 重载 += 自身加上一个 size 后的值
		us_size& operator+=(const us_size& right);
		// 重载 -= 自身减去一个 size 后的值
		us_size& operator-=(const us_size& right);
		// 重载 *= 自身放大 scale 倍 后的值
		us_size& operator*=(double scale);
		// 重载 /= 自身缩小 scale 倍 后的值
		us_size& operator/=(double scale);

	public:
		// 转换 us_size 到 vec2【(vec2)obj的形式】
		operator us_vec2<T>() const;


		/******************************************************************//**
		 * @fn		std::string us_size::to_string()const;
		 * @brief	转换为字符串.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return This object as a std::string.
		 *********************************************************************/
		std::string to_string()const;

		/******************************************************************//**
		 * @fn		static const us_size us_size::zero();
		 * @brief	获取零size.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	A const us_size.
		 *********************************************************************/
		static const us_size zero();
	};
}

//****************************************************************************//


#endif //!__US_SIZE_HPP__