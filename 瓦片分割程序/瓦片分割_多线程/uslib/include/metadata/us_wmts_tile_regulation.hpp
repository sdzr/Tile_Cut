#ifndef __US_WMTS_TILE_REGULATION_HPP__
#define __US_WMTS_TILE_REGULATION_HPP__

#ifndef __US_GEO_RECT_HPP__
#include "util/math/us_geo_rect.hpp"
#endif
#ifndef __US_STRING_HPP__
#include "util/common/us_string.hpp"
#endif

#ifndef __US_METADATA_HPP__
#include "us_metadata.hpp"
#endif

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_wmts_tile_regulation
	 * @brief	WMTS瓦片规则类.
	 * 			瓦片规则用于计算瓦片数量范围，生成tile matrix描述信息等.
	 * @author	xuefeng.dai@unispace-x.com
	 * @modify	yimin.liu@unispace-x.com
	 * @date	2017/3/29
	 *************************************************************************/
	class _US_METADATA_DLL us_wmts_tile_regulation {
	public:
		enum WMTS_TYPE {
			UNISPACE_DEGREE	= 0,  ///< 内部度网格
			UNISPACE_METER	= 1,  ///< 内部米网格
			GOOGLE_LATLNG	= 2,  ///< 经纬度，顶级为东西半球各一个网格
			WEB_MERCATOR	= 3,  ///< Web墨卡托，顶级一个方网格
		};

		WMTS_TYPE			m_type;
		double				m_scale_denom;	// 顶级Scale参数；
		us_geo_rect			m_rect_base;	// 总范围
		us_size<int>		m_rank_base;	// 顶级块数

	public:
		/**********************************************************************//**
		* @brief	设置瓦片规则.
		* @author	xuefeng.dai@unispace-x.com
		* @modify	yimin.liu@unispace-x.com
		* @date		2017/3/29
		* @param	type	瓦片规则.
		*************************************************************************/
		inline void set_tile_type(WMTS_TYPE type);

		/**********************************************************************//**
		* @brief	给定Rect获取指定level下的行列范围.
		* @author	xuefeng.dai@unispace-x.com
		* @date		2017/3/29
		* @param	level	网格级别.
		* @param	row		横向偏移.
		* @param	col		纵向偏移.
		* @return	返回该级别下行列范围。rect的x为列索引，y为行索引
		*************************************************************************/
		inline us_rect<int> get_rank_range(int level, us_geo_rect in_rect);
		

		/**********************************************************************//**
		* @brief	判断行列在该级别是否有效.
		* @author	xuefeng.dai@unispace-x.com
		* @date		2017/3/29
		* @param	level	网格级别.
		* @param	row		横向偏移.
		* @param	col		纵向偏移.
		* @return	有效返回true.
		*************************************************************************/
		inline bool is_vaild_rank(int level, int row, int col, us_geo_rect in_rect);
		
		/**********************************************************************//**
		* @brief	获取TileMatrixSet瓦片矩阵集xml描述.
		* @author	xuefeng.dai@unispace-x.com
		* @modify	yimin.liu@unispace-x.com
		* @date		2017/3/29
		* @param	tms_name		tms图层名称.
		* @param	level_min		最小网格级别.
		* @param	level_max		最大网格级别.
		* @param	tile_pixel_h	瓦片横向像素数.
		* @param	tile_pixel_v	瓦片纵向像素数.
		* @return	xml字符串.
		*************************************************************************/
		inline us_ustring get_tile_matrix_set_xml(us_ustring tms_name,
			int level_min, int level_max, int tile_pixel_h, int tile_pixel_v);
		
	};

}
#endif //!__US_WMTS_TILE_REGULATION_HPP__