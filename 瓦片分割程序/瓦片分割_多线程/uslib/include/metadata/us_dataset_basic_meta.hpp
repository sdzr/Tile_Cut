/**********************************************************************//**
 * @file us_dataset_basic_meta.hpp
 *
 * 定义 the us_dataset_basic_meta 类.
 *************************************************************************/
#ifndef __US_DATASET_BASIC_META_HPP__
#define __US_DATASET_BASIC_META_HPP__

#ifndef __US_GEO_RECT_HPP__
#include "util/math/us_geo_rect.hpp"
#endif

#ifndef __US_STRING_HPP__
#include "util/common/us_string.hpp"
#endif
#ifndef __US_UUID_HPP__
#include "util/uuid/us_uuid.hpp"
#endif

#ifndef __US_METADATA_HPP__
#include "us_metadata.hpp"
#endif

#include <vector>
#include <functional>


namespace unispace
{
	class us_uuid;

	/**********************************************************************//**
	 * @class	us_dataset_basic_meta
	 * @brief	数据集基本元数据.
	 * 			保存了数据集的入库时间，地理范围，显示层级等信息.<br>
	 *			内部包含了uuidset成员用于保存其包含的影像UUID。对于数据集中包含影像的增删，
	 *			此处不定义相关操作，应在其派生类中实现。
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/5/20
	 *************************************************************************/
	class _US_METADATA_DLL us_dataset_basic_meta
	{
	public:
		/**********************************************************************//**
		 * @brief	拷贝构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/27
		 * @param	other	数据集元信息对象
		 *************************************************************************/
		us_dataset_basic_meta(const us_dataset_basic_meta& other);
		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/6
		 * @param	name		数据集的名称.
		 * @param	create_uuid	是否生成新的uuid。默认不生成。
		 *************************************************************************/
		explicit us_dataset_basic_meta(const us_ustring& name = us_ustring(),bool create_uuid = false);
		~us_dataset_basic_meta(){};


		/**********************************************************************//**
		 * @brief	设置对象名.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	utf8_name	对象的名称，使用UTF-8编码的字符串.
		 *************************************************************************/
		void set_name(const us_ustring& utf8_name)
		{
			m_name = utf8_name;
		}

		/**********************************************************************//**
		 * @brief	获取对象名.
		 *
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @return	The name.
		 *************************************************************************/
		const us_ustring& get_name()const
		{
			return m_name;
		}

		/**********************************************************************//**
		 * @brief	设置对象UUID.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	uu	一个uuid对象.
		 *************************************************************************/
		bool set_uuid(const us_uuid& uu)
		{
			m_id = uu;
			return true;
		}

		/**********************************************************************//**
		 * @brief	设置对象UUID.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/18
		 * @param	uuidstr	UUID字符串.
		 * @return	true if it succeeds, false if it fails.
		 *************************************************************************/
		bool set_uuid(const char* uuidstr)
		{
			return us_uuid::uuid_from_string(uuidstr, &m_id);
		}

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
		us_ustring	m_name;			///< 数据集的名字
		us_ustring	m_desc;			///< 数据集的描述信息
		us_uuid		m_id;			///< 数据集的uuid
		us_uuid		m_pid;			///< 父数据集ID
		us_uuid		m_spr_uuid;		///< 数据集的空间参考uuid
		int64_t		m_ctime;		///< 入库时间
		int64_t		m_mtime;		///< 最近修改时间
		int64_t		m_dtime;		///< 数据时间
		int32_t		m_min_level;	///< 可显示最小网格层级
		int32_t		m_max_level;	///< 可显示最大网格层级
		int			m_rgb_band[3];	///< 用于取瓦片定为RGB三个波段的波段序号
		uint32_t	m_inrgb;		///< 无效像素值
		double		m_resolution_h;	///< 横向分辨率<b>一个像素的地理宽度(取影像集中的最高)</b>horizontal
		double		m_resolution_v;	///< 纵向分辨率<b>一个像素的地理高度</b>vertical
		us_geo_rect m_geo_rect;		///< 地理范围
		us_geo_rect m_latlng_rect;	///< 经纬度地理范围
		std::vector<us_uuid> m_uuidset;///< 包含的影像的uuid
		int32_t		m_has_hot;		///< 冷热标识
	};
}

#endif //!__US_DATASET_BASIC_META_HPP__



