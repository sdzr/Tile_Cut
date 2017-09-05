#ifndef __US_DATASET_INDEX_LIST_HPP__
#define __US_DATASET_INDEX_LIST_HPP__

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
	/** 数据集索引结构体 */
	struct DATASET_INDEX{
		us_ustring	name;	///< 数据集名称
		us_uuid		uuid;	///< 数据集uuid
	};
	// 之所以定义它，而不用std::pair。是有人怕分不清first和second代表什么

	/**********************************************************************//**
	 * @brief	数据集索引列表.
	 *			数据集索引列表用于保存从数据库中获取的数据集名称和UUID。<br>
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/8/02
	 *************************************************************************/
	class us_dataset_index_list
		:public us_basic_index_list<DATASET_INDEX> {
	private:
		/** 当前只授权下面三个类进行访问 */
		friend class us_dataset_manager_by_mysql;
		friend class us_dataset_manager_by_sqlite;
		friend class us_dataset_manager_by_mongodb;

		/**********************************************************************//**
		 * @brief	添加一个数据集索引到列表.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/02
		 * @param	name	以UTF8编码的数据集name.
		 * @param	uuid	数据集UUID的二进制形式.
		 *************************************************************************/
		void add_index(const char* name, const unsigned char* uuid);

		/**********************************************************************//**
		 * @brief	添加一个数据集索引到列表.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/02
		 * @param	name	以UTF8编码的数据集name(此处会改变传入的参数).
		 * @param	uuid	数据集UUID.
		 *************************************************************************/
		void add_index(const us_ustring& name,const us_uuid& uuid);
	};


	
		
	/**********************************************************************//**
	* @brief	添加一个数据集索引到列表.
	*************************************************************************/
	inline void us_dataset_index_list::add_index(
		const char* name, const unsigned char* uuid)
	{
		DATASET_INDEX dataset_index;
		dataset_index.name.assign(name);
		dataset_index.uuid.set_raw_data(uuid);
		m_index.push_back(dataset_index);
	}

	/**********************************************************************//**
	* @brief	添加一个数据集索引到列表.
	* @param	name	以UTF8编码的数据集name.
	* @param	uuid	数据集UUID.
	*************************************************************************/
	inline void us_dataset_index_list::add_index(
		const us_ustring& name, const us_uuid& uuid)
	{
		DATASET_INDEX dataset_index;
		dataset_index.name = name;
		dataset_index.uuid = uuid;
		m_index.push_back(dataset_index);
	}

}
#endif	// __US_DATASET_INDEX_LIST_HPP__
