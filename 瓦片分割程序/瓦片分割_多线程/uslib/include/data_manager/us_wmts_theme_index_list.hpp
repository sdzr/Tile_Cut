#ifndef __US_WMTS_THEME_INDEX_LIST_HPP__
#define __US_WMTS_THEME_INDEX_LIST_HPP__

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
	/**wmts主题索引结构体 */
	struct WMTS_THEME_INDEX {
		us_ustring	name;	///< 数据集名称
		us_uuid		uuid;	///< 数据集uuid
	};

	class us_wmts_theme_index_list
		:public us_basic_index_list<WMTS_THEME_INDEX> {
	private:
		/** 当前只授权下面三个类进行访问 */
		friend class us_wmts_theme_manager_by_mysql;
		//friend class us_wmts_theme_manager_by_sqlite;
		friend class us_wmts_theme_manager_by_mongodb;
	public:
		/**********************************************************************//**
		 * @brief	添加一个wmts主题索引到列表.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/02
		 * @param	name	以UTF8编码的wmts主题name.
		 * @param	uuid	数据集UUID的二进制形式.
		 *************************************************************************/
		void add_index(const char* name, const unsigned char* uuid);

		/**********************************************************************//**
		 * @brief	添加一个wmts主题索引到列表.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/02
		 * @param	name	以UTF8编码的wmts主题name.
		 * @param	uuid	数据集UUID.
		 *************************************************************************/
		void add_index(const us_ustring& name,const us_uuid& uuid);
	};


	

	/**********************************************************************//**
	* @brief	添加一个wmts主题索引到列表.
	*************************************************************************/
	inline void us_wmts_theme_index_list::add_index(
		const char* name, const unsigned char* uuid)
	{
		WMTS_THEME_INDEX dataset_index;
		dataset_index.name.assign(name);
		dataset_index.uuid.set_raw_data(uuid);
		m_index.push_back(dataset_index);
	}

	/**********************************************************************//**
	* @brief	添加一个wmts主题索引到列表.
	* @param	name	以UTF8编码的wmts主题 name.
	* @param	uuid	数据集UUID.
	*************************************************************************/
	inline void us_wmts_theme_index_list::add_index(
		const us_ustring& name, const us_uuid& uuid)
	{
		WMTS_THEME_INDEX dataset_index;
		dataset_index.name = name;
		dataset_index.uuid = uuid;
		m_index.push_back(dataset_index);
	}

}

#endif // !__US_WMTS_THEME_INDEX_LIST_HPP__
