/**********************************************************************//**
 * @file us_image_basic_meta.hpp
 *
 * 定义us_image_basic_meta类.
 *************************************************************************/

#ifndef __US_IMAGE_BASIC_META_HPP__
#define __US_IMAGE_BASIC_META_HPP__

#ifndef __US_GEO_RECT_HPP__
#include <util/math/us_geo_rect.hpp>
#endif

#ifndef __US_GRID_TYPE_HPP__
#include <grid_system/us_grid_type.hpp>
#endif

#ifndef __US_STRING_HPP__
#include <util/common/us_string.hpp>
#endif // !__US_STRING_HPP__


#ifndef __US_UUID_HPP__
#include <util/uuid/us_uuid.hpp>
#endif


#ifndef __US_METADATA_HPP__
#include "us_metadata.hpp"
#endif

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_image_basic_meta
	 * @brief	影像基本元数据.
	 * 			保存了影像的一些基本属性，以及需要存入数据库中的字段值.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/18
	 *************************************************************************/
	class _US_METADATA_DLL us_image_basic_meta
	{
	public:

		/**********************************************************************//**
		 * Default constructor.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/18
		 *************************************************************************/
		us_image_basic_meta();

		/**********************************************************************//**
		 * Equality operator.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	t The us_image_basic_meta to process.
		 * @return	true if the parameters are considered equivalent.
		 *************************************************************************/

		bool operator== (const us_image_basic_meta& t)const;

		/**********************************************************************//**
		 * @brief	判断是否已经生成了某网格类型对应的UV信息.
		 *			生成了哪些网格类型对应的UV信息的信息存储在m_uv_set中。
		 *			m_uv_set中的第 gridtype 位为1，则说明生成了该网格类型的UV信息。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/22
		 * @param	gridtype	网格类型.
		 * @return	具有该网格类型对应的UV信息返回 true ,否则返回 false.
		 *************************************************************************/

		bool has_uv_by_gridtype(const us_grid_type gridtype)const;

		/**********************************************************************//**
		 * @brief	设置对象UUID.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	uu	一个uuid对象.
		 *************************************************************************/
		bool set_uuid(const us_uuid& uu);

		/**********************************************************************//**
		 * @brief	设置对象UUID.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	uuidstr	UUID字符串.
		 * @return	true if it succeeds, false if it fails.
		 *************************************************************************/
		bool set_uuid(const char* uuidstr);

		/**********************************************************************//**
		 * @brief	获取对象UUID.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @return	The uuid.
		 *************************************************************************/
		const us_uuid& get_uuid()const
		{
			return m_id;
		}
	public:
		us_uuid		m_id;	            ///< 影像meta的uuid
		us_uuid		m_spr_uuid;         ///< 空间参考文件uuid
		us_ustring	m_image_url;	    ///< 影像数据的路径【FS = path|DB = only key】
										// URL统一资源定位器(Uniform Resource Locator)；统一资源定位符
		time_t		m_ctime;            ///< 入库时间(creat time)<b>UTC时间秒数</b>int64类型
		time_t		m_dtime;            ///< 数据时间(access time)
		time_t		m_mtime;	        ///< 修改时间(modify time)
		us_geo_rect	m_geo_rect;	        ///< 地理范围，没有地理范围时为无效值
		us_geo_rect m_latlng_rect;	    ///< 经纬度地理范围
		double		m_geo_transfrom[6];	///< 坐标转换仿射变换参数
		double		m_resolution_h;	    ///< 横向分辨率<b>一个像素的地理宽度</b>horizontal
		double		m_resolution_v;	    ///< 纵向分辨率<b>一个像素的地理高度</b>vertical
		int32_t		m_pixel_h;	        ///< 影像的横向像素数(不应该为负数)
		int32_t		m_pixel_v;	        ///< 影像的纵向像素数
		int32_t		m_band_count;	    ///< 影像波段数
		uint32_t	m_type;				///< 影像数据类别
		uint32_t	m_uv_set;	        ///< 已经生成的UV表集.弃用
		bool		m_has_pyramid;	    ///< 是否生成了金字塔. 弃用

	};
}

#endif //!__US_IMAGE_BASIC_META_HPP__