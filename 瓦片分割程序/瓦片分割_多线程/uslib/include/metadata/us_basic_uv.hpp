#ifndef __US_BASIC_UV_HPP__
#define __US_BASIC_UV_HPP__

#ifndef __US_RECT_HPP__
#include "util/math/us_rect.hpp"
#endif

#ifndef __US_METADATA_HPP__
#include "us_metadata.hpp"
#endif

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_basic_uv.
	 * @brief	基本UV类.
	 *			基本UV确定由一个四边形在一个矩形影像(纹理)中的最小取纹理范围及
	 *			取出范围内的纹理UV坐标。
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/9/07
	 *************************************************************************/
	class _US_METADATA_DLL us_basic_uv
	{
	public:
		us_basic_uv() :m_is_valid(false) {};

		/**********************************************************************//**
		 * @brief	通过在影像行列坐标系上的四个点和影像(纹理)的宽高计算UV值.
		 * 			四个角点的顺序不能乱，否则将影响UV值的计算。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/31
		 * @param	lt		左上角点在影像上的行列坐标.
		 * @param	rt		右上角点在影像上的行列坐标.
		 * @param	rb		右下角点在影像上的行列坐标.
		 * @param	lb		左下角点在影像上的行列坐标.
		 * @param	tex_h	纹理的宽度.
		 * @param	tex_w	纹理的高度
		 * @return	成功返回true。失败返回false，并设置为无效UV.
		 *************************************************************************/
		bool set_uv(const Point2i lt, const Point2i rt,
					const Point2i rb, const Point2i lb,
					const int tex_w, const int tex_h);

		/**********************************************************************//**
		 * @brief	通过在影像行列坐标系上的四个点和影像(纹理)的宽高计算UV值.
		 * 			四个角点的顺序不能乱，否则将影响UV值的计算。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/31
		 * @param	points	四个角点在影像上的行列坐标.
		 * @param	tex_w	纹理的宽度.
		 * @param	tex_h	纹理的高度
		 * @return	成功返回true。失败返回false，并设置为无效UV.
		 *************************************************************************/
		bool set_uv(const Point2i* points, const int tex_w, const int tex_h);

		/**********************************************************************//**
		 * @brief	获取有效性.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/29
		 * @return	true if valid, false if not.
		 *************************************************************************/
		inline bool is_valid(){ return m_is_valid; }
	public:
		/** 网格在影像中的占的像素范围(起始点+纹理高宽) */
		us_rect<int>	m_bound;
		/** 网格左下角点在上面像素范围中的U坐标 */
		double		m_lb_u;
		/** 网格左下角点在上面像素范围中的V坐标 */
		double		m_lb_v;
		/** 网格左上角点在上面像素范围中的U坐标 */
		double		m_lt_u;
		/** 网格左上角点在上面像素范围中的V坐标 */
		double		m_lt_v;
		/** 网格右上角点在上面像素范围中的U坐标 */
		double		m_rt_u;
		/** 网格右上角点在上面像素范围中的V坐标 */
		double		m_rt_v;
		/** 网格右下角点在上面像素范围中的U坐标 */
		double		m_rb_u;
		/** 网格右下角点在上面像素范围中的V坐标 */
		double		m_rb_v;

		/** UV是否有效标识 */
		bool m_is_valid;
	};

}

#endif //!__US_BASIC_UV_HPP__