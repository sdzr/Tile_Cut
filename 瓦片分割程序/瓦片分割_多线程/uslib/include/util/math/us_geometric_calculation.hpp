#ifndef __US_POLYGON_CALCULATION_HPP__
#define __US_POLYGON_CALCULATION_HPP__

#include "us_vec2.hpp"
#include <vector>

namespace unispace
{
	/*******************************************************************//**
	* @brief	点到直线距离计算.
	* @author	yimin.liu@unispace-x.com
	* @date		2017/3/10
	* @param	point	点.
	* @param	lp1		确定直线的第一个点.
	* @param	lp2		确定直线的第二个点.
	* @return	线段跨立返回true.
	**********************************************************************/
	template<typename T>
	double us_point_to_line_distance(const us_vec2<T> point
		,const us_vec2<T> lp1, const us_vec2<T> lp2);

	/*******************************************************************//**
	* @brief	线段是否跨立测试.
	* @author	yimin.liu@unispace-x.com
	* @date		2017/3/10
	* @param	p1		第一条线段起点.
	* @param	p2		第一条线段终点.
	* @param	q1		第二条线段起点.
	* @param	q2		第二条线段终点.
	* @return	线段跨立返回true.
	**********************************************************************/
	template<typename T>
	bool us_line_cross_test(const us_vec2<T> p1,const us_vec2<T> p2,
							const us_vec2<T> q1,const us_vec2<T> q2);


	/*******************************************************************//**
	* @brief	线段是否相交测试.
	* @author	yimin.liu@unispace-x.com
	* @date		2017/3/10
	* @param	p1		第一条线段起点.
	* @param	p2		第一条线段终点.
	* @param	q1		第二条线段起点.
	* @param	q2		第二条线段终点.
	* @return	线段有相交返回true.
	**********************************************************************/
	template<typename T>
	bool us_line_intersect_test(const us_vec2<T> p1,const us_vec2<T> p2,
								const us_vec2<T> q1,const us_vec2<T> q2);



	/*******************************************************************//**
	* @brief	多边形自相交测试.
	* @author	yimin.liu@unispace-x.com
	* @date		2017/3/10
	* @param	poly	多边形点数组.
	* @return	多边形有自相交返回true.
	**********************************************************************/
	template<typename T>
	bool us_polygon_self_intersect_test(const std::vector<us_vec2<T> >& poly);

	/*******************************************************************//**
	* @brief	多边形自相交测试.
	* @author	yimin.liu@unispace-x.com
	* @date		2017/3/10
	* @param	poly_pt_arr	多边形点数组.
	* @param	poly_pt_num	多边形点数.
	* @return	多边形有自相交返回true.
	**********************************************************************/
	template<typename T>
	bool us_polygon_self_intersect_test(
		const us_vec2<T>* const poly_pt_arr,int poly_pt_num);

	/*******************************************************************//**
	* @brief	多边形包含点测试.
	* @author	yimin.liu@unispace-x.com
	* @date		2017/3/13
	* @param	point	测试点.
	* @param	poly	多边形点数组.
	* @return	返回	0 表示点在多边形外部,1 表示点在多边形内部,-1表示点在多边形边线上.
	**********************************************************************/
	template<typename T>
	int us_point_in_polygon_test(const us_vec2<T> point,
		const std::vector<us_vec2<T> >& poly);
	/*******************************************************************//**
	* @brief	多边形包含点测试.
	* @author	yimin.liu@unispace-x.com
	* @date		2017/3/13
	* @param	point	测试点.
	* @param	poly_pt_arr	多边形点数组.
	* @param	poly_pt_num	多边形点数.
	* @return	返回	0 表示点在多边形外部,1 表示点在多边形内部,-1表示点在多边形边线上.
	**********************************************************************/
	template<typename T>
	int us_point_in_polygon_test(const us_vec2<T> point,
		const us_vec2<T>* poly_pt_arr, int poly_pt_num);

	/*******************************************************************//**
	* @brief	多边形相交测试.
	* @author	yimin.liu@unispace-x.com
	* @date		2017/3/13
	* @param	poly1	多边形1点数组.
	* @param	poly2	多边形2点数组.
	* @return	两个多边形有相交返回true.
	**********************************************************************/
	template<typename T>
	bool us_polygon_intersect_test(
		const std::vector<us_vec2<T> >& poly1,
		const std::vector<us_vec2<T> >& poly2);

	/*******************************************************************//**
	* @brief	多边形相交测试.
	* @author	yimin.liu@unispace-x.com
	* @date		2017/3/13
	* @param	poly_pt_arr1	多边形1点数组.
	* @param	poly_pt_num1	多边形1点数.
	* @param	poly_pt_arr2	多边形2点数组.
	* @param	poly_pt_num2	多边形2点数.
	* @return	两个多边形有相交返回true.
	**********************************************************************/
	template<typename T>
	bool us_polygon_intersect_test(
		const us_vec2<T>* poly_pt_arr1, int poly_pt_num1,
		const us_vec2<T>* poly_pt_arr2, int poly_pt_num2);
	
	/*******************************************************************//**
	* @brief	多边形面积计算.
	* @author	yimin.liu@unispace-x.com
	* @date		2017/3/13
	* @param	poly	多边形点数组.
	* @return	返回多边形的面积.
	**********************************************************************/
	template<typename T>
	double us_polygon_area(const std::vector<us_vec2<T> >& poly);

	/*******************************************************************//**
	* @brief	多边形面积计算.
	* @author	yimin.liu@unispace-x.com
	* @date		2017/3/13
	* @param	poly_pt_arr	多边形点数组.
	* @param	poly_pt_num	多边形点数.
	* @return	返回多边形的面积.
	**********************************************************************/
	template<typename T>
	double us_polygon_area(const us_vec2<T>* poly_pt_arr, int poly_pt_num);
}

#endif //!__US_POLYGON_CALCULATION_HPP__
