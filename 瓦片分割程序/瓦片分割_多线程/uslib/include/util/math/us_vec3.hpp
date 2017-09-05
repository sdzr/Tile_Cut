/**********************************************************************//**
 * @file math\us_vec3.hpp
 *
 * Declares the vector 3 class.
 *************************************************************************/

#ifndef __US_VEC3_HPP__
#define __US_VEC3_HPP__


#include <string>
#include <type_traits>


namespace unispace
{

	/**********************************************************************//**
	 * @class	us_vec3
	 * @brief	三维向量
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/14
	 *************************************************************************/
	template<typename T = float>
	class us_vec3{
		static_assert(std::is_same<T, int>::value ||
		std::is_same<T, float>::value ||
		std::is_same<T, double>::value,
		"template parameter must is int or float or double");
	public:

		/**********************************************************************//**
		 * @brief	构造函数.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param x The T to process.
		 * @param y The T to process.
		 * @param z The T to process.
		 *************************************************************************/

		us_vec3(T x = T(0), T y = T(0), T z = T(0));

		/**********************************************************************//**
		 * @brief	拷贝构造.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param t The us_vec3 to process.
		 *************************************************************************/

		us_vec3(const us_vec3& t);

		/**********************************************************************//**
		 * @brief	通过点p1和p1构造向量(p1-->p2)
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param p1 The first us_vec3.
		 * @param p2 The second us_vec3.
		 *************************************************************************/

		us_vec3(const us_vec3& p1, const us_vec3& p2);

	public:
		// 运算符重载
		us_vec3& operator = (const us_vec3& t);		//赋值运算
		bool operator == (const us_vec3& t)const;	//判等运算
		bool operator != (const us_vec3& t)const;	//判不等于

		us_vec3 operator + (const us_vec3& t)const;	//加
		us_vec3 operator - (const us_vec3& t)const;	//减
		us_vec3 operator - ()const;					//取负
		us_vec3 operator * (const double scale_factor);	//等比缩放


		us_vec3& operator += (const us_vec3& t);	//自加上
		us_vec3& operator -= (const us_vec3& t);	//自减去
		us_vec3& operator *= (const double scale_factor);//自缩放

	public:

		/**********************************************************************//**
		 * @brief	获取 X 方向分量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return The x coordinate.
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
		 * @brief	获取向量长度.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 * @return The length.
		 *************************************************************************/
		double get_length()const;

		/**********************************************************************//**
		 * @brief	获取长度的平方值.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 * @return The length squared.
		 *************************************************************************/
		double get_length_squared()const;


		/**********************************************************************//**
		 * @brief	获取对向量进行等比缩放的值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	scale_factor The scale factor.
		 * @return	A us_vec3.
		 *************************************************************************/
		us_vec3 scale(const double scale_factor)const;

		/**********************************************************************//**
		 * @brief	获取缩放后的向量值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	scale_factor_x The scale factor x coordinate.
		 * @param	scale_factor_y The scale factor y coordinate.
		 * @param	scale_factor_z The scale factor z coordinate.
		 * @return	A us_vec3.
		 *************************************************************************/
		us_vec3 scale(const double scale_factor_x,
					  const double scale_factor_y,
					  const double scale_factor_z)const;



		/**********************************************************************//**
		 * @brief	判断是否是零向量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/24
		 * @return	true if zero, false if not.
		 *************************************************************************/
		bool is_zero()const;

	public:

		/**********************************************************************//**
		 * @brief	设置 X,Y,Z 的值.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param x The T to process.
		 * @param y The T to process.
		 * @param z The T to process.
		 *************************************************************************/

		void set_xyz(T x, T y, T z);

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
		 * @brief	对向量自身进行等比缩放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	scale_factor The scale factor.
		 * @return	A reference to an us_vec3.
		 *************************************************************************/
		us_vec3& set_scale(const double scale_factor);

		/**********************************************************************//**
		 * @brief	缩放向量自身.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	scale_factor_x The scale factor x coordinate.
		 * @param	scale_factor_y The scale factor y coordinate.
		 * @param	scale_factor_z The scale factor z coordinate.
		 * @return	A reference to an us_vec3.
		 *************************************************************************/
		us_vec3& set_scale(const double scale_factor_x,
						   const double scale_factor_y,
						   const double scale_factor_z);


		/**********************************************************************//**
		 * @brief	获取向量的单位向量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @return The normalize.
		 *************************************************************************/

		us_vec3 get_normalize()const;

		/**********************************************************************//**
		 * @brief	将量转换为标准化向量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
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
		 * @return A const us_vec3.
		 *************************************************************************/

		static const us_vec3 zero();

		/**********************************************************************//**
		 * @brief	获取 X 方向单位向量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @return A const us_vec3.
		 *************************************************************************/

		static const us_vec3 uint_x();

		/**********************************************************************//**
		 * @brief	获取 Y 方向单位向量.
		 *
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @return A const us_vec3.
		 *************************************************************************/

		static const us_vec3 uint_y();

		/**********************************************************************//**
		 * @brief	获取 Z 方向单位向量.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	A const us_vec3.
		 *************************************************************************/
		static const us_vec3 uint_z();

		/**********************************************************************//**
		 * @brief	计算v1与v2的点积并返回.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	v1 The first us_vec3.
		 * @param	v2 The second us_vec3.
		 * @return	A double.
		 *************************************************************************/

		static double dot(const us_vec3 &v1, const us_vec3 &v2);

		/**********************************************************************//**
		 * @brief	计算v1与v2的叉乘并返回。.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	v1 The first us_vec3.
		 * @param	v2 The second us_vec3.
		 * @return	An us_vec3.
		 *************************************************************************/

		static us_vec3 cross(const us_vec3 &v1, const us_vec3 &v2);

		/**********************************************************************//**
		 * @brief	计算点p1与p2的距离值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	p1 The first us_vec3.
		 * @param	p2 The second us_vec3.
		 * @return	p1和p2的距离值.
		 *************************************************************************/

		static double distance(const us_vec3& p1, const us_vec3& p2);

		/**********************************************************************//**
		 * @brief	计算点p1与p2的距离的平方值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	p1 The first us_vec3.
		 * @param	p2 The second us_vec3.
		 * @return	两个点之间的距离长度的平方值.
		 *************************************************************************/

		static double distance_squared(const us_vec3& p1, const us_vec3& p2);
	public:
		/** x 分量(坐标). */
		T m_x;
		/** y 分量(坐标). */
		T m_y;
		/** z 分量(坐标). */
		T m_z;
	};


	typedef us_vec3<int>	Point3i;
	typedef us_vec3<float>	Point3f;
	typedef us_vec3<double>	Point3lf;
	typedef us_vec3<int>	Vec3i;
	typedef us_vec3<float>	Vec3f;
	typedef us_vec3<double> Vec3lf;
}

//****************************************************************************//

#endif //!__US_VEC3_HPP__
