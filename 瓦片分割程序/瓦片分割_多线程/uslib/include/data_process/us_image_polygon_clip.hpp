#ifndef __US_IMAGE_POLYGON_CLIP_HPP__
#define __US_IMAGE_POLYGON_CLIP_HPP__

#ifndef __US_POLY_CLIP_PARAM_HPP__
#include "us_poly_clip_param.hpp"
#endif

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_image_polygon_clip
	 * @brief	影像多边形裁切.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/14
	 *************************************************************************/
	class _US_DATA_PROCESS_DLL us_image_polygon_clip
	{
	public:

		/**********************************************************************//**
		 * @brief	执行多边形裁切影像操作.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @param	clipinfo 裁切信息对象.
		 * @return
		 *			|返回值|含义|
		 *			|---:|:---|
		 *			|0 |成功|
		 * 			|-1|裁剪信息无效|
		 *			|-2|有的影像数据不正确|
		 *			|-3|ChunkAndWarpImage失败|
		 *			|-4|创建输出文件失败|
		 *			|-5|创建WarpOptions失败|
		 *			|-6|打开输入影像文件失败|
		 *			|-7|实际影像文件波段数不匹配|
		 *			|-8|创建坐标转换参数失败|
		 *************************************************************************/

		static int image_polygon_clip(const us_poly_clip_param& clipinfo);
	};


}
#endif //!__US_IMAGE_POLYGON_CLIP_HPP__
