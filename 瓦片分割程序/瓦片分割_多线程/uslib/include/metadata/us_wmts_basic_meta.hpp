#ifndef __US_WMTS_BASIC_META_HPP__
#define __US_WMTS_BASIC_META_HPP__

#ifndef __US_STRING_HPP__
#include "util/common/us_string.hpp"
#endif
#ifndef __US_UUID_HPP__
#include "util/uuid/us_uuid.hpp"
#endif // !__US_UUID_HPP__
#ifndef __US_GEO_RECT_HPP__
#include "util/math/us_geo_rect.hpp"
#endif

#ifndef __US_GRID_METER_HPP__
#include "grid_system/us_grid_meter.hpp"
#endif
#ifndef __US_GRID_DEGREE_HPP__
#include "grid_system/us_grid_degree.hpp"
#endif

#include <cmath>

namespace unispace
{
	struct us_wmts_basic_meta {
		us_ustring	m_layer_name;	///< wmts的layer名
		us_uuid		m_uuid;			///< 唯一ID
		us_uuid		m_dataset_id;	///< 对应dataset唯一id
		us_uuid		m_dataset_spr_id;	///< 对应数据集的空间参考,弃用
		us_uuid		m_spr_uuid;		///< 空间参考的uuid
		us_geo_rect m_geo_rect;		///< 发布的地理范围
		us_geo_rect	m_dataset_rect;	///< 数据集的地理范围,弃用
		int			m_max_level;	///< 最大级别
		int			m_min_level;	///< 最小级别
		int			m_tile_pixel_h;	///< 瓦片横向像素数
		int			m_tile_pixel_v;	///< 瓦片纵向像素数
		int			m_tile_type;    ///< 瓦片规则：0：内部度网格，1：内部米网格；2：谷歌经纬度；3：谷歌Web墨卡托；
		int			m_rgb_band[3];	///< 用于取瓦片定为RGB三个波段的波段序号
		
		us_wmts_basic_meta()
#if defined(_MSC_VER) && _MSC_VER >= 1900
			:m_rgb_band { 3, 2, 1 }
		{
#else
		{
			m_rgb_band[0] = 3; m_rgb_band[1] = 2; m_rgb_band[2] = 1;
#endif
		}
	};
}
#if 0
	public:
		/**********************************************************************//**
		 * @brief	获取某级别的wmts图层范围(左上角点和宽高).
		 *			返回的rect的基准点为左上角点，正方向为向右向下.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/13
		 * @param	level	网格级别.
		 * @return	该级别下的最大网格地理范围.
		 *************************************************************************/
		template<typename _GRID = us_grid_meter>
		us_rect<double> get_rect_base_top_left(int level)const;

		/**********************************************************************//**
		 * @brief	获取网格ID.
		 *			获取该级别网格下相对于左上角点偏移的格子数(向右向下为正).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/13
		 * @param	level	网格级别.
		 * @param	row		横向偏移.
		 * @param	col		纵向偏移.
		 * @return	该位置处的网格ID.
		 *************************************************************************/
		template<typename _GRID = us_grid_meter>
		us_grid_id get_grid_id(int level,int row,int col)const;

		/**********************************************************************//**
		 * @brief	判断行列在该级别是否有效.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/13
		 * @param	level	网格级别.
		 * @param	row		横向偏移.
		 * @param	col		纵向偏移.
		 * @return	有效返回true.
		 *************************************************************************/
		template<typename _GRID = us_grid_meter>
		bool is_vaild_rank(int level,int row,int col)const;
		
		/**********************************************************************//**
		 * @brief	获取比例尺分母.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/13
		 * @param	level	网格级别.
		 * @return	比例因子分母.
		 *************************************************************************/
		template<typename _GRID = us_grid_meter>
		double get_scale_denomination(int level)const;

		/**********************************************************************//**
		 * @brief	获取瓦片行列数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/13
		 * @param	level	网格级别.
		 * @return	瓦片行列数.
		 *************************************************************************/
		template<typename _GRID = us_grid_meter>
		us_size<int> get_tile_ranks(int level)const;

		/**********************************************************************//**
		 * @brief	获取TileMatrixSet瓦片矩阵集xml描述.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/15
		 * @return	xml字符串.
		 *************************************************************************/
		template<typename _GRID = us_grid_meter>
		us_ustring get_tile_matrix_set_xml()const;
	};
}

#ifndef __US_WMTS_BASIC_META_HPP_INL__
#include "us_wmts_basic_meta.hpp.inl"
#endif

#endif


#endif //!__US_WMTS_BASIC_META_HPP__