#ifndef __US_GRID_TYPE_HPP__
#define __US_GRID_TYPE_HPP__

namespace unispace
{
	/** 表示网格类型的枚举值. */
	enum class us_grid_type :unsigned short
	{
		GRID_TYPE_UNKNOWN     = 0,	///< 未知类型网格
		GRID_TYPE_METER       = 1,	///< 投影网格，米网格为基准网格
		GRID_TYPE_DEGREE      = 2,	///< 度网格，度以下四分，所有网格都左下角为基准
		GRID_TYPE_DEGREE_QUAD = 3,	///< 度网格，度以下四分，网格基准根据象限确定
		GRID_TYPE_SECOND      = 4,	///< 度分秒网格，所有网格都左下角为基准
		GRID_TYPE_SECOND_QUAD = 5,	///< 度分秒网格，网格基准根据象限确定
		GRID_TYPE_KILOMETER   = 6,	///< 投影网格，公里、米两级基准网格

		// 扩展时请注意，网格类型的数值最好限定在31以内。
	};
}

#endif //!__US_GRID_TYPE_HPP__