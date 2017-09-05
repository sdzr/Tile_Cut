#ifndef __US_WMTS_INDEX_LIST_HPP__
#define __US_WMTS_INDEX_LIST_HPP__

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
	struct WMTS_INDEX {
		us_ustring	layer;	///< wmts图层名称
		us_uuid		uuid;	///< 对应数据集的uuid
	};

	/**********************************************************************//**
	 * @brief	数据集索引列表.
	 *			数据集索引列表用于保存从数据库中获取的数据集名称和UUID。<br>
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/8/02
	 *************************************************************************/
	class us_wmts_index_list
		:public us_basic_index_list<WMTS_INDEX>{
		
	private:
		/** 当前只授权下面三个类进行访问 */
		friend class us_wmts_manager_by_mysql;
		//friend class us_wmts_manager_by_sqlite;
		friend class us_wmts_manager_by_mongodb;

		/**********************************************************************//**
		 * @brief	添加一个wmts索引到列表.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @param	layer	以UTF8编码的wmts图层名.
		 * @param	uuid	数据集UUID的二进制形式.
		 *************************************************************************/
		void add_index(const char* layer, const unsigned char* uuid);

		/**********************************************************************//**
		 * @brief	添加一个wmts索引到列表.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @param	layer	以UTF8编码的wmts图层名.
		 * @param	uuid	数据集UUID.
		 *************************************************************************/
		void add_index(const us_ustring& layer,const us_uuid& uuid);
	};
	
	
	inline void us_wmts_index_list::add_index(
		const char * layer, const unsigned char * uuid)
	{
		WMTS_INDEX index;
		index.layer.assign(layer);
		index.uuid.set_raw_data(uuid);
		m_index.push_back(index);
	}
	inline void us_wmts_index_list::add_index(
		const us_ustring & layer, const us_uuid & uuid)
	{
		WMTS_INDEX index;
		index.layer = layer;
		index.uuid = uuid;
		m_index.push_back(index);
	}
}



#endif // !__US_WMTS_INDEX_LIST_HPP__

