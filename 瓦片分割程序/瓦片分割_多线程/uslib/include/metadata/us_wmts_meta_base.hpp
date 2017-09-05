#ifndef __US_WMTS_META_BASE_HPP__
#define __US_WMTS_META_BASE_HPP__

#ifndef __US_WMTS_BASIC_META_HPP__
#include "us_wmts_basic_meta.hpp"
#endif
#ifndef __US_WMTS_TILE_REGULATION_HPP__
#include "us_wmts_tile_regulation.hpp"
#endif

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_wmts_meta_base
	 * @brief	WMTS元信息类.
	 * @author	xuefeng.dai@unispace-x.com
	 * @date	2017/3/29
	 *************************************************************************/
	class us_wmts_meta_base {
	public:
		us_wmts_basic_meta		m_meta;	// 基本meta信息
		us_wmts_tile_regulation	m_tile_regul;	// 瓦片规则
	public:
		/**********************************************************************//**
		* @brief	获取请求的网格在数据坐标体系下的角点.
		*			返回的rect的基准点为左上角点，正方向为向右向下.
		* @author	yimin.liu@unispace-x.com
		* @date		2016/10/13
		* @param	level	网格级别.
		* @param	row		横向偏移.
		* @param	col		纵向偏移.
		* @param	corner	输出，顶点.
		* @return	无.
		*************************************************************************/
		inline void get_grid_corners(int level, int row, int col, us_vec2<double>* corner)
		{
			double tile_span = m_tile_regul.m_rect_base.get_height() / (0x1 << level);
			double min_x = tile_span * col + m_tile_regul.m_rect_base.get_min_x();
			double max_x = min_x + tile_span;
			double max_y = m_tile_regul.m_rect_base.get_max_y() - tile_span * row;
			double min_y = max_y - tile_span;
			corner[0].set_x(min_x);
			corner[0].set_y(max_y);
			corner[1].set_x(max_x);
			corner[1].set_y(max_y);
			corner[2].set_x(max_x);
			corner[2].set_y(min_y);
			corner[3].set_x(min_x);
			corner[3].set_y(min_y);

		}

		/**********************************************************************//**
		 * @brief	判断行列在该级别是否有效.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/13
		 * @param	level	网格级别.
		 * @param	row		横向偏移.
		 * @param	col		纵向偏移.
		 * @return	有效返回true.
		 *************************************************************************/
		inline bool is_vaild_rank(int level, int row, int col)
		{
			return m_tile_regul.is_vaild_rank(level, row, col, m_meta.m_geo_rect);
		}

		/**********************************************************************//**
		 * @brief	获取TileMatrixSet瓦片矩阵集xml描述.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/15
		 * @return	xml字符串.
		 *************************************************************************/
		inline us_ustring get_tile_matrix_set_xml()
		{
			return m_tile_regul.get_tile_matrix_set_xml(m_meta.m_layer_name,
				m_meta.m_min_level, m_meta.m_max_level, m_meta.m_tile_pixel_h, m_meta.m_tile_pixel_v);
		}
	};
}
#endif //!__US_WMTS_META_BASE_HPP__