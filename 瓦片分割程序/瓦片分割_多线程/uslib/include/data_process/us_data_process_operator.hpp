/**********************************************************************//**
 * @file us_data_process_operator.hpp
 *
 * 声明 建金字塔/读取影像元数据/投影和影像行列坐标转换四个函数.
 *************************************************************************/

#ifndef __US_DATA_PROCESS_OPERATOR_HPP__
#define __US_DATA_PROCESS_OPERATOR_HPP__


#ifndef __US_IMAGE_HPP__
#include "us_image.hpp"
#endif


#ifndef __US_DATA_PROCESS_HPP__
#include "us_data_process.hpp"
#endif

#include <vector>

namespace unispace
{
	class us_image_basic_meta;
	class us_ustring;
	class us_grid_base;
	class us_grid_uv;
	class us_grid_id;
	class us_uuid;

	/**********************************************************************//**
	 * @brief	初始化data process库.
	 *			执行以下初始化动作，包括GDAL的初始化.
	 * @author yimin.liu@unispace-x.com
	 * @date 2016/3/25
	 *************************************************************************/
	_US_DATA_PROCESS_DLL void initialization_data_process();


	/**********************************************************************//**
	 * @brief	创建影像金字塔.
	 *			1/(4^n)抽稀至宽或者高小于512截止(n为1,2,3,...).<br>
	 *			输出的金字塔影像放置在 pyramid_root_path 目录下，以影像的uuid为
	 *			名称的子目录中.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/6/7
	 * @param [in,out]	in_out_meta	要创建金字塔的影像元信息.
	 * @param			fmt			输出影像格式.
	 * @param	pyramid_root_path	输出金字塔的根路径.
	 *************************************************************************/
	_US_DATA_PROCESS_DLL bool creat_image_pyramid(us_image_basic_meta* in_out_meta,
												  us_image::IMAGE_FORMAT fmt,
												  const us_ustring& pyramid_root_path);

	/**********************************************************************//**
	 * @brief	删除影像金字塔.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/8/10
	 * @param [in]	uuid				影像的uuid.
	 * @param [in]	pyramid_root_path	金字塔根目录.
	 * @return		成功返回true,失败返回false.
	 ***********************************************************************/
	_US_DATA_PROCESS_DLL bool remove_image_pyramid(const us_uuid& uuid,
												   const us_ustring& pyramid_root_path);

	/**********************************************************************//**
	 * @brief	读取影像元数据.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/23
	 * @param	path			影像路径(统一后的路径).
	 * @param	[in,out]		传入传出影像meta信息.
	 * @param	update_uuid	    为true时更新uuid.
	 * @return	成功返回true，失败返回false.
	 *************************************************************************/

	_US_DATA_PROCESS_DLL bool generate_image_meta(const us_ustring& path,
												  us_image_basic_meta* out_meta,
												  bool update_uuid = true);

	/**********************************************************************//**
	 * @brief	编码RGBA8888排列的的影像像素数据问哦PNG格式数据.
	 *			当前只支持RGBA8888排列的像素数据，不支持其他形式.
	 *			输出的PNG数据为无损压缩形式.需要确保pSrc指向的缓
	 *			冲区的大小为 srcW * srcH * 4 bytes.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/12/08
	 * @param	pSrc	像素数据地址.
	 * @param	srcW	像素数据的横向像素数.
	 * @param	srcH	像素数据的纵向像素数.
	 * @param	pDst	目标png数据缓存区.
	 * @return	成功返回true,失败返回false.
	 *************************************************************************/
	_US_DATA_PROCESS_DLL bool encode_rgba8888_to_png32(
		const void* pSrc,int srcW, int srcH,std::vector<uint8_t>* pDst);

	/**********************************************************************//**
	 * @brief	影像数据冷转热.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/12/26
	 * @param	meta	影像的元数据.
	 * @return	成功返回0，失败返回负数.
	 *************************************************************************/
	_US_DATA_PROCESS_DLL int create_image_heating_data(
		const us_image_basic_meta& meta);

	/**********************************************************************//**
	 * @brief	影像数据热转冷.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/12/26
	 * @param	meta	影像的元数据.
	 * @return	成功返回0，失败返回负数.
	 *************************************************************************/
	_US_DATA_PROCESS_DLL int remove_image_heating_data(
		const us_image_basic_meta& meta);




	/**********************************************************************//**
	 * @brief	获取指定路径的影像的网格UV.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/6/28
	 * @param	path			    影像文件的路径.
	 * @param	grid
	 * @param	[in,out] out_uv If non-null, the out meta.
	 * @return true if it succeeds, false if it fails.
	 *************************************************************************/
	_US_DATA_PROCESS_DLL bool generate_image_grid_uv(const us_ustring& path,
													 const us_grid_base& grid,
													 us_grid_uv* out_uv);


	_US_DATA_PROCESS_DLL bool generate_image_grid_uv(const us_ustring& path,
													 const us_grid_id& gid,
													 us_grid_uv* out_uv);

	_US_DATA_PROCESS_DLL bool generate_image_grid_uv(const us_ustring& path,
													 const char* grid_str,
													 us_grid_uv* out_uv);

	_US_DATA_PROCESS_DLL bool generate_image_grid_uv(const us_image_basic_meta& meta,
													 const char* grid_str,
													 us_grid_uv* out_uv);
}


#endif //!__US_DATA_PROCESS_OPERATOR_HPP__
