/**********************************************************************//**
 * @file us_dataset_manager_by_sqlite.hpp
 *
 * 定义 the us_dataset_manager_by_sqlite 类.
 *************************************************************************/
#ifndef __US_DATASET_MANAGER_BY_SQLITE_HPP__
#define __US_DATASET_MANAGER_BY_SQLITE_HPP__

#ifndef __US_DATASET_MANAGER_HPP__
#include "../us_dataset_manager.hpp"
#endif

struct sqlite3;

namespace unispace
{
	/**********************************************************************//**
	 * @brief	基于SQLite3数据库的数据集管理类.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/5/20
	 *************************************************************************/
	class us_dataset_manager_by_sqlite :
		public us_dataset_manager
	{
	private:
		/** sqlite数据库操作句柄 */
		sqlite3* db;
		us_dataset_manager_by_sqlite(const us_dataset_manager_by_sqlite&);
		us_dataset_manager_by_sqlite& operator=(const us_dataset_manager_by_sqlite&);

		/** 给予基类访问权限 */
		friend class us_dataset_manager;

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	filename SQLite3文件路径.
		 *************************************************************************/
		us_dataset_manager_by_sqlite(const char* filename);

		virtual ~us_dataset_manager_by_sqlite();

	public:
		/**********************************************************************//**
		 * @brief	添加数据集到数据库.
		 *			如果已经存在，？？？？
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	meta			数据集meta信息.
		 * @param	update_ctime	是否更新创建时间.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_dataset(const us_dataset_basic_meta& meta,
									  bool update_ctime = true)const;

		/**********************************************************************//**
		 * @brief	从数据库中删除数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	uuid		数据集的uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_dataset(const us_uuid& uuid)const;

		/**********************************************************************//**
		 * @brief	从数据库中删除数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/24
		 * @param	name		数据集的名称.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_dataset(const us_ustring& name)const;

		/**********************************************************************//**
		 * @brief	查找数据集名称.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/23
		 * @param	uuid			数据集的 uuid.
		 * @param	[out] out_name	如果非NULL，传出数据集名称.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_name(const us_uuid& uuid,
											us_ustring* out_name)const;

		/**********************************************************************//**
		 * @brief	查找数据集UUID.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/23
		 * @param	name			影像的 uuid数据集的名称.
		 * @param	[out] out_uuid	如果非NULL，传出数据集UUID.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_uuid(const us_ustring& name,
											us_uuid* out_uuid)const;

		/**********************************************************************//**
		 * @brief	查找数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	uuid		数据集的uuid.
		 * @param	[out] out_meta	如果非NULL，传出数据集的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset(const us_uuid& uuid,
									   us_dataset_basic_meta* out_meta)const;

		/**********************************************************************//**
		 * @brief	查找数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	name		数据集的名称.
		 * @param	[out] out_meta	如果非NULL，传出数据集的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset(const us_ustring& name,
									   us_dataset_basic_meta* out_meta)const;

		/**********************************************************************//**
		 * @brief	更新数据集.
		 *			更新数据集的meta信息和记录的影像uuid集合。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	meta			数据集meta信息.
		 * @param	not_up_uuidset	不更新记录的影像uuid集合，默认为true.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT update_dataset(const us_dataset_basic_meta& meta,
										 bool not_up_uuidset = true)const;

		/**********************************************************************//**
		 * @brief	获取当前数据库总的数据集数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/22
		 * @param	out_count	传出总的影像数.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_dataset_count(long int* out_count)const;

		/**********************************************************************//**
		 * @brief	获取当前数据库数据集索引列表.
		 * 			获取到的是根据起止索引数(SQL表中的行号)影像的路径和uuid的索引。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/02
		 * @param	beg_index	要获取的数据集的起始索引号(从0开始)
		 * @param	count		要获取的数据集索引数
		 * @param	out_list	传出索引范围内的数据集索引.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_dataset_index_list_by_range(int beg_index,int count,
														  us_dataset_index_list* out_list
														  )const;
	};
}

#endif //!__US_DATASET_MANAGER_BY_SQLITE_HPP__
