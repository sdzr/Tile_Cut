/**********************************************************************//**
 * @file math\us_matrix4.hpp
 *
 * Declares the matrix 4 class.
 *************************************************************************/

#ifndef __US_MATRIX4_HPP__
#define __US_MATRIX4_HPP__


#ifndef __US_VEC3_HPP__
#include "us_vec3.hpp"
#endif

#ifndef __US_VEC4_HPP__
#include "us_vec4.hpp"
#endif


namespace unispace
{

	/**********************************************************************//**
	 * @class	us_matrix4
	 * @brief	4x4的矩阵(此处应该改名为us_mat4x4比较准确)
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/14
	 *************************************************************************/
	template<typename T = double>
	class us_matrix4
	{
	protected:
		union{
			struct{
				T	m11, m12, m13, m14;
				T	m21, m22, m23, m24;
				T	m31, m32, m33, m34;
				T	m41, m42, m43, m44;
			};
			T m[16];
		};
	public:
		// 构造函数
		us_matrix4();
		// 拷贝构造函数
		us_matrix4(const us_matrix4& mat);
		// 十六参数构造
		us_matrix4(T t11, T t12, T t13, T t14,
				   T t21, T t22, T t23, T t24,
				   T t31, T t32, T t33, T t34,
				   T t41, T t42, T t43, T t44);
		
		// 重载赋值运算符
		us_matrix4& operator = (const us_matrix4& mat);
		// 重载 == 运算符
		bool operator == (const us_matrix4& mat)const;
		// 重载 != 运算符
		bool operator != (const us_matrix4& mat)const;
		// 重载 + 运算符(返回矩阵相加结果)
		us_matrix4 operator + (const us_matrix4& mat)const;
		// 重载 - 运算符(返回矩阵相减结果)
		us_matrix4 operator - (const us_matrix4& mat)const;
		// 重载 * 运算符(返回矩阵相乘结果)
		us_matrix4 operator * (const us_matrix4& mat)const;
		// 重载 * 运算符(返回矩阵乘以向量的结果)
		us_vec4<T> operator *(const us_vec4<T> vec)const;

		// 重载 * 运算符(返回矩阵缩放结果)
		us_matrix4 operator * (double scale_factor)const;
		// 重载 / 运算符(返回矩阵缩放结果)
		// us_matrix4 operator / (T scale_factor)const;
		// 重载 - 运算符(返回取负结果)
		us_matrix4 operator - ()const;
		
		// 重载 += 运算符(对自身进行矩阵加上操作)
		us_matrix4& operator += (const us_matrix4& mat);
		// 重载 -= 运算符(对自身进行矩阵减去操作)
		us_matrix4& operator -= (const us_matrix4& mat);
		// 重载 *= 运算符(对自身进行矩阵乘上操作)
		us_matrix4& operator *= (const us_matrix4& mat);

		// 重载 *= 运算符(对自身进行矩阵缩放操作)
		us_matrix4& operator *= (double scale_factor);
		// 重载 /= 运算符(对自身进行矩阵缩放操作)
		// us_matrix4& operator /= (T scale_factor);

		// 友元 重载全局 * 运算符(矩阵缩放结果)
		friend us_matrix4<T> operator * (double scale_factor, const us_matrix4<T>& mat);
		// 友元 重载全局 * 运算符(向量乘以矩阵)
		friend us_vec4<T> operator * (const us_vec4<T>& vec,const us_matrix4<T>& mat);
		// 友元 重载全局 * 运算符(平移点坐标结果vec3当作[x,y,z,1])
		friend us_vec3<T> operator * (const us_vec3<T>& vec, const us_matrix4<T>& mat);

	public:
		// 获取转置矩阵
		us_matrix4<T> get_transpose()const;
		// 获取逆矩阵
		us_matrix4<T> get_inverse()const;
		// 获取共轭矩阵(伴随矩阵)
		us_matrix4<T> get_adjoint()const;
		// 获取行列式值
		T get_determinant()const;

		// 获取字符串形式
		std::string to_string()const;


	public:
		// 设置为零矩阵
		us_matrix4& set_zero();
		// 设置为单位矩阵
		us_matrix4& set_identity();

	public:
		// 平移点坐标
		static us_vec3<T> translation_coordinate(const us_vec3<T>& vec, const us_matrix4& mat);
		// 平移法线
		static us_vec3<T> translation_normal(const us_vec3<T>& vec, const us_matrix4& mat);
		// 旋转法线
		static us_vec3<T> rotate_normal(const us_vec3<T>& vec, const us_matrix4& mat);

		// 获取一个零矩阵
		static us_matrix4<T> zero();
		// 获取一个单位矩阵
		static us_matrix4<T> identity();
	};
}

#endif //!__US_MATRIX4_HPP__
