#ifndef __US_META_JSON_CONVERT_HPP__
#define __US_META_JSON_CONVERT_HPP__

#ifndef __US_METADATA_HPP__
#include "us_metadata.hpp"
#endif // !__US_METADATA_HPP__


namespace unispace
{
	class us_ustring;
	class us_image_basic_meta;
	class us_dataset_basic_meta;
	struct us_wmts_basic_meta;
	class us_wmts_theme_basic_meta;

	/**********************************************************************//**
	 * @brief	将影像元数据转换为json字符串.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/2/27
	 * @param	in_meta		传入影像元信息.
	 * @param	out_json	传出json字符串
	 * @return	成功返回true,失败返回false.
	 *************************************************************************/
	_US_METADATA_DLL bool us_image_meta_to_json(
		const us_image_basic_meta& in_meta,us_ustring* out_json);
	
	/**********************************************************************//**
	 * @brief	从json字符串解析出影像元数据信息.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/2/27
	 * @param	in_json		传入json字符串
	 * @param	out_meta	传出影像元信息.
	 * @return	成功返回true,失败返回false.
	 *************************************************************************/
	_US_METADATA_DLL bool us_json_to_image_meta(
		const us_ustring& in_json,us_image_basic_meta* out_meta);



	/**********************************************************************//**
	 * @brief	将数据集元数据转换为json字符串.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/2/27
	 * @param	in_meta		传入数据集元信息.
	 * @param	out_json	传出json字符串
	 * @return	成功返回true,失败返回false.
	 *************************************************************************/
	_US_METADATA_DLL bool us_dataset_meta_to_json(
		const us_dataset_basic_meta& in_meta,us_ustring* out_json, bool hasimgids);
	
	/**********************************************************************//**
	 * @brief	从json字符串解析出数据集元数据信息.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/2/27
	 * @param	in_json		传入json字符串
	 * @param	out_meta	传出数据集元信息.
	 * @return	成功返回true,失败返回false.
	 *************************************************************************/
	_US_METADATA_DLL bool us_json_to_dataset_meta(
		const us_ustring& in_json, us_dataset_basic_meta* out_meta, bool hasimgids);


	/**********************************************************************//**
	 * @brief	将wmts元数据转换为json字符串.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/2/27
	 * @param	in_meta		传入wmts元信息.
	 * @param	out_json	传出json字符串
	 * @return	成功返回true,失败返回false.
	 *************************************************************************/
	_US_METADATA_DLL bool us_wmts_meta_to_json(
		const us_wmts_basic_meta& in_meta,us_ustring* out_json);
	
	/**********************************************************************//**
	 * @brief	从json字符串解析出wmts元数据信息.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/2/27
	 * @param	in_json		传入json字符串
	 * @param	out_meta	传出wmts元信息.
	 * @return	成功返回true,失败返回false.
	 *************************************************************************/
	_US_METADATA_DLL bool us_json_to_wmts_meta(
		const us_ustring& in_json,us_wmts_basic_meta* out_meta);


	/**********************************************************************//**
	 * @brief	将wmts theme元数据转换为json字符串.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/2/27
	 * @param	in_meta		传入wmts theme元信息.
	 * @param	out_json	传出json字符串
	 * @return	成功返回true,失败返回false.
	 *************************************************************************/
	_US_METADATA_DLL bool us_wmts_theme_meta_to_json(
		const us_wmts_theme_basic_meta& in_meta,us_ustring* out_json);
	
	/**********************************************************************//**
	 * @brief	从json字符串解析出wmts theme元数据信息.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/2/27
	 * @param	in_json		传入json字符串
	 * @param	out_meta	传出wmts theme元信息.
	 * @return	成功返回true,失败返回false.
	 *************************************************************************/
	_US_METADATA_DLL bool us_json_to_wmts_theme_meta(
		const us_ustring& in_json,us_wmts_theme_basic_meta* out_meta);
}


#endif // !__US_META_JSON_CONVERT_HPP__
