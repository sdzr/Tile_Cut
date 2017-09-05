#ifndef __US_IMAGE_INDEX_LIST_HPP__
#define __US_IMAGE_INDEX_LIST_HPP__

#ifndef __US_STRING_HPP__
#include "util/common/us_string.hpp"
#endif

#ifndef __US_UUID_HPP__
#include "util/uuid/us_uuid.hpp"
#endif

#ifndef __US_BASIC_INDEX_LIST_HPP__
#include "data_manager/us_basic_index_list.hpp"
#endif

namespace unispace
{
	/** 影像索引结构体 */
	struct IMG_INDEX{
		us_ustring	url;	///< 影像路径
		us_uuid		uuid;	///< 影像uuid
	};
	// 之所以定义它，而不用std::pair。是有人怕分不清first和second代表什么

	/**********************************************************************//**
	 * @brief	影像索引列表.
	 *			影像索引列表用于保存从数据库中获取的影像URL和UUID。<br>
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/22
	 *************************************************************************/
	class us_image_index_list
		:public us_basic_index_list<IMG_INDEX> {
	private:
		/** 当前只授权下面两个类进行访问 */
		friend class us_image_manager_by_mysql;
		friend class us_image_manager_by_sqlite;
		friend class us_image_manager_by_mongodb;

		/**********************************************************************//**
		 * @brief	添加一个影像索引到列表.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/6
		 * @param	url		以UTF8编码的影像URL.
		 * @param	uuid	影像UUID的二进制形式.
		 *************************************************************************/
		void add_index(const char* url, const unsigned char* uuid);

		/**********************************************************************//**
		 * @brief	添加一个影像索引到列表.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/6
		 * @param	url		以UTF8编码的影像URL(此处会改变传入的参数).
		 * @param	uuid	影像UUID.
		 *************************************************************************/
		void add_index(const us_ustring& url,const us_uuid& uuid);
	};


	/**********************************************************************//**
	* @brief	添加一个影像索引到列表.
	*************************************************************************/
	inline void us_image_index_list::add_index(
		const char* url, const unsigned char* uuid)
	{
		IMG_INDEX img_index;
		img_index.url.assign(url);
		img_index.uuid.set_raw_data(uuid);
		m_index.push_back(img_index);
	}

	/**********************************************************************//**
	* @brief	添加一个影像索引到列表.
	* @param	url		以UTF8编码的影像URL.
	* @param	uuid	影像UUID.
	*************************************************************************/
	inline void us_image_index_list::add_index(
		const us_ustring& url, const us_uuid& uuid)
	{
		IMG_INDEX img_index;
		img_index.url = url;
		img_index.uuid = uuid;
		m_index.push_back(img_index);
	}

}
#endif
