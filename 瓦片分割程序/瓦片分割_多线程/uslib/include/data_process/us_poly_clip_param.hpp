#ifndef __US_POLY_CLIP_PARAM_HPP__
#define __US_POLY_CLIP_PARAM_HPP__

#ifndef __US__STRING__HPP__
#include "util/common/us_string.hpp"
#endif

#ifndef __US_IMAGE_BASIC_META_HPP__
#include "metadata/us_image_basic_meta.hpp"
#endif

#ifndef __US_DATA_PROCESS_HPP__
#include "us_data_process.hpp"
#endif


#include <vector>


namespace unispace
{
	/**********************************************************************//**
	 * @class	unispace::us_poly_clip_param
	 * @brief	多边形裁切参数信息类.
	 * 			包含了多边形裁切所需要的相关参数.<br>
	 * 			1、多边形数组<br>
	 * 			2、影像meta数组<br>
	 * 			3、目标影像的纵横像素数<br>
	 * 			4、重采样模式<br>
	 * 			5....
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/4/5
	 *************************************************************************/
	class _US_DATA_PROCESS_DLL us_poly_clip_param
	{
	public:
		/** 单个平面多边形点序列 */
		typedef std::vector<us_vec2<double> > POLY;
		/** 影像meta数组 */
		typedef std::vector<us_image_basic_meta> METAARRAY;
		/** 重采样类型 */
		enum RESAMPLE_MODE{
			CCY_NEARESTNEIGHBOUR = 0,///< 最邻近法（选择一个输入像素）
			CCY_BILINEAR = 1,        ///< 双线性内插法（2X2内核）
			CCY_CUBIC = 2,           ///< 三次卷积法（4X4内核）
			CCY_CUBICSPLINE = 3,     ///< 三次B样条逼近（4X4内核）
			CCY_LANCZOS = 4,         ///< lanczos窗sinc插值（6X6内核）
			CCY_AVERAGE = 5,         ///< 平均值法
			CCY_MODE = 6,            ///< 模式（选择最常出现的所有采样点的值）
			// CCY_GAUSS = 7保留。
			CCY_MAX = 8,             ///< 最大值法
			CCY_MIN = 9,             ///< 最小值法
			CCY_MED = 10,            ///< 中位数值法
			CCY_Q1 = 11,             ///< Q1（选择所有非空有像素的第一个四分位数）
			CCY_Q3 = 12              ///< Q3（选择所有非空有第三像素值）
		};

	public:
		us_poly_clip_param();

		/**********************************************************************//**
		 * @brief	判断是否无效.
		 * 			返回true一定是无效的,回false也不表示有效.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @return true if invalid, false if not.
		 *************************************************************************/
		bool is_invalid()const;

		/** 目标存储路径 */
		us_ustring	m_dst_url;
		// 目标影像格式[从目标存储路径的后缀名中提取]
		// us_image::IMAGE_FORMAT m_imgfmt;

		/** 目标图像横向像素数 */
		mutable int	m_pixel_h;
		/** 目标图像纵向像素数 */
		mutable int	m_pixel_v;

		/** 目标图像与原始数据集的大小的比例 */
		float		m_scale_h;
		float		m_scale_v;
		
		// 目标投影参数
		
		/** 用于裁切的影像序列 */
		METAARRAY	m_meta_array;
		/** 进行裁切的多边形序列(地理范围) */
		std::vector<POLY> m_multi_polygon;
		/** 重采样方法 */
		RESAMPLE_MODE	m_resample_mode;
	};

	_US_DATA_PROCESS_DLL bool us_poly_clip_param_space_unification(
		us_poly_clip_param* in_out_info,
		const us_uuid& img_spr_id, const us_uuid& poly_spr_id);

}

#endif //!__US_POLY_CLIP_PARAM_HPP__