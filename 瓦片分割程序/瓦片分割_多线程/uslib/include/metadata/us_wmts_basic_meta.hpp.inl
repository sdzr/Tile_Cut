#ifndef __US_WMTS_BASIC_META_HPP_INL__
#define __US_WMTS_BASIC_META_HPP_INL__

#ifndef __US_STRING_HPP__
#include "util/common/us_string.hpp"
#endif
#ifndef __US_UUID_HPP__
#include "util/uuid/us_uuid.hpp"
#endif // !__US_UUID_HPP__
#ifndef __US_GEO_RECT_HPP__
#include "util/math/us_geo_rect.hpp"
#endif

#ifndef __US_GRID_SYSTEM_HPP__
#include "grid_system/us_grid_system.hpp"
#endif

#ifndef __US_SPATIAL_RECORD_HPP__
#include "geo_coord_transform/us_spatial_record.hpp"
#endif

namespace unispace
{

	template<typename _GRID>
	inline us_rect<double> us_wmts_basic_meta::get_rect_base_top_left(int level) const
	{
		// 限制模板参数
		static_assert(std::is_same<_GRID, us_grid_meter>::value ||
			std::is_same<_GRID, us_grid_degree>::value,
			"template parameter must is unispace grid class name");

		// 谷歌经纬度网格瓦片
		if (m_tile_type == 2){
			return us_rect<double>(-180.0, -90.0, 360.0, 180.0);
		}
		// 谷歌Web墨卡托网格瓦片
		if (m_tile_type == 3){
			return us_rect<double>(-20037508.3427892, -20037508.3427892, 40075016.6855784, 40075016.6855784);
		}

		// 左上角是西北(保存的地理范围方向与数据集的一致)
		Point2lf xy = m_geo_rect.get_corner(us_geo_rect::CONRNER_TYPE::WEST_NORTH);
		// 取这个网格的左上角点
		_GRID lt;
		lt.set_grid_from_coords(xy.get_x(), xy.get_y(), level);
		// 计算网格最大范围
		us_rect<double> maxrt = lt.get_geo_rect().get_combine(m_geo_rect);
		double unit = us_grid_base::grid_unit_length(lt.get_type(), level);
		maxrt.set_size(floor(maxrt.get_width() / unit)*unit, floor(maxrt.get_height() / unit)*unit);
		// 将范围的基准点改为左上角
		Point2lf origin = maxrt.get_origin();
		origin.set_y(origin.get_y() + maxrt.get_height());
		maxrt.set_origin(origin);
		// 返回
		return maxrt;
	}

	template<typename _GRID>
	inline us_grid_id us_wmts_basic_meta::get_grid_id(int level, int row, int col) const
	{
		// 限制模板参数
		static_assert(std::is_same<_GRID, us_grid_meter>::value ||
			std::is_same<_GRID, us_grid_degree>::value,
			"template parameter must is unispace grid class name");

		// 取左上角点的网格
		// 左上角是西北(保存的地理范围方向与数据集的一致)
		Point2lf xy = m_geo_rect.get_corner(us_geo_rect::CONRNER_TYPE::WEST_NORTH);
		_GRID lt;
		lt.set_grid_from_coords(xy.get_x(), xy.get_y(), level);
		// 对网格进行偏移
		lt.us_grid_base::get_offset_grid(&lt, col, -row);
		return lt.get_full_id();
	}

	template<typename _GRID>
	inline bool us_wmts_basic_meta::is_vaild_rank(int level, int row, int col) const
	{
		us_size<int> sz = get_tile_ranks<_GRID>(level);
		return !((row < 0) || (col < 0) || (row > sz.m_height) || (col > sz.m_width));
	}

	template<typename _GRID>
	inline double us_wmts_basic_meta::get_scale_denomination(int level) const
	{
		// 限制模板参数
		static_assert(std::is_same<_GRID, us_grid_meter>::value ||
			std::is_same<_GRID, us_grid_degree>::value,
			"template parameter must is unispace grid class name");
		// pixelSpan = scaleDenomination * 0.00028 / metersPerUnit(crs)
		// scaleDenomination = pixelSpan * metersPerUnit(crs) / 0.00028
		// 缩放分母 = 像素跨度 * 米每单位 / 0.00028
		// 米每单位与坐标系有关
		double sd = m_max_scale_denom *(0x1 << (m_max_level - level));
		return sd;
	}

	template<typename _GRID>
	inline us_size<int> us_wmts_basic_meta::get_tile_ranks(int level) const
	{
		// 谷歌经纬度网格默认为2^level * 2^level 个格子
		if (m_tile_type == 2) {
			const int row = (0x1 << level);
			return (us_size<int>(row, row));
		}
		// 比谷歌经纬度在横向上多一倍
		if (m_tile_type == 3) {
			const int col = (0x1 << level);
			return (us_size<int>(col * 2, col));
		}

		us_rect<double> grt = get_rect_base_top_left<_GRID>(level);
		_GRID g;
		double grid_width = us_grid_base::grid_unit_length(g.get_type(), level);
		int w = grt.get_width() / grid_width;
		int h = grt.get_height() / grid_width;
		return us_size<int>(w, h);
	}

	template<typename _GRID>
	inline us_ustring us_wmts_basic_meta::get_tile_matrix_set_xml()const
	{
		us_ustring tms;
		tms.reserve(abs(m_max_level - m_min_level) * 384);

		// 相关参数
		int epsg_code = 4326;   // 内部度网格、谷歌经纬度瓦片均默认4326
		if (m_tile_type == 1){
			// 米网格需要计算对应的code
			us_spatial_record rcd;
			rcd.id = m_spr_uuid;
			epsg_code = rcd.get_spr_code();
		}
		else if (m_tile_type == 3){
			epsg_code = 3857; // Google WebMerc 3857；
		}

		// 添加xml文本
		tms.append("<TileMatrixSet><ows:Identifier>").append(m_layer_name).append("</ows:Identifier>");
		tms.append("<ows:SupportedCRS>urn:ogc:def:crs:EPSG::").append(us_ustring().set_num(epsg_code)).append("</ows:SupportedCRS>");
		{
			// 添加每一个层级
			for (int level = m_min_level; level <= m_max_level; ++level) {
				// 获取缩放分母
				double scaledenom = get_scale_denomination<_GRID>(level);
				// 获取地理范围
				us_rect<double> grt = get_rect_base_top_left<_GRID>(level);
				// 计算格子数
				us_size<int> ranks = get_tile_ranks(level);
				tms.append("<TileMatrix>");
				tms.append("<ows:Identifier>").append(us_ustring().set_num(level)).append("</ows:Identifier>");
				tms.append("<ScaleDenominator>").append(us_ustring().set_num(scaledenom)).append("</ScaleDenominator>");
				tms.append("<TopLeftCorner>").append(us_ustring().set_num(grt.get_origin().get_y() + grt.get_height()));
				tms.append(" ").append(us_ustring().set_num(grt.get_origin().get_x())).append("</TopLeftCorner>");
				tms.append("<TileWidth>").append(us_ustring().set_num(m_tile_pixel_h)).append("</TileWidth>");
				tms.append("<TileHeight>").append(us_ustring().set_num(m_tile_pixel_v)).append("</TileHeight>");
				tms.append("<MatrixWidth>").append(us_ustring().set_num(ranks.m_width)).append("</MatrixWidth>");
				tms.append("<MatrixHeight>").append(us_ustring().set_num(ranks.m_height)).append("</MatrixHeight>");
				tms.append("</TileMatrix>");
			}
		}
		tms.append("</TileMatrixSet>");
		return tms;
	}
}


#endif //!__US_WMTS_BASIC_META_HPP_INL__
