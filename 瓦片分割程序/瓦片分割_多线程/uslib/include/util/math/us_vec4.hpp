/**********************************************************************//**
 * @file math\us_vec4.hpp
 *
 * Declares the vector 4 class.
 *************************************************************************/

#ifndef __US_VEC4_HPP__
#define __US_VEC4_HPP__


#include <string>
#include <type_traits>


namespace unispace
{

	/**********************************************************************//**
	 * @class	us_vec4
	 * @brief	四维向量
	 * @author yimin.liu@unispace-x.com
	 * @date 2016/3/14
	 *************************************************************************/
	template<typename T = float>
	class us_vec4{
		static_assert(std::is_same<T, int>::value ||
		std::is_same<T, float>::value ||
		std::is_same<T, double>::value,
		"template parameter must is int or float or double");
	public:

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	x	X方向分量.
		 * @param	y	Y方向分量.
		 * @param	z	Z方向分量.
		 * @param	w	W方向分量.
		 *************************************************************************/

		us_vec4(T x = T(0), T y = T(0), T z = T(0), T w = T(0));

		/**********************************************************************//**
		 * @brief	拷贝构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	t The us_vec4 to process.
		 *************************************************************************/

		us_vec4(const us_vec4& t);

		/**********************************************************************//**
		 * @brief	通过点p1和p1构造向量(p1-->p2)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	p1 The first us_vec4.
		 * @param	p2 The second us_vec4.
		 *************************************************************************/

		us_vec4(const us_vec4& p1, const us_vec4& p2);

	public:
		// 运算符重载
		us_vec4& operator = (const us_vec4& t);		//赋值运算
		bool operator == (const us_vec4& t)const;	//判等运算
		bool operator != (const us_vec4& t)const;	//判不等于

		us_vec4 operator + (const us_vec4& t)const;	//加
		us_vec4 operator - (const us_vec4& t)const;	//减
		us_vec4 operator - ()const;					//取负
		us_vec4 operator * (const double scale_factor);	//等比缩放


		us_vec4& operator += (const us_vec4& t);	//自加上
		us_vec4& operator -= (const us_vec4& t);	//自减去
		us_vec4& operator *= (const double scale_factor);//自缩放

	public:

		/**********************************************************************//**
		 * @brief	获取 X 方向分量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The x coordinate.
		 *************************************************************************/
		T get_x()const;

		/**********************************************************************//**
		 * @brief	获取 Y 方向分量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The y coordinate.
		 *************************************************************************/
		T get_y()const;

		/**********************************************************************//**
		 * @brief	获取 Z 方向分量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The z coordinate.
		 *************************************************************************/
		T get_z()const;

		/**********************************************************************//**
		 * @brief	获取 W 方向分量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The w.
		 *************************************************************************/
		T get_w()const;

		/**********************************************************************//**
		 * @brief	获取向量长度.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The length.
		 *************************************************************************/
		double get_length()const;

		/**********************************************************************//**
		 * @brief	获取长度的平方值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	The length squared.
		 *************************************************************************/
		double get_length_squared()const;

		/**********************************************************************//**
		 * @brief	获取向量等比缩放后的值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	scale_factor 缩放因子.
		 * @return	A us_vec4.
		 *************************************************************************/
		us_vec4 scale(const double scale_factor)const;

		/**********************************************************************//**
		 * @brief	获取缩放向量后的值.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 *
		 * @param scale_factor_x The scale factor x coordinate.
		 * @param scale_factor_y The scale factor y coordinate.
		 * @param scale_factor_z The scale factor z coordinate.
		 * @param scale_factor_w The scale factor w.
		 *
		 * @return A us_vec4.
		 *************************************************************************/
		us_vec4 scale(const double scale_factor_x,
					  const double scale_factor_y,
					  const double scale_factor_z,
					  const double scale_factor_w)const;


		/**********************************************************************//**
		 * @brief	判断是否是零向量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	true if zero, false if not.
		 *************************************************************************/
		bool is_zero()const;

	public:

		/**********************************************************************//**
		 * @brief	设置 X,Y,Z,W 的值.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param x The T to process.
		 * @param y The T to process.
		 * @param z The T to process.
		 * @param w The T to process.
		 *************************************************************************/

		void set_xyzw(T x, T y,T z, T w);

		/**********************************************************************//**
		 * @brief	设置 X 方向分量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param x The T to process.
		 *************************************************************************/

		void set_x(T x);

		/**********************************************************************//**
		 * @brief	设置 Y 方向分量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param y The T to process.
		 *************************************************************************/

		void set_y(T y);

		/**********************************************************************//**
		 * @brief	设置 Z 方向分量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param z The T to process.
		 *************************************************************************/

		void set_z(T z);

		/**********************************************************************//**
		 * @brief	设置 W 方向分量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param w The T to process.
		 *************************************************************************/

		void set_w(T w);

		/**********************************************************************//**
		 * @brief	对向量自身进行等比缩放.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	scale_factor 缩放因子.
		 * @return	A reference to an us_vec4.
		 *************************************************************************/

		us_vec4& set_scale(const double scale_factor);

		/**********************************************************************//**
		 * @brief	缩放向量自身.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param scale_factor_x The scale factor x coordinate.
		 * @param scale_factor_y The scale factor y coordinate.
		 * @param scale_factor_z The scale factor z coordinate.
		 * @param scale_factor_w The scale factor w.
		 *
		 * @return A reference to an us_vec4.
		 *************************************************************************/

		us_vec4& set_scale(const double scale_factor_x,
						   const double scale_factor_y,
						   const double scale_factor_z,
						   const double scale_factor_w);

		/**********************************************************************//**
		 * @brief	获取向量的单位向量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return The normalize.
		 *************************************************************************/
		us_vec4 get_normalize()const;

		/**********************************************************************//**
		 * @brief	将量转换为标准化向量.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 *************************************************************************/
		void normalize();

	public:

		/**********************************************************************//**
		 * @brief	获取向量的字符串(形式：vec2<T>(x,y))
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @return This object as a std::string.
		 *************************************************************************/

		std::string to_string()const;
	public:

		/**********************************************************************//**
		 * @brief	获取零向量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @return A const us_vec4.
		 *************************************************************************/

		static const us_vec4 zero();

		/**********************************************************************//**
		 * @brief	获取 X 方向单位向量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @return A const us_vec4.
		 *************************************************************************/

		static const us_vec4 uint_x();

		/**********************************************************************//**
		 * @brief	获取 Y 方向单位向量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @return A const us_vec4.
		 *************************************************************************/

		static const us_vec4 uint_y();

		/**********************************************************************//**
		 * @brief	获取 Z 方向单位向量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @return A const us_vec4.
		 *************************************************************************/

		static const us_vec4 uint_z();

		/**********************************************************************//**
		 * @brief	获取 W 方向单位向量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @return A const us_vec4.
		 *************************************************************************/

		static const us_vec4 uint_w();

		/**********************************************************************//**
		 * @brief	计算v1与v2的点积并返回.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 * @param v1 The first us_vec4.
		 * @param v2 The second us_vec4.
		 * @return A double.
		 *************************************************************************/

		static double dot(const us_vec4 &v1, const us_vec4 &v2);
	public:
		T m_x;
		T m_y;
		T m_z;
		T m_w;
	};

}

//****************************************************************************//


#endif //!__US_VEC4_HPP__
