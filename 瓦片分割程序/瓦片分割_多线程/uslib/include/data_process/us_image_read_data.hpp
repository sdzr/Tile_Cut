#ifndef __US_IMAGE_READ_DATA_HPP__
#define __US_IMAGE_READ_DATA_HPP__

#ifndef __US_IMAGE_HPP__
#include "us_image.hpp"
#endif

#ifndef __US_DATA_PROCESS_HPP__
#include "us_data_process.hpp"
#endif

#include <vector>

namespace unispace
{
	class us_ustring;
	class us_image_basic_meta;
	class us_grid_id;
	class us_basic_uv;
	class us_spatial_reference;

	struct us_read_grid_image_rgba_data_param
	{
		/** 待读取的影像meta列表 */
		const std::vector<unispace::us_image_basic_meta>& m_metalist;
		/** 取图的网格 */
		const unispace::us_grid_id& m_gid;
		/** 传入传出影像像素数据保存的buffer */
		std::vector<uint8_t>* m_outBuf;
		/** 传入目标区域的宽高，传出实际取出buf的宽高 */
		int* m_inOutW,* m_inOutH;
		/** 传出取出的位置的中网格的UV */
		unispace::us_basic_uv* m_outUV;
		/** RGB三波段波段序号 */
		int m_rgb_band[3];
		/** 无效像素值(值为 R + G*256 + B*65536) */
		/** 如果不处理无效值，则设为0xff000000U即可(最高位不为0)*/
		uint32_t m_invalid_rgb;
		/** 是否进行透视变换(重采样) */
		bool m_doPerspectiveTransform;

		// 构造函数（必须传入全部参数）
		us_read_grid_image_rgba_data_param(
			const std::vector<unispace::us_image_basic_meta>& metalist,
			const unispace::us_grid_id& gid,
			std::vector<uint8_t>* outBuf, int* inOutW, int* inOutH,
			unispace::us_basic_uv* outUV,
			bool doPerspectiveTransform,
			int rband = 3,int gband = 2,int bband = 1,
			uint32_t invalid_rgb = 0)
			:m_metalist(metalist),
			m_gid(gid),
			m_outBuf(outBuf),m_inOutW(inOutW),m_inOutH(inOutH),
			m_outUV(outUV), m_doPerspectiveTransform(doPerspectiveTransform),
			m_invalid_rgb(invalid_rgb)
		{
			m_rgb_band[0] = rband;
			m_rgb_band[1] = gband;
			m_rgb_band[2] = bband;
		}

		int param_check()const;

	};



	/**********************************************************************//**
		* @brief	获取网格范围影像RGBA像素数据.
		* 			从多个影像中获取网格对应区域的像素数据，默认影像的地理坐标与网格
		*			的地理坐标是一致的.
		* @author	yimin.liu@unispace-x.com
		* @date		2016/11/05
		* @param	metalist	待读取的影像meta列表.
		* @param	gid			取图的网格.
		* @param	[out]outBuf	传出影像像素数据保存的buffer.
		* @param	outW		设置取图输出宽.
		* @param	outH		设置取图输出高.
		* @param	[out]outUV	传出取出的位置的中网格的UV.
		* @param	pyramid_root_path	金字塔的路径.
		* @param	pyramid_fmt			金字塔的格式.
		* @return	读取成功返回保存到缓冲区的数据量(字节数),失败返回一个负数.
		* 			|返回值|含义|
		* 			|:---|:---|
		* 			|-1|影像列表为空|
		* 			|-2|outBuf或outUV为空|
		* 			|-3|outW或outH无效|
		* 			|-4|网格无效|
		* 			|-5|读取数据返回错误|
		*			|-6|计算出的UV无效|
		*************************************************************************/
	_US_DATA_PROCESS_DLL int64_t get_grid_image_rgba_buffer(
		const std::vector<unispace::us_image_basic_meta>& metalist,
		const unispace::us_grid_id& gid,
		std::vector<uint8_t>* outBuf, int OutW, int OutH,
		unispace::us_basic_uv* outUV,
		const unispace::us_ustring& pyramid_root_path,
		us_image::IMAGE_FORMAT pyramid_fmt);

		/**********************************************************************//**
		* @brief	获取网格范围影像RGBA像素数据.
		* 			从多个影像中获取网格对应区域的像素数据，如果网格为投影网格，则认为影像
		*			地理坐标为经纬坐标.反之亦然.
		*			的地理坐标是一致的.
		* @author	yimin.liu@unispace-x.com
		* @date		2016/11/05
		* @param	metalist	待读取的影像meta列表.
		* @param	gid			取图的网格.
		* @param	spr			影像与网格直接转换的坐标参考.
		* @param	[out]outBuf	传出影像像素数据保存的buffer.
		* @param	[in,out]inOutW		传入目标区域的宽，传出实际取出buf的宽.
		* @param	[in,out]inOutH		传入目标区域的高，传出实际取出buf的高.
		* @param	[out]outUV	传出取出的位置的中网格的UV.
		* @param	pyramid_root_path	金字塔的路径.
		* @param	pyramid_fmt			金字塔的格式.
		* @param	doPerspectiveTransform 是否进行透视变换(重采样)
		* @return	读取成功返回保存到缓冲区的数据量(字节数),失败返回一个负数.
		* 			|返回值|含义|
		* 			|:---|:---|
		* 			|-1|影像列表为空|
		* 			|-2|outBuf或outUV为空|
		* 			|-3|outW或outH无效|
		* 			|-4|网格无效|
		* 			|-5|读取数据返回错误|
		*			|-6|计算出的UV无效|
		*			|-7|空间参考无效|
		*************************************************************************/
	_US_DATA_PROCESS_DLL int64_t get_grid_image_rgba_buffer(
		const std::vector<unispace::us_image_basic_meta>& metalist,
		const unispace::us_grid_id& gid,
		const us_spatial_reference& spr,
		std::vector<uint8_t>* outBuf, int* inOutW, int* inOutH,
		unispace::us_basic_uv* outUV,
		const unispace::us_ustring& pyramid_root_path,
		us_image::IMAGE_FORMAT pyramid_fmt,
		bool doPerspectiveTransform);

		/**********************************************************************//**
		* @brief	获取网格范围影像RGBA像素数据.
		* 			从多个影像中获取网格对应区域的像素数据。将根据网格和影像各自的空间参考进行坐标转换.
		*			的地理坐标是一致的.
		* @author	yimin.liu@unispace-x.com
		* @date		2016/11/05
		* @param	metalist	待读取的影像meta列表.
		* @param	img_spr		影像的坐标参考.
		* @param	grid_gid	取图的网格.
		* @param	spr			网格的坐标参考.
		* @param	[out]outBuf	传出影像像素数据保存的buffer.
		* @param	[in,out]inOutW		传入目标区域的宽，传出实际取出buf的宽.
		* @param	[in,out]inOutH		传入目标区域的高，传出实际取出buf的高.
		* @param	[out]outUV	传出取出的位置的中网格的UV.
		* @param	pyramid_root_path	金字塔的路径.
		* @param	pyramid_fmt			金字塔的格式.
		* @param	doPerspectiveTransform 是否进行透视变换(重采样)
		* @return	读取成功返回保存到缓冲区的数据量(字节数),失败返回一个负数.
		* 			|返回值|含义|
		* 			|:---|:---|
		* 			|-1|影像列表为空|
		* 			|-2|outBuf或outUV为空|
		* 			|-3|outW或outH无效|
		* 			|-4|网格无效|
		* 			|-5|读取数据返回错误|
		*			|-6|计算出的UV无效|
		*			|-7|影像或者网格的空间参考无效|
		*************************************************************************/
	_US_DATA_PROCESS_DLL int64_t get_grid_image_rgba_buffer(
		const std::vector<unispace::us_image_basic_meta>& metalist,
		const us_spatial_reference& img_spr,
		const unispace::us_grid_id& gid,
		const us_spatial_reference& grid_spr,
		std::vector<uint8_t>* outBuf, int* inOutW, int* inOutH,
		unispace::us_basic_uv* outUV,
		const unispace::us_ustring& pyramid_root_path,
		us_image::IMAGE_FORMAT pyramid_fmt,
		bool doPerspectiveTransform);

	_US_DATA_PROCESS_DLL int64_t get_grid_image_rgba_buffer_aux(
		const std::vector<unispace::us_image_basic_meta>& metalist,
		const unispace::us_vec2<double>* gridGeoCorner,
		std::vector<uint8_t>* outBuf, int* inOutW, int* inOutH,
		unispace::us_basic_uv& uv,
		const unispace::us_ustring& pyramid_root_path,
		us_image::IMAGE_FORMAT pyramid_fmt,
		bool doPerspectiveTransform);


	/**********************************************************************//**
		* @brief	获取网格范围影像RGBA像素数据.
		* 			从多个影像中获取网格对应区域的像素数据。将根据网格和影像各自的空间参考进行坐标转换.
		*			的地理坐标是一致的.
		* @author	yimin.liu@unispace-x.com
		* @date		2017/04/26
		* @param	rdparam		读取参数.
		* @param	img_spr		影像的坐标参考.
		* @param	spr			网格的坐标参考.
		* @param	pyramid_root_path	金字塔的路径.
		* @param	pyramid_fmt			金字塔的格式.
		* @return	读取成功返回保存到缓冲区的数据量(字节数),失败返回一个负数.
		* 			|返回值|含义|
		* 			|:---|:---|
		* 			|-1|影像列表为空|
		* 			|-2|outBuf或outUV为空|
		* 			|-3|outW或outH无效|
		* 			|-4|网格无效|
		* 			|-5|读取数据返回错误|
		*			|-6|计算出的UV无效|
		*			|-7|影像或者网格的空间参考无效|
		*************************************************************************/
	_US_DATA_PROCESS_DLL int64_t get_grid_image_rgba_buffer(
		const us_read_grid_image_rgba_data_param& rdparam,
		const us_spatial_reference& img_spr,
		const us_spatial_reference& grid_spr,
		const unispace::us_ustring& pyramid_root_path,
		us_image::IMAGE_FORMAT pyramid_fmt);

	_US_DATA_PROCESS_DLL int64_t get_grid_image_rgba_buffer_aux(
		const us_read_grid_image_rgba_data_param& rdparam,
		const unispace::us_vec2<double>* gridGeoCorner,
		const unispace::us_ustring& pyramid_root_path,
		us_image::IMAGE_FORMAT pyramid_fmt);

}

#endif // !__US_IMAGE_READ_DATA_HPP__

