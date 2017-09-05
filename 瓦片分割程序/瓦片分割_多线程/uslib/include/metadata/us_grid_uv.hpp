/**********************************************************************//**
 * @file us_grid_uv.hpp
 *
 * 定义 the us_grid_uv 类.
 *************************************************************************/

#ifndef __US_GRID_UV_HPP__
#define __US_GRID_UV_HPP__

#ifndef __US_RECT_HPP__
#include "util/math/us_rect.hpp"
#endif

#ifndef __US_GRID_ID_HPP__
#include "grid_system/us_grid_base.hpp"
#endif

#ifndef __US_UUID_HPP__
#include "util/uuid/us_uuid.hpp"
#endif

#ifndef __US_BASIC_UV_HPP__
#include "us_basic_uv.hpp"
#endif

#ifndef __US_METADATA_HPP__
#include "us_metadata.hpp"
#endif

namespace unispace
{
	class us_image_basic_meta;
	class us_spatial_reference;

	/**********************************************************************//**
	 * @class	us_grid_uv.
	 * @brief	网格UV类.
	 *			网格UV确定一个网格和一个影像之间的取纹理关系。
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/5/20
	 *************************************************************************/
	 
	class _US_METADATA_DLL us_grid_uv
		:public us_basic_uv
	{
	public:
		/**********************************************************************//**
		 * @brief	构造函数，构造一个无效UV记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/28
		 *************************************************************************/
		us_grid_uv():m_gid(us_grid_type::GRID_TYPE_UNKNOWN,0,0){ };
		
		/**********************************************************************//**
		 * @brief	构造函数，通过网格和影像meta来构建一个UV记录.
		 *			如果网格和影像在地理范围上不重叠或影像坐标上不重叠，那么不计算UV。设置UV记录无效。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/28
		 *
		 * @param	grid	网格.
		 * @param	meta	影像meta记录.
		 *************************************************************************/
		us_grid_uv(const us_grid_base& grid, const us_image_basic_meta& meta);

		/**********************************************************************//**
		 * @brief	构造函数，通过网格和影像meta来构建一个UV记录.
		 *			如果网格和影像在地理范围上不重叠或影像坐标上不重叠，那么不计算UV。设置UV记录无效。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/31
		 * @param	grid	网格.
		 * @param	meta		影像meta记录.
		 * @param	spr		空间参考(当前仅支持投影坐标参考).
		 *************************************************************************/
		us_grid_uv(const us_grid_base& grid, const us_image_basic_meta& meta,
					const us_spatial_reference& spr);

		/**********************************************************************//**
		 * @brief	构造函数，通过网格和影像meta来构建一个UV记录.
		 *			如果网格和影像在地理范围上不重叠或影像坐标上不重叠，那么不计算UV。设置UV记录无效。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/31
		 * @param	grid		网格.
		 * @param	img			影像meta记录.
		 * @param	grid_spr	网格所在空间参考.
		 * @param	img_spr		影像所在空间参考.
		 *************************************************************************/
		us_grid_uv(const us_grid_base& grid, const us_spatial_reference& grid_spr,
				   const us_image_basic_meta& img, const us_spatial_reference& img_spr);

		~us_grid_uv(){};

		/**********************************************************************//**
		 * @brief	通过网格和影像meta来设置UV记录的值.
		 * 			本方法内默认影像和网格的地理坐标体系是同一个。<br>
		 *			如果网格和影像在地理范围上不重叠或影像坐标上不重叠，那么不计算UV。设置UV记录无效。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/31
		 * @param	grid	网格.
		 * @param	img		影像meta记录.
		 * @return	成功返回true。失败返回false，并设置为无效UV.
		 *************************************************************************/
		bool set_uv(const us_grid_base& grid, const us_image_basic_meta& img);
		/**********************************************************************//**
		 * @brief	通过网格和影像meta来设置UV记录的值.
		 * 			如果spr是投影坐标系统，那么将根据grid的网格类型来判断是其是投影坐标还是地理坐标。
		 * 			<br>如果grid是米网格，则认为影像地理坐标是经纬度，UV由网格地理坐标投影逆算后计
		 *			算得到。<br> 如果grid是经纬网格，则认为影像地理坐标是投影坐标，UV由投影正算后
		 *			计算得到。<br>
		 *			如果网格和影像在地理范围上不重叠或影像坐标上不重叠，那么不计算UV。设置UV记录无效。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/31
		 * @param	grid	网格.
		 * @param	img		影像meta记录.
		 * @param	spr		空间参考(当前仅支持投影坐标参考).
		 * @return	成功返回true。失败返回false，并设置为无效UV.
		 *************************************************************************/
		bool set_uv(const us_grid_base& grid, const us_image_basic_meta& img,
					const us_spatial_reference& spr);
		/**********************************************************************//**
		 * @brief	通过网格和影像meta来设置UV记录的值.
		 * 			本方法内先将网格的地理坐标换算到影像所在的地理坐标系上，然后计算UV。<br>
		 *			如果网格和影像在地理范围上不重叠或影像坐标上不重叠，那么不计算UV。设置UV记录无效。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/31
		 * @param	grid		网格.
		 * @param	img			影像meta记录.
		 * @param	grid_spr	网格所在空间参考.
		 * @param	img_spr		影像所在空间参考.
		 * @return	成功返回true。失败返回false，并设置为无效UV.
		 *************************************************************************/
		bool set_uv(const us_grid_base& grid, const us_spatial_reference& grid_spr,
					const us_image_basic_meta& img, const us_spatial_reference& img_spr);
		/**********************************************************************//**
		 * @brief	通过在影像行列坐标系上的四个点和影像的meta计算UV值.
		 * 			四个角点的顺序不能乱，否则将影响UV值的计算。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/31
		 * @param	lt		左上角点在影像上的行列坐标.
		 * @param	rt		右上角点在影像上的行列坐标.
		 * @param	rb		右下角点在影像上的行列坐标.
		 * @param	lb		左下角点在影像上的行列坐标.
		 * @param	img		影像meta记录.
		 * @return	成功返回true。失败返回false，并设置为无效UV.
		 *************************************************************************/
		bool set_uv(const Point2i lt, const Point2i rt,
					const Point2i rb, const Point2i lb,
					const us_image_basic_meta& img);
		/**********************************************************************//**
		 * @brief	通过在影像行列坐标系上的四个点和影像的meta计算UV值.
		 * 			四个角点的顺序不能乱，否则将影响UV值的计算。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/31
		 * @param	points	四个角点在影像上的行列坐标.
		 * @param	img		影像meta记录.
		 * @return	成功返回true。失败返回false，并设置为无效UV.
		 *************************************************************************/
		bool set_uv(const Point2i* points,const us_image_basic_meta& img);
	public:
		us_uuid		m_img_uuid;		// 影像的uuid
		us_grid_id	m_gid;			// 网格的gid
	};

}
#endif //!__US_GRID_UV_HPP__