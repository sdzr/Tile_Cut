/**********************************************************************//**
 * @file math\us_vec2.hpp
 *
 * Declares the vector 2 class.
 *************************************************************************/

#ifndef __US_VEC2_HPP__
#define __US_VEC2_HPP__


#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

#include <string>
#include <type_traits>

namespace unispace
{

	/***********************************************************************//**
	 * @class	us_vec2
	 * @brief	二维向量vector 2.也作为point2使用
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/9
	 **************************************************************************/
	template<typename T = float>
	class us_vec2{
		static_assert(std::is_same<T, int>::value ||
		std::is_same<T, float>::value ||
		std::is_same<T, double>::value,
		"template parameter must is int or float or double");
	public:
		// 构造函数
		us_vec2(T x = T(0), T y = T(0));
		// 拷贝构造
		us_vec2(const us_vec2& t);
		// 通过点p1和p1构造向量(p1-->p2)
		us_vec2(const us_vec2& p1, const us_vec2& p2);

	public:
		// 运算符重载
		us_vec2& operator = (const us_vec2& t);		//赋值运算
		bool operator == (const us_vec2& t)const;	//判等运算
		bool operator != (const us_vec2& t)const;	//判不等于

		us_vec2 operator + (const us_vec2& t)const;	//加
		us_vec2 operator - (const us_vec2& t)const;	//减
		us_vec2 operator - ()const;					//取负
		us_vec2 operator * (const double scale_factor);	//等比缩放


		us_vec2& operator += (const us_vec2& t);	//自加上
		us_vec2& operator -= (const us_vec2& t);	//自减去
		us_vec2& operator *= (const double scale_factor);//自缩放

	public:

		/*******************************************************************//**
		 * @fn		T us_vec2::get_x()const;
		 * @brief	获取 X 方向分量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @return	X 方向分量
		 **********************************************************************/
		T get_x()const;

		/******************************************************************//**
		 * @fn		T us_vec2::get_y()const;
		 * @brief	获取 Y 方向分量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @return	Y 方向分量.
		 *********************************************************************/
		T get_y()const;

		/*****************************************************************//**
		 * @fn		double us_vec2::get_length()const;
		 * @brief   获取向量长度.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @return	The length.
		 *********************************************************************/
		double get_length()const;

		/******************************************************************//**
		 * @fn		double us_vec2::get_length_squared()const;
		 * @brief	获取长度的平方值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @return	The length squared.
		 *********************************************************************/
		double get_length_squared()const;

		/**********************************************************************//**
		 * @brief	获取缩放后的向量值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/24
		 * @param	scale_factor The scale factor.
		 * @return	The scale.
		 *************************************************************************/

		us_vec2 scale(const double scale_factor)const;

		/**********************************************************************//**
		 * @brief	获取缩放后的向量值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/24
		 * @param	scale_factor_x The scale factor x coordinate.
		 * @param	scale_factor_y The scale factor y coordinate.
		 * @return	The scale.
		 *************************************************************************/

		us_vec2 scale(const double scale_factor_x, const double scale_factor_y)const;


		/******************************************************************//**
		 * @fn		bool us_vec2::is_zero()const;
		 * @brief	判断是否是零向量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @return	true if zero, false if not.
		 *********************************************************************/
		bool is_zero()const;

	public:

		/*****************************************************************//**
		 * @fn		void us_vec2::set_xy(T x, T y);
		 * @brief	设置 X,Y 的值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @param	x The T to process.
		 * @param	y The T to process.
		 *********************************************************************/
		void set_xy(T x, T y);

		/******************************************************************//**
		 * @fn		void us_vec2::set_x(T x);
		 * @brief	设置 X 方向分量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @param	x The T to process.
		 *********************************************************************/
		void set_x(T x);

		/******************************************************************//**
		 * @fn		void us_vec2::set_y(T y);
		 * @brief	设置 Y 方向分量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @param	y The T to process.
		 *********************************************************************/
		void set_y(T y);

		/*****************************************************************//**
		 * @brief	对向量自身进行缩放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @param	scale_factor The scale factor.
		 * @return	A reference to an us_vec2.
		 *********************************************************************/
		us_vec2& set_scale(const double scale_factor);

		/*****************************************************************//**
		 * @fn		us_vec2& us_vec2::set_scale(const T scale_factor_x,
		 * 			                            const T scale_factor_y);
		 * @brief	对向量自身进行缩放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @param	scale_factor_x The scale factor x coordinate.
		 * @param	scale_factor_y The scale factor y coordinate.
		 * @return	A reference to an us_vec2.
		 *********************************************************************/
		us_vec2& set_scale(const double scale_factor_x, const double scale_factor_y);


		/*****************************************************************//**
		 * @fn		us_vec2 us_vec2::get_normalize()const;
		 * @brief	获取向量的单位向量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @return	The normalize.
		 *********************************************************************/
		us_vec2 get_normalize()const;

		/******************************************************************//**
		 * @fn		void us_vec2::normalize();
		 * @brief	将量转换为标准化向量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 *********************************************************************/
		void normalize();

	public:

		/******************************************************************//**
		 * @fn		std::string  us_vec2::to_string()const;
		 * @brief	获取向量的字符串(形式：vec2<T>(x,y))
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @return	This object as a std::string.
		 *********************************************************************/
		std::string to_string()const;
	public:

		/******************************************************************//**
		 * @fn		static const us_vec2::us_vec2 zero();
		 * @brief   获取零向量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @return	A const us_vec2.
		 *********************************************************************/
		static const us_vec2 zero();

		/******************************************************************//**
		 * @fn		static const us_vec2::us_vec2 uint_x();
		 * @brief	获取 X 方向单位向量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @return	A const us_vec2.
		 *********************************************************************/
		static const us_vec2 uint_x();

		/******************************************************************//**
		 * @fn		static const us_vec2::us_vec2 uint_y();
		 * @brief   获取 Y 方向单位向量.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @return	A const us_vec2.
		 *********************************************************************/
		static const us_vec2 uint_y();

		/******************************************************************//**
		 * @fn		static double us_vec2::dot(const us_vec2 &v1, const us_vec2 &v2);
		 * @brief	计算v1与v2的点积并返回.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @param	v1 The first us_vec2.
		 * @param	v2 The second us_vec2.
		 * @return	两个向量的点积.
		 *********************************************************************/
		static double dot(const us_vec2 &v1, const us_vec2 &v2);

		/******************************************************************//**
		 * @fn		static double us_vec2::distance(const us_vec2& p1, const us_vec2& p2);
		 * @brief   获取点到点的距离.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/9
		 * @param	p1 第一个点.
		 * @param	p2 第二个点.
		 * @return	p1到p2的距离.
		 *********************************************************************/
		static double distance(const us_vec2& p1, const us_vec2& p2);

		/******************************************************************//**
		 * @fn		static double us_vec2::distance_squared(const us_vec2& p1,
		 * 													const us_vec2& p2);
		 * @brief   获取点到点的距离的平方值.
		 * @author  yimin.liu@unispace-x.com
		 * @date    2016/3/9
		 * @param	p1 第一个点.
		 * @param	p2 第二个点.
		 * @return	p1到p2的距离的平方.
		 *********************************************************************/
		static double distance_squared(const us_vec2& p1, const us_vec2& p2);
	public:
		/** x 分量(坐标). */
		T m_x;
		/** y 分量(坐标). */
		T m_y;
	};


	typedef us_vec2<int>	Point2i;
	typedef us_vec2<float>	Point2f;
	typedef us_vec2<double>	Point2lf;
	typedef us_vec2<int>	Vec2i;
	typedef us_vec2<float>	Vec2f;
	typedef us_vec2<double> Vec2lf;
}

//****************************************************************************//

#endif //!__US_VEC2_HPP__