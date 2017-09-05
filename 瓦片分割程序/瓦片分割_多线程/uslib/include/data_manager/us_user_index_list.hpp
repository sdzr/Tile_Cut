#ifndef __US_USER_INDEX_LIST_HPP__
#define __US_USER_INDEX_LIST_HPP__

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
	/** 用户索引结构体 */
	struct USER_INDEX {
		us_ustring	name;	///< 用户名
		us_uuid		id;		///< 用户ID
	};

	/**********************************************************************//**
	 * @brief	用户索引列表.
	 *			用户索引列表用于保存从数据库中获取的用户名称和UUID。<br>
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/4/26
	 *************************************************************************/
	class us_user_index_list
		:public us_basic_index_list<USER_INDEX>{
		
	private:
		/** 当前只授权下面三个类进行访问 */
		friend class us_user_manager_by_mysql;
		//friend class us_user_manager_by_sqlite;
		friend class us_user_manager_by_mongodb;

		/**********************************************************************//**
		 * @brief	添加一个用户索引到列表.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/26
		 * @param	name	以UTF8编码的用户名.
		 * @param	uuid	用户ID的二进制形式.
		 *************************************************************************/
		void add_index(const char* name, const unsigned char* uuid);

		/**********************************************************************//**
		 * @brief	添加一个用户索引到列表.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/26
		 * @param	name	以UTF8编码的用户名.
		 * @param	uuid	用户ID.
		 *************************************************************************/
		void add_index(const us_ustring& name,const us_uuid& id);
	};
	
	
	inline void us_user_index_list::add_index(
		const char * name, const unsigned char * uuid)
	{
		USER_INDEX index;
		index.name.assign(name);
		index.id.set_raw_data(uuid);
		m_index.push_back(index);
	}
	inline void us_user_index_list::add_index(
		const us_ustring & name, const us_uuid & id)
	{
		USER_INDEX index;
		index.name = name;
		index.id = id;
		m_index.push_back(index);
	}
}

#endif // !__US_USER_INDEX_LIST_HPP__

